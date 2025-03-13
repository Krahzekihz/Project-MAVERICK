#ifndef POMODOROSETTINGS_H
#define POMODOROSETTINGS_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QFormLayout>
#include "database.h"  // ✅ Include database header


namespace Ui {
class PomodoroSettings;
}

class PomodoroSettings : public QDialog
{
    Q_OBJECT

public:
    explicit PomodoroSettings(Database *database, QWidget *parent = nullptr);  // ✅ Pass Database
    ~PomodoroSettings();
    int getFocusDuration() const;
    int getBreakDuration() const;
    int getBreaksPerSession() const;
    int getTotalSessions() const;
    QString getSoundPath() const;

public slots:
    void saveSettings();
    void saveSettingsToFile();
    void loadSettingsFromFile();

private slots:
    void selectSound();
    void resetDatabase();  // 🔥 New function to erase Pomodoro data
    void resetToDefault();
private:
    Ui::PomodoroSettings *ui;

    QSpinBox *focusDuration;
    QSpinBox *breakDuration;
    QSpinBox *breaksPerSession;
    QSpinBox *totalSessions;
    QPushButton *soundUpload;
    QPushButton *saveButton;
    Database *db;

    QString soundPath;
signals:
    void settingsApplied(); // ✅ This emits the signal when settings are applied

};

#endif // POMODOROSETTINGS_H
