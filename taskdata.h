#ifndef TASKDATA_H
#define TASKDATA_H

#include <QString>
#include <QDate>

class TaskData {
public:
    TaskData(const QDate &date, const QString &name, const QString &due);

    QString getTaskName() const;
    QDate getTaskDate() const;
    QString getDueDetails() const;

private:
    QDate taskDate;
    QString taskName;
    QString dueDetails;
};

#endif // TASKDATA_H
