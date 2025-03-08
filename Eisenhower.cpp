#include "eisenhower.h"

Eisenhower::Eisenhower(QObject *parent) : QObject(parent) {}

void Eisenhower::addTask(const QString &task, Quadrant quadrant) {
    tasks[quadrant].append(task);
}

void Eisenhower::removeTask(const QString &task, Quadrant quadrant) {
    tasks[quadrant].removeAll(task);
}

QStringList Eisenhower::getTasks(Quadrant quadrant) const {
    return tasks.value(quadrant);
}

void Eisenhower::setQuadrantColor(Quadrant quadrant, const QColor &color) {
    quadrantColors[quadrant] = color;
}

QColor Eisenhower::getQuadrantColor(Quadrant quadrant) const {
    return quadrantColors.value(quadrant, QColor(Qt::white));
}

void Eisenhower::filterTasks(const QString &query) {
    for (auto &list : tasks) {
        for (auto &task : list) {
            if (!task.contains(query, Qt::CaseInsensitive)) {
                list.removeAll(task);
            }
        }
    }
}

void Eisenhower::sortTasks(Quadrant quadrant, bool alphabetical) {
    if (alphabetical) {
        std::sort(tasks[quadrant].begin(), tasks[quadrant].end());
    }
}
