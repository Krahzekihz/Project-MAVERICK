#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QWidget>
#include "taskdata.h"
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class TaskManager; }
QT_END_NAMESPACE

class TaskManager : public QWidget {
    Q_OBJECT

public:
    explicit TaskManager(QWidget *parent = nullptr);
    ~TaskManager();

private slots:
    void addTask();
    void removeTask();
    void updateDateLabel();

private:
    Ui::TaskManager *ui;
    QList<TaskData> taskList;
};

#endif // TASKMANAGER_H
