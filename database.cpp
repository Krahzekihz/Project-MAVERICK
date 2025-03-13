#include "database.h"
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>

Database::Database(QObject *parent) : QObject(parent) {}

bool Database::connectDatabase()
{
    // ✅ Ensure we're not creating duplicate connections
    if (QSqlDatabase::contains("PomodoroDB")) {
        db = QSqlDatabase::database("PomodoroDB");  // 🔥 Use existing connection
        if (db.isOpen()) {
            qDebug() << "✅ Database already connected!";
            return true;
        }
    } else {
        db = QSqlDatabase::addDatabase("QODBC", "PomodoroDB");  // ✅ Unique connection name
    }

    QString dbPath = QDir::currentPath() + "/FormFiles/Database1.accdb";
    qDebug() << "Database path:" << dbPath;

    if (!QFile::exists(dbPath)) {
        qDebug() << "❌ Database file NOT FOUND at:" << dbPath;
        return false;
    }

    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=" + dbPath + ";");

    if (!db.open()) {
        qDebug() << "❌ Database Connection Failed:" << db.lastError().text();
        return false;
    }

    qDebug() << "✅ Database Connected Successfully";
    createPomodoroTable();  // Ensure table exists
    return true;
}


void Database::createPomodoroTable()
{
    QSqlQuery query(db);

    // ✅ Check if PomodoroSessions table exists
    query.exec("SELECT 1 FROM PomodoroSessions");
    if (query.lastError().type() == QSqlError::StatementError) {
        qDebug() << "⚠️ PomodoroSessions table does NOT exist. Creating...";
        if (!query.exec("CREATE TABLE PomodoroSessions ("
                        "ID AUTOINCREMENT PRIMARY KEY, "
                        "StartTime DATETIME, "
                        "EndTime DATETIME, "
                        "FocusDuration INTEGER, "
                        "BreaksTaken INTEGER, "
                        "PauseCount INTEGER)")) {
            qDebug() << "❌ Failed to create PomodoroSessions:" << query.lastError().text();
        } else {
            qDebug() << "✅ PomodoroSessions table created successfully!";
        }
    }

    // ✅ Check if PomodoroHistory table exists
    query.exec("SELECT 1 FROM PomodoroHistory");
    if (query.lastError().type() == QSqlError::StatementError) {
        qDebug() << "⚠️ PomodoroHistory table does NOT exist. Creating...";
        if (!query.exec("CREATE TABLE PomodoroHistory ("
                        "ID AUTOINCREMENT PRIMARY KEY, "
                        "SessionID INTEGER, "
                        "StartTime DATETIME, "
                        "EndTime DATETIME, "
                        "FocusDuration INTEGER, "
                        "BreaksTaken INTEGER, "
                        "PauseCount INTEGER, "
                        "FOREIGN KEY(SessionID) REFERENCES PomodoroSessions(ID))")) {
            qDebug() << "❌ Failed to create PomodoroHistory:" << query.lastError().text();
        } else {
            qDebug() << "✅ PomodoroHistory table created successfully!";
        }
    }
}

bool Database::insertSession(const QDateTime &start, const QDateTime &end, int focusDuration, int breaks, int pauseCount, const QString &notes)
{
    QSqlQuery query(db);

    query.prepare("INSERT INTO PomodoroSessions (StartTime, EndTime, FocusDuration, BreaksTaken, PauseCount, Notes) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(start);
    query.addBindValue(end);
    query.addBindValue(focusDuration);
    query.addBindValue(breaks);
    query.addBindValue(pauseCount);
    query.addBindValue(notes);  // ✅ Now it properly stores notes

    if (!query.exec()) {
        qDebug() << "❌ Insert into PomodoroSessions Failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Session successfully saved!";
    return true;
}


QSqlDatabase Database::getDatabase()
{
    if (!db.isOpen()) {  // 🔥 Ensure the database is open before returning it
        qDebug() << "❌ ERROR: Database is not open! Attempting to reconnect...";
        connectDatabase();  // Try reconnecting
    }
    return db;
}

void Database::eraseDatabase()
{
    if (db.isOpen()) {
        qDebug() << "⚠️ Closing database before deletion...";
        db.close();  // ✅ Close the database first
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);  // ✅ Remove connection
    }

    QString dbPath = QDir::currentPath() + "/FormFiles/Database1.accdb";

    if (QFile::exists(dbPath)) {
        if (QFile::remove(dbPath)) {
            qDebug() << "✅ Database erased successfully!";
        } else {
            qDebug() << "❌ Failed to erase database! File might be in use.";
        }
    } else {
        qDebug() << "⚠️ Database file does not exist.";
    }
}
