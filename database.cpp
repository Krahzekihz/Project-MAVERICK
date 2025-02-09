#include "database.h"
#include <QtSql/QSqlDatabase>  // Ensure full path is used
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

Database::Database(QObject* parent) : QObject(parent) {}

bool Database::connectToDatabase(const QString& dbPath) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=" + dbPath);

    if (!db.open()) {
        qDebug() << "Error: Unable to connect to the database" << db.lastError();
        return false;
    }
    qDebug() << "Connected to database!";
    return true;
}
