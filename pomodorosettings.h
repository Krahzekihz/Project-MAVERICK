#ifndef POMODOROSETTINGS_H
#define POMODOROSETTINGS_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QFormLayout>

namespace Ui {
class PomodoroSettings;
}

class PomodoroSettings : public QDialog
{
    Q_OBJECT

public:
    explicit PomodoroSettings(QWidget *parent = nullptr);
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

private:
    Ui::PomodoroSettings *ui;

    QSpinBox *focusDuration;
    QSpinBox *breakDuration;
    QSpinBox *breaksPerSession;
    QSpinBox *totalSessions;
    QPushButton *soundUpload;
    QPushButton *saveButton;


    QString soundPath;
signals:
    void settingsApplied(); // ✅ This emits the signal when settings are applied

};

#endif // POMODOROSETTINGS_H
