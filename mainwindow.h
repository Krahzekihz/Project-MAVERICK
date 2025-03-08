#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "eisenhower.h"  // Include Eisenhower Matrix
#include "pomodoro.h"    // Include Pomodoro if needed

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    Eisenhower *eisenhowerMatrix;  // Pointer to Eisenhower Matrix
    Pomodoro *pomodoroTimer;       // Pointer to Pomodoro

    void setupTabs();  // Function to configure tabs
};

#endif // MAINWINDOW_H
