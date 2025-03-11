#include "pomodorosettings.h"
#include "timer.h"
#include "ui_pomodorosettings.h"
#include <QMessageBox>
#include <QFileDialog>

PomodoroSettings::PomodoroSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PomodoroSettings)
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
