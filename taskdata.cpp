#include "taskdata.h"

TaskData::TaskData(const QDate &date, const QString &name, const QString &due)
    : taskDate(date), taskName(name), dueDetails(due) {}

QString TaskData::getTaskName() const {
    return taskName;
}

QDate TaskData::getTaskDate() const {
    return taskDate;
}

QString TaskData::getDueDetails() const {
    return dueDetails;
}
