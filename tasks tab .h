// tasks_tab.h

#ifndef TASKS_TAB_H
#define TASKS_TAB_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QTimer>
#include <QSystemTrayIcon>

class TasksTab : public QWidget {
    Q_OBJECT

public:
    TasksTab(QWidget *parent = nullptr);
    void setTrayIcon(QSystemTrayIcon* tray);

private slots:
    void addTask();
    void editReminderTime(QListWidgetItem *item);
    void checkReminders();

private:
    void setupUI();
    void setupDatabase();
    void loadTasks();
    void showNotification(const QString &task);
    void deleteTask(const QString &task);
    void startTimer();

    QListWidget *taskListWidget;
    QLineEdit *taskLineEdit;
    QPushButton *addButton;
    QSqlDatabase db;
    QTimer *timer;
    QSystemTrayIcon *trayIcon = nullptr;
};

#endif // TASKS_TAB_H
