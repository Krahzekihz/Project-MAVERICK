#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);

    bool connectDatabase();
    void createPomodoroTable();  // ✅ Ensures table exists
    bool insertSession(const QDateTime &start, const QDateTime &end, int focusDuration, int breaks, int pauseCount, const QString &notes);
    void eraseDatabase();  // ✅ Declare function in the header file

    QSqlDatabase getDatabase();  // Optional getter if needed

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
