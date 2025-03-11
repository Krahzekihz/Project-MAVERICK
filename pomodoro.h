#ifndef POMODORO_H
#define POMODORO_H

#include <QWidget>
#include "timer.h"
#include "stopwatch.h"
#include "notes.h"

namespace Ui {
class Pomodoro;
}

class Pomodoro : public QWidget
{
    Q_OBJECT

public:
    explicit Pomodoro(QWidget *parent = nullptr);
    ~Pomodoro();
    PomodoroSettings *settingsWindow;  // Expose Settings Window
    Timer *timer;                     // Expose Timer



private slots:
    void openSettings(); // Slot to open the settings dialog

private:
    Ui::Pomodoro *ui;

    Timer *timerUI;        // Timer Tab
    Stopwatch *stopwatchUI; // Stopwatch Tab
    Notes *notesWidget;     // Notes Widget
};

#endif // POMODORO_H
