#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>  // Ensure full path is used
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

class Database : public QObject {
    Q_OBJECT
public:
    explicit Database(QObject* parent = nullptr);
    bool connectToDatabase(const QString& dbPath);
};

#endif // DATABASE_H
