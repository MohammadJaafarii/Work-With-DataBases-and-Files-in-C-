#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "logger.h"


class DatabaseManager
{
private:
    Logger logger;
    QSqlDatabase db;

public:
    DatabaseManager(const QString& dbName, Logger& logger);
    QSqlQuery executeQuery(const QString& queryString);
    ~DatabaseManager();
};

#endif // DATABASEMANAGER_H
