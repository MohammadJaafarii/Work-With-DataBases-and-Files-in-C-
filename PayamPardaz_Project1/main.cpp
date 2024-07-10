#include <iostream>
#include <vector>
#include <map>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <string>
#include <QCoreApplication>
#include <QDebug>
#include <fstream>

using std::cout;
using std::cin;
using std:: endl;
using std::string;
using std::map;
using std::vector;

class DatabaseManager {
private:
    QSqlDatabase db;

public:
    DatabaseManager(const QString& dbName) {
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

    QSqlQuery executeQuery(const QString& queryString) {
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

    void printQueryResult(QSqlQuery& query) {
        qDebug() << "Query result:";
        QSqlRecord record = query.record();
        int columnCount = record.count();

        while (query.next()) {
            QStringList rowValues;
            for (int i = 0; i < columnCount; ++i) {
                QString columnName = record.fieldName(i);
                QVariant columnValue = query.value(i);
                if (columnValue.isNull()) {
                    rowValues << QString("%1: %2").arg(columnName, "NULL");
                } else {
                    rowValues << QString("%1: %2").arg(columnName, columnValue.toString());
                }
            }
            qDebug().noquote() << rowValues.join(", ");
        }
    }


    ~DatabaseManager() {
        db.close();
    }


};


class User{
public:
    int ID;
    string name;
    long long IP;
    string Password;
    int GroupID;

    User(int ID, string name, long long IP, string Password, int GroupID){
        try{
            this->ID = ID;
            this->name = name;
            this->IP = IP;
            this->Password = Password;
            // GroupId could be NULL
            //NULL for integers is defined as -1
            this->GroupID = GroupID;

        }

        catch(...){
            qDebug() << "Error occured while setting value for User object";
        }

    }


    static map<int, vector<User>>& loadUsers(DatabaseManager& dbManager, map<int, vector<User>>& users) {
        try{
            const QString query_command = "SELECT * FROM 'User'";
            QSqlQuery query = dbManager.executeQuery(query_command);
            while (query.next()) {
                int id = query.value(0).toInt();
                string name = query.value(1).toString().toStdString();
                long long IP = query.value(2).toLongLong();
                string password = query.value(3).toString().toStdString();
                int groupid = query.isNull(4) ? -1 : query.value(4).toInt();

                User user(id, name, IP, password, groupid);
                users[id].push_back(user);
            }
            qDebug() << "Loaded users successfully.";
            return users;
        }

        catch(...){
            qDebug() << "Error Occurred while loading 'User' Data";
            exit(1);
        }

    }

    static void saveUsersToFile(const string& fileName, const std::map<int, vector<User>>& users) {
        try {
            std::ofstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                qDebug() << "Error opening file for writing:" << QString::fromStdString(fileName);
                return;
            }

            for (const auto& pair : users) {
                int id = pair.first;
                const vector<User>& userList = pair.second;
                for (const User& user : userList) {
                    file.write(reinterpret_cast<const char*>(&id), sizeof(id));
                    int nameSize = user.name.size();
                    file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
                    file.write(user.name.c_str(), nameSize);
                    file.write(reinterpret_cast<const char*>(&user.IP), sizeof(user.IP));
                    int passwordSize = user.Password.size();
                    file.write(reinterpret_cast<const char*>(&passwordSize), sizeof(passwordSize));
                    file.write(user.Password.c_str(), passwordSize);
                    file.write(reinterpret_cast<const char*>(&user.GroupID), sizeof(user.GroupID));
                }
            }

            qDebug() << "Users saved to file" << QString::fromStdString(fileName) << "successfully." ;
            file.close();
        }
        catch (...) {
            qDebug() << "Error occurred while saving users to file.";
        }
    }

    static void loadUsersFromFile(const string& fileName, std::map<int, std::vector<User>>& users) {
        try {
            std::ifstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                qDebug() << "Error: Unable to open file for reading";
                return;
            }

            int id;
            while (file.read(reinterpret_cast<char*>(&id), sizeof(id))) {

                int nameSize;
                file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
                string name(nameSize, '\0');
                file.read(&name[0], nameSize);

                long long IP;
                file.read(reinterpret_cast<char*>(&IP), sizeof(IP));

                int passwordSize;
                file.read(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
                string password(passwordSize, '\0');
                file.read(&password[0], passwordSize);

                int groupid;
                file.read(reinterpret_cast<char*>(&groupid), sizeof(groupid));

                if (file.eof()) break;  // To handle the last read which can be eof.

                User user(id, name, IP, password, groupid);
                users[id].push_back(user);
            }

            file.close();
            qDebug() << "Users loaded from file successfully.";
        }
        catch (...) {
            qDebug() << "Error occurred while loading users from file.";
        }
    }
};

class Group{
public:
    int ID;
    string Name;
    string Description;
    bool Is_Active;
    Group(int ID, string Name, bool Is_Active, string Description = nullptr){
        try{
            this->ID = ID;
            this->Name = Name;
            this-> Description = Description;
            this->Is_Active = Is_Active;
        }
        catch(...){
            qDebug() << "Error occured while setting value for Group object";

        }
    }

    static map<int, vector<Group>>& loadGroups(DatabaseManager& dbManager, map<int, vector<Group>>& groups) {

        try{
            const QString query_command = "SELECT * FROM 'Group'";
            QSqlQuery query = dbManager.executeQuery(query_command);
            while (query.next()) {
                int id = query.value(0).toInt();
                string name = query.value(1).toString().toStdString();
                string description = query.value(2).toString().toStdString();
                bool isActive = query.value(3).toBool();

                Group group(id, name, isActive, description);
                groups[id].push_back(group);
            }
            qDebug() << "Loaded groups successfully.";
            return groups;
        }

        catch(...){
            qDebug() << "Error Occurred while loading 'Group' Data";
            exit(1);
        }

    }



    static void saveGroupsToFile(const string& fileName, const map<int, vector<Group>>& groups ) {

        try{
            std::ofstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                qDebug() << "Error opening file for writing:" << QString::fromStdString(fileName);
                return;
            }

            for (const auto& pair : groups) {
                int groupID = pair.first;
                const vector<Group>& groupList = pair.second;

                for (const Group& group : groupList) {

                    file.write(reinterpret_cast<const char*>(&groupID), sizeof(groupID));
                    int nameSize = group.Name.size();
                    file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
                    file.write(group.Name.c_str(), nameSize);

                    int descriptionSize = group.Description.size();
                    file.write(reinterpret_cast<const char*>(&descriptionSize), sizeof(descriptionSize));
                    if (descriptionSize > 0) {
                        file.write(group.Description.c_str(), descriptionSize);
                    }

                    file.write(reinterpret_cast<const char*>(&group.Is_Active), sizeof(group.Is_Active));
                }
            }

            qDebug() << "Groups saved to file" << QString::fromStdString(fileName) << "successfully.";
            file.close();
        }
        catch (...) {
            qDebug() << "Error occurred while saving Groups to file.";
        }

    }

    static void loadGroupsFromFile(const string& filename, map<int, vector<Group>>& groups) {

        try{
            std::ifstream file(filename, std::ios::binary);
            if (!file.is_open()) {
                qDebug() << "Error opening file for reading:" << QString::fromStdString(filename);
            }


            int groupID;
            while (file.read(reinterpret_cast<char*>(&groupID), sizeof(groupID))) {

                int nameSize;
                file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
                string name(nameSize, '\0');
                file.read(&name[0], nameSize);

                int descriptionSize;
                file.read(reinterpret_cast<char*>(&descriptionSize), sizeof(descriptionSize));
                string description = "";
                if (descriptionSize > 0) {
                    description.resize(descriptionSize);
                    file.read(&description[0], descriptionSize);
                }

                bool isActive;
                file.read(reinterpret_cast<char*>(&isActive), sizeof(isActive));

                Group group(groupID, name, isActive, description);
                groups[groupID].push_back(group);
            }

            qDebug() << "Loaded groups from file:" << QString::fromStdString(filename);
            file.close();
        }

        catch (...) {
            qDebug() << "Error occurred while loading Groups from file.";
        }

    }
};

class DetailPersonalInfo{
public:
    int UserID;
    string FirstName;
    string LastName;
    string Office;
    string Phone;
    string PersonnelCode;
    string Address;

    DetailPersonalInfo(int UserID, string FirstName = nullptr, string LastName = nullptr, string Office = nullptr, string Phone = nullptr,
                       string PersonnelCode = nullptr, string Address = nullptr){
        try{
            this->UserID = UserID;
            this->FirstName = FirstName;
            this->LastName = LastName;
            this->Office = Office;
            this->Phone = Phone;
            this->PersonnelCode = PersonnelCode;
            this->Address = Address;
        }

        catch(...){

            qDebug() << "Error occured while setting value for DetailPersonalInfo object";

        }
    }

    static map<int, std::vector<DetailPersonalInfo>> loadDetailPersonalInfo(DatabaseManager& dbManager,
                                                                            map<int, std::vector<DetailPersonalInfo>>& details) {

        try{
            const QString query_command = "SELECT * FROM 'DetailPersonalInfo'";
            QSqlQuery query = dbManager.executeQuery(query_command);
            while (query.next()) {
                int userID = query.value(0).toInt();
                std::string firstName = query.value(1).toString().toStdString();
                std::string lastName = query.value(2).toString().toStdString();
                std::string office = query.value(3).toString().toStdString();
                std::string phone = query.value(4).toString().toStdString();
                std::string personnelCode = query.value(5).toString().toStdString();
                std::string address = query.value(6).toString().toStdString();

                DetailPersonalInfo detail(userID, firstName, lastName, office, phone, personnelCode, address);
                details[userID].push_back(detail);
            }
            qDebug() << "Loaded DetailPersonalInfos successfully.";
            return details;
        }

        catch(...){
            qDebug() << "Error Occurred while loading 'DetailPersonalInfo' Data";
            exit(1);
        }

    }

    static void saveDetailPersonalInfosToFile(const std::string& fileName, const std::map<int, std::vector<DetailPersonalInfo>>& details) {
        try {
            std::ofstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                qDebug() << "Error opening file for writing:" << QString::fromStdString(fileName);
                return;
            }

            for (const auto& pair : details) {
                int userID = pair.first;
                const std::vector<DetailPersonalInfo>& detailList = pair.second;

                for (const DetailPersonalInfo& detail : detailList) {
                    file.write(reinterpret_cast<const char*>(&userID), sizeof(userID));

                    int firstNameSize = detail.FirstName.size();
                    file.write(reinterpret_cast<const char*>(&firstNameSize), sizeof(firstNameSize));
                    if (firstNameSize > 0){
                        file.write(detail.FirstName.c_str(), firstNameSize);
                    }

                    int lastNameSize = detail.LastName.size();
                    file.write(reinterpret_cast<const char*>(&lastNameSize), sizeof(lastNameSize));
                    if (lastNameSize > 0){
                        file.write(detail.LastName.c_str(), lastNameSize);
                    }

                    int officeSize = detail.Office.size();
                    file.write(reinterpret_cast<const char*>(&officeSize), sizeof(officeSize));
                    if (officeSize > 0){
                        file.write(detail.Office.c_str(), officeSize);
                    }

                    int phoneSize = detail.Phone.size();
                    file.write(reinterpret_cast<const char*>(&phoneSize), sizeof(phoneSize));
                    if (phoneSize > 0){
                        file.write(detail.Phone.c_str(), phoneSize);

                    }

                    int personnelCodeSize = detail.PersonnelCode.size();
                    file.write(reinterpret_cast<const char*>(&personnelCodeSize), sizeof(personnelCodeSize));

                    if (personnelCodeSize > 0){
                        file.write(detail.PersonnelCode.c_str(), personnelCodeSize);
                    }

                    int addressSize = detail.Address.size();
                    file.write(reinterpret_cast<const char*>(&addressSize), sizeof(addressSize));
                    if (addressSize > 0){
                        file.write(detail.Address.c_str(), addressSize);
                    }
                }
            }

            qDebug() << "DetailPersonalInfos saved to file" << QString::fromStdString(fileName) << "successfully.";
            file.close();
        } catch (...) {
            qDebug() << "Error occurred while saving DetailPersonalInfos to file.";
        }
    }

    static map<int, vector<DetailPersonalInfo>>& loadDetailPersonalInfosFromFile(const std::string& filename,
                                                             map<int, vector<DetailPersonalInfo>>& details) {
        try {
            std::ifstream file(filename, std::ios::binary);
            if (!file.is_open()) {
                qDebug() << "Error opening file for reading:" << QString::fromStdString(filename);
                return details;
            }


            int userID;
            while (file.read(reinterpret_cast<char*>(&userID), sizeof(userID))) {


                int firstNameSize;
                file.read(reinterpret_cast<char*>(&firstNameSize), sizeof(firstNameSize));
                string firstName = "";
                if (firstNameSize > 0) {
                    firstName.resize(firstNameSize);
                    file.read(&firstName[0], firstNameSize);
                }

                int lastNameSize;
                file.read(reinterpret_cast<char*>(&lastNameSize), sizeof(lastNameSize));
                string lastName = "";
                if (lastNameSize > 0) {
                    lastName.resize(lastNameSize);
                    file.read(&lastName[0], lastNameSize);
                }

                int officeSize;
                file.read(reinterpret_cast<char*>(&officeSize), sizeof(officeSize));
                string office = "";
                if (officeSize > 0) {
                    office.resize(officeSize);
                    file.read(&office[0], officeSize);
                }

                int phoneSize;
                file.read(reinterpret_cast<char*>(&phoneSize), sizeof(phoneSize));
                string phone = "";
                if (phoneSize > 0) {
                    phone.resize(phoneSize);
                    file.read(&phone[0], phoneSize);
                }

                int personnelCodeSize;
                file.read(reinterpret_cast<char*>(&personnelCodeSize), sizeof(personnelCodeSize));
                string personnelCode = "";
                if (personnelCodeSize > 0) {
                    personnelCode.resize(personnelCodeSize);
                    file.read(&personnelCode[0], personnelCodeSize);
                }

                int addressSize;
                file.read(reinterpret_cast<char*>(&addressSize), sizeof(addressSize));
                string address = "";
                if (addressSize > 0) {
                    address.resize(addressSize);
                    file.read(&address[0], addressSize);
                }

                DetailPersonalInfo detail(userID, firstName, lastName, office, phone, personnelCode, address);
                details[userID].push_back(detail);
            }

            qDebug() << "Loaded DetailPersonalInfos from file:" << QString::fromStdString(filename);
            file.close();
        } catch (...) {
            qDebug() << "Error occurred while loading DetailPersonalInfos from file.";
        }

        return details;
    }


};





int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    DatabaseManager db("Project1.db");

    map<int, vector<User>> users, luser;
    User::loadUsers(db, users);
    User::saveUsersToFile("User.dat", users);
    User::loadUsersFromFile("User.dat", luser);

    map<int, vector<Group>> groups, lgroup;
    Group::loadGroups(db, groups);
    Group::saveGroupsToFile("Group.dat", groups);
    Group::loadGroupsFromFile("Group.dat", lgroup);

    map<int, vector<DetailPersonalInfo>> DetailPersonalInfo, lDetailPersonalInfo;
    DetailPersonalInfo::loadDetailPersonalInfo(db, DetailPersonalInfo);
    DetailPersonalInfo::saveDetailPersonalInfosToFile("DetailPersonalInfo.dat",DetailPersonalInfo);
    DetailPersonalInfo::loadDetailPersonalInfosFromFile("DetailPersonalInfo.dat",lDetailPersonalInfo);
    return 0;

}
