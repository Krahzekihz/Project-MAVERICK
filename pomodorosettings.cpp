#include "pomodorosettings.h"
#include "timer.h"
#include "ui_pomodorosettings.h"
#include <QMessageBox>
#include <QFileDialog>
#include <Qtsql/QSqlQuery>
#include <Qtsql/QSqlError>

PomodoroSettings::PomodoroSettings(Database *database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PomodoroSettings)
    , db(database)  // ✅ Store database reference
{
    ui->setupUi(this);

    focusDuration = ui->focusDuration;
    breakDuration = ui->breakDuration;
    breaksPerSession = ui->breaksPerSession;
    totalSessions = ui->totalSessions;
    soundUpload = ui->soundUpload;
    saveButton = ui->saveButton;
    loadSettingsFromFile();
    connect(soundUpload, &QPushButton::clicked, this, &PomodoroSettings::selectSound);
    connect(saveButton, &QPushButton::clicked, this, &PomodoroSettings::saveSettings);
    connect(ui->ResetDatabaseButton, &QPushButton::clicked, this, &PomodoroSettings::resetDatabase);
    connect(ui->ResetDefaultsButton, &QPushButton::clicked, this, &PomodoroSettings::resetToDefault);


    connect(saveButton, &QPushButton::clicked, this, [=]() {
        saveSettingsToFile();       // Save the settings
        emit settingsApplied();     // Fire the Signal
        qDebug() << "🔥 SETTINGS APPLIED FROM SAVE BUTTON";
        accept();                  // Close the Window
    });
}


PomodoroSettings::~PomodoroSettings()
{
    delete ui;
}

void PomodoroSettings::selectSound()
{
    soundPath = QFileDialog::getOpenFileName(this, "Select Sound", "", "MP3 Files (*.mp3)");
    if (!soundPath.isEmpty()) {
        QMessageBox::information(this, "Sound Selected", "Sound uploaded successfully!");
    }
}

void PomodoroSettings::saveSettings()
{
    // Optionally validate the settings here

    qDebug() << "Focus Duration:" << focusDuration->value();
    qDebug() << "Break Time:" << breakDuration->value();
    qDebug() << "Breaks Per Session:" << breaksPerSession->value();
    qDebug() << "Total Sessions:" << totalSessions->value();

    if (focusDuration->value() <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Focus time must be greater than zero!");
        return;
    }
    QMessageBox::information(this, "Settings Saved", "Your Pomodoro settings have been saved.");
    emit settingsApplied();
    parent()->findChild<Timer*>()->applySettings(this);    // Notify Timer that settings are updated
    accept(); // Close the dialog
}

#include <QSettings>

void PomodoroSettings::saveSettingsToFile()
{
    QSettings settings("MAVERICK", "Pomodoro");
    settings.setValue("FocusDuration", focusDuration->value());
    settings.setValue("BreakDuration", breakDuration->value());
    settings.setValue("BreaksPerSession", breaksPerSession->value());
    settings.setValue("TotalSessions", totalSessions->value());
    settings.setValue("SoundPath", soundPath);

    qDebug() << " SETTINGS SAVED TO INI FILE";
}

void PomodoroSettings::loadSettingsFromFile()
{
    QSettings settings("MAVERICK", "Pomodoro");
    focusDuration->setValue(settings.value("FocusDuration", 25).toInt());
    breakDuration->setValue(settings.value("BreakDuration", 5).toInt());
    breaksPerSession->setValue(settings.value("BreaksPerSession", 4).toInt());
    totalSessions->setValue(settings.value("TotalSessions", 5).toInt());
    soundPath = settings.value("SoundPath", "").toString();

    qDebug() << " SETTINGS LOADED FROM INI FILE";
}


int PomodoroSettings::getFocusDuration() const { return focusDuration->value(); }
int PomodoroSettings::getBreakDuration() const { return breakDuration->value(); }
int PomodoroSettings::getBreaksPerSession() const { return breaksPerSession->value(); }
int PomodoroSettings::getTotalSessions() const { return totalSessions->value(); }
QString PomodoroSettings::getSoundPath() const { return soundPath; }


void PomodoroSettings::resetDatabase()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Reset Database",
                                  "Are you sure you want to erase all Pomodoro data?\n\n"
                                  "⚠️ *Note:* You need to restart the program for changes to take effect.",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (!db->getDatabase().isOpen()) {  // ✅ Use 'db->' since it's a pointer
            QMessageBox::critical(this, "Error",
                                  "Database is not open! Attempting to reconnect...");

            if (!db->connectDatabase()) {
                QMessageBox::critical(this, "Error",
                                      "Failed to reconnect to the database!");
                return;
            }
        }

        QSqlQuery query(db->getDatabase());  // ✅ Use 'db->' correctly

        if (query.exec("DELETE FROM PomodoroSessions")) {
            QMessageBox::information(this, "Success",
                                     "All Pomodoro session data has been erased.\n\n"
                                     "⚠️ Please restart the application to refresh the database.");
        } else {
            QMessageBox::critical(this, "Error",
                                  "Failed to reset database: " + query.lastError().text());
        }
    }
}

void PomodoroSettings::resetToDefault()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Reset to Default",
                                  "Are you sure you want to reset Pomodoro settings to default?\n"
                                  "This will reset focus time, break time, and session counts.",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 🔥 Reset values to default
        focusDuration->setValue(25);
        breakDuration->setValue(5);
        breaksPerSession->setValue(4);
        totalSessions->setValue(5);
        soundPath = "";  // Clear custom sound

        // 🔥 Save to INI file
        saveSettingsToFile();

        QMessageBox::information(this, "Settings Reset",
                                 "Pomodoro settings have been restored to default values.");
    }
}
