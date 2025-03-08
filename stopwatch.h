#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QLCDNumber> // Include for digital clock display

namespace Ui {
class Stopwatch;
}

class Stopwatch : public QWidget {
    Q_OBJECT

public:
    explicit Stopwatch(QWidget *parent = nullptr);
    ~Stopwatch();

private slots:
    void updateClock(); // Slot to update the clock every second
    void startStopwatch(); // Start the stopwatch
    void pauseStopwatch(); // Pause the stopwatch
    void resetStopwatch(); // Reset the stopwatch

private:
    void drawClock(); // Method to draw the clock face
    void drawSecondsHand(int seconds); // Method to draw the seconds hand
    QString formatTime(int seconds); // Method to format elapsed time

    Ui::Stopwatch *ui; // Pointer to the UI
    QGraphicsScene *scene; // Scene to hold the clock elements
    QTimer *timer; // Timer to update the clock
    int elapsedSeconds; // Elapsed seconds for the stopwatch
    QLCDNumber *lcdDisplay; // Digital clock display
};

#endif // STOPWATCH_H
