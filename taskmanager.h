#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QVariantList>

class TaskManager : public QObject {
    Q_OBJECT
public:
    explicit TaskManager(QObject* parent = nullptr);

    Q_INVOKABLE QVariantList fetchTasks();
    Q_INVOKABLE void addTask(const QString& taskName, const QString& tags, const QString& dueDate);
    Q_INVOKABLE void exportTasksToTxt();
};

#endif // TASKMANAGER_H
