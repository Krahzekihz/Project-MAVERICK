#ifndef TASK_H
#define TASK_H

#include <QString>

class Task {
public:
    int id;
    QString taskName;
    QString status; // "Ongoing", "Hidden", "Completed"
    QString createdAt;
    QString dueDate;
    QString tags;
    int reminderTime; // Time before due date in minutes

    Task(int id, const QString& taskName, const QString& status, const QString& createdAt,
        const QString& dueDate, const QString& tags, int reminderTime)
        : id(id), taskName(taskName), status(status), createdAt(createdAt),
        dueDate(dueDate), tags(tags), reminderTime(reminderTime) {}
};

#endif // TASK_H
