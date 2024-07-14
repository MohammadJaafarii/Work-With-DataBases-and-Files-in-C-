#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class DatabaseManager
{

public:
    DatabaseManager();

private:
    QSqlDatabase db;

public:
    DatabaseManager(const QString& dbName);
    QSqlQuery executeQuery(const QString& queryString);
    ~DatabaseManager();
};

#endif // DATABASEMANAGER_H
