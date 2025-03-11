#include "timer.h"
#include "ui_timer.h"
#include "pomodorosettings.h"  // This one is crucial 🔥
#include <QMessageBox>

Timer::Timer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timer)
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
    , settingsWindow(new PomodoroSettings(this))
{
    ui->setupUi(this);



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
        lcdNumber->display(formatTime(remainingTime));       // Refresh LCD with new time
        timer->start(1000);
        isRunning = true;
        ui->TimerStart->setEnabled(false);
        ui->TimerPause->setEnabled(true);
    }
}



void Timer::handlePauseResume()
{
    if (isRunning) {
        timer->stop(); // Pause the timer
        isRunning = false;
        ui->TimerPause->setText("Resume"); // Change the button text to "Resume"
    } else {
        timer->start(1000); // Resume the timer
        isRunning = true;
        ui->TimerPause->setText("Pause"); // Change the button text back to "Pause"
    }
}

void Timer::resetSession()
{
    timer->stop(); // Stop the timer
    isRunning = false;
    remainingTime = totalTime; // Reset remaining time to the default
    lcdNumber->display(formatTime(remainingTime)); // Reset display to the default time
    drawCircle(); // Redraw the circle
    ui->TimerStart->setEnabled(true); // Enable the Start button
    ui->TimerPause->setEnabled(false); // Disable the Pause button
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



