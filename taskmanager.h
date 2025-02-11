#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtWidgets/QFileDialog>
#include <QDebug>
#include <QVariantList>

class TaskManager : public QObject {
    Q_OBJECT

public:
    explicit TaskManager(QObject* parent = nullptr);

public slots:
    void openDatabase(const QString& filePath);

private:
    void setupDatabase(const QString& dbPath);
    QSqlDatabase db;
signals:
    void databaseConnected();

};

#endif // TASKMANAGER_H