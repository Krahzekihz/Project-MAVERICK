#ifndef POMODORO_H
#define POMODORO_H

#include <QWidget>
#include "database.h"
#include "timer.h"
#include "stopwatch.h"
#include "notes.h"
#include "pomodorosettings.h"

namespace Ui {
class Pomodoro;
}

class Pomodoro : public QWidget
{
    Q_OBJECT

public:
    explicit Pomodoro(Database *database, QWidget *parent = nullptr); // Ensure this line exists
    ~Pomodoro();

private slots:
    void openSettings();

private:
    Ui::Pomodoro *ui;
    Database *db; // Database reference
    Timer *timerUI; // Timer UI
    Stopwatch *stopwatchUI; // Stopwatch UI
    Notes *notesWidget; // Notes widget
    PomodoroSettings *settingsWindow; // Settings window
};

#endif // POMODORO_H
