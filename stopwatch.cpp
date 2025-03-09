#include "stopwatch.h"
#include "ui_stopwatch.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>

Stopwatch::Stopwatch(QWidget *parent)
    : QWidget(parent), elapsedSeconds(0), ui(new Ui::Stopwatch) {
    ui->setupUi(this); // Set up the UI

    // Create the graphics scene for the clock
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene); // Assuming you have a QGraphicsView named graphicsView in your UI

    // Create the digital clock display
    lcdDisplay = new QLCDNumber(this);
    lcdDisplay->setDigitCount(8); // HH:MM:SS
    lcdDisplay->setStyleSheet("QLCDNumber { background: transparent; color: black; border: 2px solid white; border-radius: 5px; }");
    lcdDisplay->setFixedSize(100, 50);
    lcdDisplay->move(110, 135); // Adjust position as needed
    lcdDisplay->setParent(ui->graphicsView); // Set parent to graphicsView

    // Set up the timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::updateClock);

    // Connect buttons to their respective slots
    connect(ui->StopwatchStart, &QPushButton::clicked, this, &Stopwatch::startStopwatch);
    connect(ui->StopwatchPause, &QPushButton::clicked, this, &Stopwatch::pauseStopwatch);
    connect(ui->StopwatchReset, &QPushButton::clicked, this, &Stopwatch::resetStopwatch);

    drawClock(); // Initial drawing of the clock
}

Stopwatch::~Stopwatch() {
    delete ui;
}

void Stopwatch::drawClock() {
    scene->clear(); // Clear previous drawings

    // Draw clock face
    int clockDiameter = 300;
    int clockX = 10; // X position of the clock face
    int clockY = 10; // Y position of the clock face
    scene->addEllipse(clockX, clockY, clockDiameter, clockDiameter, QPen(Qt::black), QBrush(Qt::white));

    // Calculate the center of the clock face
    int centerX = clockX + clockDiameter / 2;
    int centerY = clockY + clockDiameter / 2;

    // Draw lines for numbers (every 5 seconds)
    for (int i = 0; i < 60; ++i) {
        double angle = i * 6.0; // 360 degrees / 60 lines
        double rad = qDegreesToRadians(angle);
        double x1 = centerX + 140 * qCos(rad); // Outer point
        double y1 = centerY + 140 * qSin(rad); // Outer point
        double x2 = centerX + 120 * qCos(rad); // Inner point
        double y2 = centerY + 120 * qSin(rad); // Inner point
        scene->addLine(x1, y1, x2, y2, QPen(Qt::black));
    }
}

void Stopwatch::updateClock() {
    elapsedSeconds++; // Increment elapsed seconds
    drawClock(); // Redraw the clock face
    drawSecondsHand(elapsedSeconds); // Draw the seconds hand
    lcdDisplay->display(formatTime(elapsedSeconds)); // Update the digital clock display
}

void Stopwatch::drawSecondsHand(int seconds) {
    // Calculate the center of the clock face
    int clockDiameter = 300;
    int clockX = 10; // X position of the clock face
    int clockY = 10; // Y position of the clock face
    int centerX = clockX + clockDiameter / 2; // Center X
    int centerY = clockY + clockDiameter / 2; // Center Y

    double secondsAngle = (seconds % 60) * 6.0; // 360 degrees / 60 seconds
    double rad = qDegreesToRadians(secondsAngle);
    double x = centerX + 100 * qCos(rad); // Calculate the end point of the seconds hand
    double y = centerY + 100 * qSin(rad); // Calculate the end point of the seconds hand

    // Clear previous seconds hand before drawing the new one
    scene->addLine(centerX, centerY, x, y, QPen(Qt::red, 2)); // Red seconds hand
}

QString Stopwatch::formatTime(int seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;
    return QString("%1:%2:%3")
        .arg(hours, 2, 10, QChar('0'))
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0')); // Format as HH:MM:SS
}

void Stopwatch::startStopwatch() {
    timer->start(1000); // Start the timer to update every second
}

void Stopwatch::pauseStopwatch() {
    timer->stop(); // Stop the timer
}

void Stopwatch::resetStopwatch() {
    timer->stop(); // Stop the timer
    elapsedSeconds = 0; // Reset elapsed seconds
    drawClock(); // Redraw the clock face
    drawSecondsHand(elapsedSeconds); // Reset the seconds hand
    lcdDisplay->display(formatTime(elapsedSeconds)); // Reset the digital clock display
}
