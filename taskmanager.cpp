#include "taskmanager.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

TaskManager::TaskManager(QObject* parent) : QObject(parent) {}

// Dummy function to fetch tasks
QVariantList TaskManager::fetchTasks() {
    QVariantList taskList;
    QVariantMap task;
    task["taskName"] = "Test Task";
    task["tags"] = "Sample";
    task["dueDate"] = "2025-02-15";
    taskList.append(task);
    return taskList;
}

// Dummy function to add a task
void TaskManager::addTask(const QString& taskName, const QString& tags, const QString& dueDate) {
    qDebug() << "Task Added:" << taskName << tags << dueDate;
}

// Dummy function to export tasks
void TaskManager::exportTasksToTxt() {
    QFile file("tasks.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Sample Task, Sample Tag, 2025-02-15\n";
        file.close();
        qDebug() << "Tasks exported successfully!";
    }
}
