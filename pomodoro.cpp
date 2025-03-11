#include "pomodoro.h"
#include "ui_pomodoro.h"
#include "timer.h"
#include "stopwatch.h"
#include "notes.h"
#include "pomodorosettings.h"

#include <QVBoxLayout> // Include this for QVBoxLayout

Pomodoro::Pomodoro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Pomodoro)
{
    ui->setupUi(this);

    // Remove extra tabs (Tab 1 and Tab 2)
    ui->tabWidget->removeTab(0); // Removes the first tab
    ui->tabWidget->removeTab(0); // Removes the second tab (index shifts after removal)


    // Instantiate Timer and Stopwatch UIs
    timerUI = new Timer(this);
    stopwatchUI = new Stopwatch(this);
    notesWidget = new Notes(this);

    // Add Timer to the first tab
    ui->tabWidget->addTab(timerUI, "Timer");

    // Add Stopwatch to the second tab
    ui->tabWidget->addTab(stopwatchUI, "Stopwatch");

    // Create a layout for NotesWidget before adding Notes widget
    QVBoxLayout *notesLayout = new QVBoxLayout();
    ui->NotesWidget->setLayout(notesLayout);
    notesLayout->addWidget(notesWidget);



    // Connect the Settings button to open the settings window
    connect(ui->PomodoroSettings, &QToolButton::clicked, this, &Pomodoro::openSettings);


}

Pomodoro::~Pomodoro()
{
    delete ui;
}

void Pomodoro::openSettings()
{
    PomodoroSettings settingsDialog(this);
    settingsDialog.exec();
}
