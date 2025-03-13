#include "timer.h"
#include "ui_timer.h"
#include "pomodorosettings.h"  // This one is crucial 🔥
#include <QMessageBox>

Timer::Timer(Database *database, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timer)
    , db(database)
    , settingsWindow(new PomodoroSettings(db, this)) // Pass db instead of this
    , totalTime(25 * 60)  // Default 25 minutes
    , remainingTime(totalTime)
    , isRunning(false)
    , breakTime(5 * 60) // Default break time
    , breaksPerSession(4)
    , currentBreaks(0)
    , totalSessions(5)
    , currentSessions(0)
    , isFocusTime(true)
    , soundEnabled(true)
    , timer(new QTimer(this))
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , tray(new QSystemTrayIcon(this))


{
    ui->setupUi(this);

    // 🔥 Initialize the session history table

    ui->SessionHistoryTable->setColumnCount(4);
    ui->SessionHistoryTable->setHorizontalHeaderLabels({"Start Time", "End Time", "Focus Duration", "Breaks Taken"});
    ui->SessionHistoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SessionHistoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Prevent editing rows
    ui->SessionHistoryTable->setColumnWidth(0, 150);
    ui->SessionHistoryTable->setColumnWidth(1, 150);
    ui->SessionHistoryTable->setColumnWidth(2, 100);
    ui->SessionHistoryTable->setColumnWidth(3, 100);

    updateStatistics();



    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Timer::updateTimer);
    connect(settingsWindow, &PomodoroSettings::settingsApplied, this, [this]() {
        applySettings(settingsWindow); // ✅ Pass the pointer directly
    });
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    drawCircle();

    // LCD Timer inside GraphicsView
    lcdNumber = new QLCDNumber(this);
    lcdNumber->setDigitCount(5);
    lcdNumber->setSegmentStyle(QLCDNumber::Flat); // Optional for aesthetic
    lcdNumber->setDigitCount(5); // MM:SS needs 5 digits
    lcdNumber->display(formatTime(remainingTime)); // ✅ This will display the correct format "25:00"

    lcdNumber->setParent(ui->graphicsView);
    lcdNumber->setFixedSize(100, 50);
    lcdNumber->move(110, 135);

    lcdNumber->setStyleSheet("QLCDNumber { background: transparent; color: black; border: 2px solid white; border-radius: 5px; }");

    // Connect Buttons
    connect(ui->TimerStart, &QPushButton::clicked, this, &Timer::handleStart);
    connect(ui->TimerReset, &QPushButton::clicked, this, &Timer::resetSession);
    connect(ui->TimerPause, &QPushButton::clicked, this, &Timer::handlePauseResume);

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/sounds/bell.mp3")); // Ensure this path is correct
    soundEnabled = true;

    // Initialize button states
    ui->TimerPause->setEnabled(false); // Disable Pause button initially

    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(":/icons/maverick.png")); // Replace with your app icon
    tray->show();

    setupConnections();
}

Timer::~Timer()
{
    delete ui;
}

void Timer::drawCircle()
{
    scene->clear(); // Clear previous drawings
    int sceneWidth = 320; // Example width
    int sceneHeight = 320; // Example height

    // Calculate the center position
    int centerX = (sceneWidth - 300) / 2; // 300 is the width of the outer circle
    int centerY = (sceneHeight - 300) / 2; // 300 is the height of the outer circle

    // Create a semi-transparent background circle
    QBrush backgroundBrush(QColor(230, 230, 230, 180)); // Semi-transparent color
    scene->addEllipse(centerX, centerY, 300, 300, QPen(Qt::white, 3), backgroundBrush);

    // Draw the outer circle (progress bar)
    outerCircle = scene->addEllipse(centerX, centerY, 300, 300, QPen(Qt::black, 10), QBrush(Qt::transparent));

    // Draw the inner circle (donut hole)
    int innerCircleSize = 200; // Size of the inner circle
    innerCircle = scene->addEllipse(centerX + (300 - innerCircleSize) / 2, centerY + (300 - innerCircleSize) / 2, innerCircleSize, innerCircleSize, QPen(Qt::white, 3), QBrush(Qt::white)); // White hole
    innerCircle->setZValue(1); // Ensure the inner circle is drawn on top

    // Initialize the progress circle
    progressCircle = scene->addEllipse(centerX, centerY, 300, 300, QPen(Qt::black, 10), QBrush(Qt::black)); // Change color as needed
    progressCircle->setStartAngle(90 * 16); // Start from the top
    progressCircle->setSpanAngle(0); // Initially, no progress
}

void Timer::updateCircle()
{
    double progress = 360.0 * (totalTime - remainingTime) / totalTime; // Calculate progress
    progressCircle->setSpanAngle(progress * -16); // Update the span angle for the progress circle
}

void Timer::handleStart()
{
    if (!isRunning) {
        sessionStartTime = QDateTime::currentDateTime();  // ✅ Set the start time
        lcdNumber->display(formatTime(remainingTime));
        timer->start(1000);
        isRunning = true;
        ui->TimerStart->setEnabled(false);
        ui->TimerPause->setEnabled(true);
    }
}



void Timer::handlePauseResume()
{
    if (isRunning) {
        timer->stop();
        isRunning = false;
        ui->TimerPause->setText("Resume");
    } else {
        timer->start(1000);
        isRunning = true;
        ui->TimerPause->setText("Pause");

        pauseCounter++;  // ✅ Increment pause count when resuming
        qDebug() << "Pause Count:" << pauseCounter;
    }
}


void Timer::resetSession()
{
    if (!isRunning) return;  // ✅ Prevent saving empty sessions

    QDateTime sessionEndTime = QDateTime::currentDateTime();
    int elapsedFocusTime = (sessionStartTime.secsTo(sessionEndTime) / 60);

    if (elapsedFocusTime > 0) {
        db->insertSession(sessionStartTime, sessionEndTime, elapsedFocusTime, currentBreaks, pauseCounter, "");
    }

    // ✅ Reset Timer
    timer->stop();
    isRunning = false;
    remainingTime = totalTime;
    pauseCounter = 0;
    currentBreaks = 0;
    lcdNumber->display(formatTime(remainingTime));
    drawCircle();
    ui->TimerStart->setEnabled(true);
    ui->TimerPause->setEnabled(false);

    updateStatistics();  // ✅ Now history updates after every reset!
}




void Timer::updateTimer()
{
        if (remainingTime > 0) {
            remainingTime--;
            updateCircle(); // Update donut circle
            lcdNumber->display(formatTime(remainingTime)); // Update LCD
        } else {
            timer->stop();
            player->play(); // ✅ Bell.mp3

        if (isFocusTime) {
            currentBreaks++; // Increment Break Count
            showNotification("MAVERICK", "Break Time Started!"); // 🔥 Desktop Notification

            if (currentBreaks <= breaksPerSession) {
                isFocusTime = false;
                remainingTime = breakTime;
                QMessageBox::information(this, "Break Time", "Break time started!");
                drawCircle(); // Reset Progress Bar
                timer->start(1000);
            }
            else if (currentSessions < totalSessions) {
                currentSessions++;
                currentBreaks = 0;
                isFocusTime = true;
                remainingTime = totalTime;
                showNotification("MAVERICK", "Next Session Started!"); // Desktop Notif for Next Session
                QMessageBox::information(this, "Focus Time", "Next session started!");
                drawCircle(); // Reset Progress Bar
                timer->start(1000);
            }
            else {
                showNotification("MAVERICK", "All Sessions Completed! 🎯");
                QMessageBox::information(this, "Session Complete", "All sessions completed!");
                resetSession(); // Stop and Reset Timer
            }
        }
        else { // If Break Time is Over
            isFocusTime = true;
            remainingTime = totalTime;
            showNotification("MAVERICK", "Focus Time Started!");
            QMessageBox::information(this, "Focus Time", "Focus time started!");
            drawCircle(); // Reset Progress Bar
            timer->start(1000);
        }
    }
}


QString Timer::formatTime(int seconds)
{
    int minutes = seconds / 60;
    seconds = seconds % 60;
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}


void Timer::applySettings(PomodoroSettings *settings)
{
    qDebug() << "Applying Settings";  // Debug Checkpoint

    totalTime = settings->getFocusDuration() * 60;
    breakTime = settings->getBreakDuration() * 60;
    breaksPerSession = settings->getBreaksPerSession();
    totalSessions = settings->getTotalSessions();
    soundPath = settings->getSoundPath();

    remainingTime = totalTime; // 🔑 Sync Remaining Time

    if (isRunning) {
        qDebug() << "Timer is running, stopping...";
        timer->stop();      // 💀 This is what was missing
        isRunning = false;
        ui->TimerPause->setText("Pause");
    }

    lcdNumber->display(formatTime(remainingTime));
    drawCircle(); // Reset Progress Circle
    ui->TimerStart->setEnabled(true);
    ui->TimerPause->setEnabled(false);

    if (!soundPath.isEmpty()) {
        player->setSource(QUrl::fromLocalFile(soundPath));
    }
    settings->saveSettingsToFile();
    qDebug() << "🔥 SETTINGS SYNCED FROM FILE";
    qDebug() << "Settings Applied Successfully 🔥";
}


void Timer::showNotification(const QString &title, const QString &message)
{
#ifdef Q_OS_WIN
    tray->showMessage(title, message, QSystemTrayIcon::Information, 3000); // Auto close in 3s
#endif
}

void Timer::setupConnections()
{
    connect(settingsWindow, &PomodoroSettings::settingsApplied, this, [=]() {
        qDebug() << "Settings Signal Received";  // Debug Checkpoint
        applySettings(settingsWindow);           // Sync Settings
        resetSession();                         // Force Reset 🔥
    });
}

void Timer::updateStatistics()
{
    if (!db->getDatabase().isOpen()) {
        qDebug() << "❌ ERROR: Database is not open! Attempting to reconnect...";
        if (!db->connectDatabase()) {
            qDebug() << "❌ Failed to reconnect!";
            return;
        } else {
            qDebug() << "✅ Database Reconnected!";
        }
    }

    QSqlQuery query(db->getDatabase());
    query.clear();

    // Fetch total statistics
    int totalFocus = 0, totalBreaks = 0, totalPauses = 0, totalSessions = 0;
    if (query.exec("SELECT SUM(FocusDuration), SUM(BreaksTaken), SUM(PauseCount), COUNT(*) FROM PomodoroSessions") && query.next()) {
        totalFocus = query.value(0).isNull() ? 0 : query.value(0).toInt();
        totalBreaks = query.value(1).isNull() ? 0 : query.value(1).toInt();
        totalPauses = query.value(2).isNull() ? 0 : query.value(2).toInt();
        totalSessions = query.value(3).isNull() ? 0 : query.value(3).toInt();
    } else {
        qDebug() << "❌ Failed to fetch total statistics:" << query.lastError().text();
    }
    query.finish();

    qDebug() << "🟢 Total Focus Time:" << totalFocus;
    qDebug() << "🟢 Total Breaks Taken:" << totalBreaks;
    qDebug() << "🟢 Total Pauses:" << totalPauses;
    qDebug() << "🟢 Total Sessions:" << totalSessions;

    // Fetch last 5 session history
    ui->SessionHistoryTable->clearContents();
    ui->SessionHistoryTable->setRowCount(0);

    if (!query.exec("SELECT TOP 5 StartTime, EndTime, FocusDuration, BreaksTaken FROM PomodoroSessions ORDER BY StartTime DESC")) {
        qDebug() << "❌ Failed to fetch session history:" << query.lastError().text();
    } else {
        int row = 0;
        while (query.next()) {
            QString startTime = query.value(0).toString();
            QString endTime = query.value(1).toString();
            QString focusDuration = query.value(2).isNull() ? "0" : QString::number(query.value(2).toInt());
            QString breaks = query.value(3).isNull() ? "0" : QString::number(query.value(3).toInt());

            ui->SessionHistoryTable->insertRow(row);
            ui->SessionHistoryTable->setItem(row, 0, new QTableWidgetItem(startTime));
            ui->SessionHistoryTable->setItem(row, 1, new QTableWidgetItem(endTime));
            ui->SessionHistoryTable->setItem(row, 2, new QTableWidgetItem(focusDuration));
            ui->SessionHistoryTable->setItem(row, 3, new QTableWidgetItem(breaks));

            row++;
        }
    }

    // Format Statistics in HTML
    QString statsText = QString(
                            "<h2><b>🔥 Pomodoro Statistics 🔥</b></h2>"
                            "<p><b>🕒 Total Focus Time:</b> %1 minutes</p>"
                            "<p><b>☕ Total Breaks Taken:</b> %2</p>"
                            "<p><b>⏸️ Total Pauses:</b> %3</p>"
                            "<p><b>📅 Total Sessions Completed:</b> %4</p><br>"
                            ).arg(QString::number(totalFocus),
                                 QString::number(totalBreaks),
                                 QString::number(totalPauses),
                                 QString::number(totalSessions));

    // Append session history
    statsText += "<h3><b>📜 Recent Pomodoro Sessions 📜</b></h3><br>";

    if (!query.exec("SELECT TOP 5 StartTime, EndTime, FocusDuration, BreaksTaken FROM PomodoroSessions ORDER BY StartTime DESC")) {
        qDebug() << "❌ Failed to fetch session history:" << query.lastError().text();
    } else {
        while (query.next()) {
            statsText += QString(
                             "<p><b>📌 Start:</b> %1</p>"
                             "<p><b>⏳ End:</b> %2</p>"
                             "<p><b>🕒 Focus:</b> %3 min</p>"
                             "<p><b>☕ Breaks:</b> %4</p><br>"
                             ).arg(query.value(0).toString(),
                                  query.value(1).toString(),
                                  query.value(2).isNull() ? "0" : query.value(2).toString(),
                                  query.value(3).isNull() ? "0" : query.value(3).toString());
        }
    }
    // Update QTextEdit with HTML formatting
    if (ui->PomodoroStats) {
        ui->PomodoroStats->setHtml(statsText);
    }

    qDebug() << "✅ Statistics & Session Table Updated!";
}
