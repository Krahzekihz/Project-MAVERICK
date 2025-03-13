#ifndef TIMER_H
#define TIMER_H

#include "database.h"
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
#include <QTableWidget>
#include <QTextEdit>
#include <QDateTime> // Include QDateTime for sessionStartTime

namespace Ui {
class Timer;
}

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(Database *database, QWidget *parent = nullptr);
    ~Timer();
    void applySettings(PomodoroSettings *settings);
    void resetSession();

private slots:
    void handleStart();
    void handlePauseResume();
    void updateTimer();
    void updateStatistics();  // 🔥 Fetch statistics from DB

private:
    Ui::Timer *ui;  // ✅ UI Pointer
    Database *db;   // ✅ Move db above settingsWindow
    PomodoroSettings *settingsWindow;  // ✅ Settings Window

    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *circle;
    QGraphicsEllipseItem *outerCircle;
    QGraphicsEllipseItem *innerCircle;
    QGraphicsEllipseItem *progressCircle;
    QLCDNumber *lcdNumber;

    int totalTime;           // Total time for the session
    int remainingTime;       // Remaining time
    bool isRunning;
    int breakTime;           // Break Time in Seconds
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

    QDateTime sessionStartTime;  // ✅ Store session start time
    int pauseCounter;  // ✅ Track pauses

    // Declare formatTime function
    QString formatTime(int seconds); // Add this line
};

#endif // TIMER_H
