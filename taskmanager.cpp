#include "taskmanager.h"
#include <QDateTime>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtWidgets/QFileDialog>

TaskManager::TaskManager(QObject* parent) : QObject(parent) {
    qDebug() << "TaskManager initialized";
}

void TaskManager::openDatabase(const QString& filePath) {
    qDebug() << "Dropped file: " << filePath;

    if (!filePath.endsWith(".accdb")) {
        qDebug() << "Invalid file type!";
        return;
    }

    setupDatabase(filePath);
}

void TaskManager::setupDatabase(const QString& dbPath) {
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Database error: " << db.lastError().text();
    }
    else {
        qDebug() << "Database connected successfully!";
        emit databaseConnected();
    }
}