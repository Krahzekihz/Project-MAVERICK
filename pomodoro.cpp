#include "pomodoro.h"
#include "ui_pomodoro.h"
#include <QVBoxLayout>

Pomodoro::Pomodoro(Database *database, QWidget *parent) // Accept Database pointer
    : QWidget(parent)
    , ui(new Ui::Pomodoro)
    , db(database)  // Store the database reference
    , timerUI(new Timer(db, this))  // Pass database correctly
{
    ui->setupUi(this);

    // Remove extra tabs (Tab 1 and Tab 2)
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

    // Connect to Database
    if (!db->connectDatabase()) {
        qDebug() << "❌ Failed to connect to database!";
    }

    // Instantiate Stopwatch and Notes UIs
    stopwatchUI = new Stopwatch(this);
    notesWidget = new Notes(this);

    // Add Timer to the first tab
    ui->tabWidget->addTab(timerUI, "Timer");

    // Add Stopwatch to the second tab
    ui->tabWidget->addTab(stopwatchUI, "Stopwatch");

    // Set up Notes widget
    QVBoxLayout *notesLayout = new QVBoxLayout();
    ui->NotesWidget->setLayout(notesLayout);
    notesLayout->addWidget(notesWidget);

    // Connect Settings button
    connect(ui->PomodoroSettings, &QToolButton::clicked, this, &Pomodoro::openSettings);
}

Pomodoro::~Pomodoro()
{
    delete ui;
    // Do not delete db here if it's managed elsewhere
}

void Pomodoro::openSettings()
{
    settingsWindow = new PomodoroSettings(db, this);  // Pass Database only when needed
    settingsWindow->exec();
}
