#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

#include "taskmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSaveTaskClicked();
    void onViewTaskClicked();
    void updateCurrentDateLabel();

private:
    Ui::MainWindow *ui;
    TaskManager taskManager;

    void connectSignals();
};
#endif // MAINWINDOW_H
