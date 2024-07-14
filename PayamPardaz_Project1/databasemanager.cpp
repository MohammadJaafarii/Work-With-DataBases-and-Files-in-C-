#include "databasemanager.h"

DatabaseManager::DatabaseManager(const QString& dbName) {
    try{
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);

        if (!db.open()) {
            qDebug() << "Error: Failed to connect to Database:" << db.lastError().text();
            exit(1);
        } else {
            qDebug() << "Connected to database successfully!";
        }
    }
    catch(...){
        qDebug() << "Error occured while connecting to Database!";

    }
}

QSqlQuery DatabaseManager:: executeQuery(const QString& queryString){
    QSqlQuery query(db);
    try {
        if (!query.exec(queryString)) {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
    } catch (...) {
        qDebug() << "Error occurred while executing query!";
    }
    return query;
}

DatabaseManager::~DatabaseManager(){
    db.close();
}



