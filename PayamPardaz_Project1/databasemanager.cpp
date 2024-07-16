#include "databasemanager.h"

DatabaseManager::DatabaseManager(const QString& dbName, Logger& logger) {
    try{

        this->logger = logger;
        this->logger.info("______________________________DataBase Manager (constructor function)______________________________");
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);

        if (!db.open()) {
            this->logger.error("Error: Failed to connect to Database:" + db.lastError().text());
            exit(1);
        } else {
            this->logger.info("Connected to database successfully!");
        }
    }
    catch(...){
        this->logger.error("Error occured while connecting to Database!");

    }
}

QSqlQuery DatabaseManager:: executeQuery(const QString& queryString){
    QSqlQuery query(db);
    try {

        if (!query.exec(queryString)) {
            this->logger.error("Error executing query:" + query.lastError().text());
        }
    } catch (...) {
        this->logger.error("Error occurred while executing query!");
    }
    return query;
}

DatabaseManager::~DatabaseManager(){
    db.close();
}



