#ifndef TIMER_H
#define TIMER_H

#include "pomodorosettings.h"
#include <QWidget>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QLCDNumber>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QApplication>

namespace Ui {
class Timer;
}

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();
    void applySettings(PomodoroSettings *settings);
    void resetSession();


private slots:
    void handleStart();

    void handlePauseResume();
    void updateTimer();

private:
    QString formatTime(int seconds); // Declare formatTime here

    Ui::Timer *ui;

    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *circle;
    QGraphicsEllipseItem *outerCircle; // To hold the outer circle
    QGraphicsEllipseItem *innerCircle; // To hold the inner circle'
    QGraphicsEllipseItem *progressCircle;
    QLCDNumber *lcdNumber;

    int totalTime;           // Total time for the session
    int remainingTime;       // Remaining time
    bool isRunning;
    int breakTime;  // Break Time in Seconds
    int breaksPerSession;
    int currentBreaks;
    int totalSessions;
    int currentSessions;
    QString soundPath;

    bool isFocusTime;

    void drawCircle();
    void updateCircle();
    void setupConnections();

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    bool soundEnabled;

    QSystemTrayIcon *tray;
    void showNotification(const QString &title, const QString &message);

    PomodoroSettings *settingsWindow; // Declare the settings window pointer

};

#endif // TIMER_H
