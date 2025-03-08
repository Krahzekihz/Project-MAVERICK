#ifndef EISENHOWER_H
#define EISENHOWER_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QColor>

class Eisenhower : public QObject {
    Q_OBJECT

public:
    enum Quadrant { UrgentImportant, NotUrgentImportant, UrgentNotImportant, NotUrgentNotImportant };
    explicit Eisenhower(QObject *parent = nullptr);

    void addTask(const QString &task, Quadrant quadrant);
    void removeTask(const QString &task, Quadrant quadrant);
    QStringList getTasks(Quadrant quadrant) const;

    void setQuadrantColor(Quadrant quadrant, const QColor &color);
    QColor getQuadrantColor(Quadrant quadrant) const;

    void filterTasks(const QString &query);
    void sortTasks(Quadrant quadrant, bool alphabetical);

private:
    QMap<Quadrant, QStringList> tasks;
    QMap<Quadrant, QColor> quadrantColors;
};

#endif // EISENHOWER_H
