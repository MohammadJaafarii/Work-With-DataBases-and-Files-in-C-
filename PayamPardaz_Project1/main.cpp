#include <iostream>
#include <map>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <string>
#include <QString>
#include <QCoreApplication>
#include <QDebug>
#include <locale>
#include "databasemanager.h"
#include "saveandloadtofile.h"
#include "user.h"
#include "group.h"
#include "detailpersonalinfo.h"

// class DatabaseManager {
// private:
//     QSqlDatabase db;

// public:
//     DatabaseManager(const QString& dbName) {
//         try{
//             db = QSqlDatabase::addDatabase("QSQLITE");
//             db.setDatabaseName(dbName);

//             if (!db.open()) {
//                 qDebug() << "Error: Failed to connect to Database:" << db.lastError().text();
//                 exit(1);
//             } else {
//                 qDebug() << "Connected to database successfully!";
//             }
//         }
//         catch(...){
//             qDebug() << "Error occured while connecting to Database!";

//         }
//     }

//     QSqlQuery executeQuery(const QString& queryString) {
//         QSqlQuery query(db);
//         try {
//             if (!query.exec(queryString)) {
//                 qDebug() << "Error executing query:" << query.lastError().text();
//             }
//         } catch (...) {
//             qDebug() << "Error occurred while executing query!";
//         }
//         return query;
//     }


//     ~DatabaseManager() {
//         db.close();
//     }


// };


// template <class T> class SaveAndLoadToFile{
// public:
//     static void saveToFile(const std::string& fileName, std::map<int, T> & infos){
//         try {
//             std::ofstream file(fileName, std::ios::binary);
//             if (!file.is_open()) {
//                 qDebug() << "Error opening file for writing:" << QString::fromStdString(fileName);
//                 return;
//             }

//             for(auto [_, info] : infos)
//             {
//                 file.write(reinterpret_cast<const char*>(&info), sizeof(info));
//             }

//             qDebug() << "Users saved to file" << QString::fromStdString(fileName) << "successfully." ;
//             file.close();
//         }
//         catch (...) {
//             qDebug() << "Error occurred while saving users to file.";
//         }
//     }

//     static void loadFromFile(const std::string& fileName, std::map<int, T> & infos){
//         try {
//             std::ifstream file(fileName, std::ios::binary);
//             if (!file.is_open()) {
//                 qDebug() << "Error: Unable to open file for reading" << QString::fromStdString(fileName);
//                 return;
//             }

//             T info;
//             while (file.read(reinterpret_cast<char*>(&info), sizeof(info))) {

//                 infos[info.ID] = info;
//             }

//             file.close();
//             qDebug() << "Loaded groups from file:" << QString::fromStdString(fileName);
//         }
//         catch (...) {
//             qDebug() << "Error occurred while loading users from file.";
//         }
//     }
// };


// class User{
    
// public:
//     int ID;
//     wchar_t  name [101];
//     uint32_t IP;
//     wchar_t  Password[51];
//     int GroupID;
    
//     User(int ID, wchar_t  name[101], uint32_t IP, wchar_t  Password[51], int GroupID){

//         this->ID = ID;

//         std::wmemset(this->name, 0, sizeof(this->name) / sizeof(this->name[0]));
//         size_t len_name = std::wcslen(name);
//         std::wcsncpy(this->name, name, len_name);
//         this->name[len_name] = L'\0';

//         this->IP = IP;

//         std::wmemset(this->Password, 0, sizeof(this->Password) / sizeof(this->Password[0]));
//         size_t len_pass = std::wcslen(Password);
//         std::wcsncpy(this->Password, Password, len_pass);
//         this->name[len_pass] = L'\0';

//         // GroupId could be NULL
//         //NULL for integers is defined as -1
//         this->GroupID = GroupID;
//     }
    // User(){
        
    // }
    
    // using UserInfo = std::map<int, User>;
    
    // static UserInfo& loadUsers(DatabaseManager& dbManager, UserInfo& users) {
    //     try{
    //         const QString query_command = "SELECT * FROM User";
    //         QSqlQuery query = dbManager.executeQuery(query_command);
    //         while (query.next()) {
                
    //             int id = query.value(0).toInt();
                
    //             std::string name = query.value(1).toString().toStdString();
    //             std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    //             std::wstring nsource = converter.from_bytes(name);
    //             wchar_t name_c[101];
    //             //std::wmemset(name_c, 0, sizeof(name_c));
    //             size_t name_len = nsource.size();
    //             std::wcsncpy(name_c, nsource.c_str(), name_len);
    //             name_c[name_len] = L'\0';
                
    //             uint32_t IP = static_cast<uint32_t>(query.value(2).toULongLong());

    //             std::string password = query.value(3).toString().toStdString();
    //             std::wstring pass_source = converter.from_bytes(password);
    //             wchar_t pass_c[51];
    //             //std::wmemset(pass_c, 0, sizeof(pass_c));
    //             size_t pass_len = pass_source.size();
    //             std::wcsncpy(pass_c, pass_source.c_str(), pass_len);
    //             pass_c[pass_len] = L'\0';
                
    //             int groupid = query.isNull(4) ? -1 : query.value(4).toInt();
    //             users[id]= User {id, name_c, IP, pass_c, groupid};
                    
                
                
    //         }
    //         qDebug() << "Loaded users successfully.";
    //         return users;
    //     }

    //     catch(...){
    //         qDebug() << "Error Occurred while loading 'User' Data\n";
    //         exit(1);
    //     }

    // }
    
    // static void saveUsersToFile(const std::string& fileName, UserInfo& users) {
    //     try {
    //         std::ofstream file(fileName, std::ios::binary);
    //         if (!file.is_open()) {
    //             qDebug() << "Error opening file for writing:" << QString::fromStdString(fileName);
    //             return;
    //         }
            
    //         for(auto [_, user] : users)
    //         {
    //             file.write(reinterpret_cast<const char*>(&user), sizeof(user));
    //         }
            
    //         qDebug() << "Users saved to file" << QString::fromStdString(fileName) << "successfully." ;
    //         file.close();
    //     }
    //     catch (...) {
    //         qDebug() << "Error occurred while saving users to file.";
    //     }
    // }
    
    // static void loadUsersFromFile(const std::string& fileName, UserInfo& users) {
    //     try {
    //         std::ifstream file(fileName, std::ios::binary);
    //         if (!file.is_open()) {
    //             qDebug() << "Error: Unable to open file for reading" << QString::fromStdString(fileName);
    //             return;
    //         }
            
    //         User user;
    //         while (file.read(reinterpret_cast<char*>(&user), sizeof(user))) {

    //             users[user.ID] = user;
    //         }

    //         file.close();
    //         qDebug() << "Loaded groups from file:" << QString::fromStdString(fileName);
    //     }
    //     catch (...) {
    //         qDebug() << "Error occurred while loading users from file.";
    //     }
    // }

//     static void saveUsersToDatabase(DatabaseManager& dbManager, const UserInfo& users) {
//         try {
//             for (const auto& pair : users) {
//                 int id = pair.first;
//                 const User user = pair.second;
                
//                 QSqlQuery query;
//                 query.prepare("INSERT INTO 'User' (name, IP, Password, GroupID) VALUES (:name, :IP, :Password, :GroupID)");
//                 query.bindValue(":name", QString::fromWCharArray(user.name));
//                 query.bindValue(":IP", qlonglong(user.IP));
//                 query.bindValue(":Password", QString::fromWCharArray(user.Password));
//                 query.bindValue(":GroupID", user.GroupID == -1 ? QVariant(QVariant::Int) : user.GroupID);
                
//                 if (!query.exec()) {
//                     qDebug() << "Error:\nInserting data into User table for UserID:" << user.ID << " - " << query.lastError().text();
//                     continue;
//                 }
//                 QString success_msg = QString("User with UserID '%1' inserted successfully").arg(QString::number(id));
//                 qDebug() << success_msg;

                
//             }

//         }
//         catch (...) {
//             qDebug() << "Error occurred while saving users to database.";
//         }
//     }
// };

// class Group{
// public:
//     int ID;
//     wchar_t Name[101];
//     wchar_t Description [1001];
//     bool Is_Active;
//     Group(int ID, wchar_t Name [101], bool Is_Active, wchar_t Description[1001] = nullptr){
//         try{
//             this->ID = ID;

//             std::wmemset(this->Name, 0, sizeof(this->Name) / sizeof(this->Name[0]));
//             size_t len_name = std::wcslen(Name);
//             std::wcsncpy(this->Name, Name, len_name);
//             this->Name[len_name] = L'\0';

//             std::wmemset(this->Description, 0, sizeof(this->Description) / sizeof(this->Description[0]));
//             size_t len_description = std::wcslen(Description);
//             std::wcsncpy(this->Description, Description, len_description);
//             this->Description[len_description] = L'\0';

//             this->Is_Active = Is_Active;
//         }
//         catch(...){
//             qDebug() << "Error occured while setting value for Group object";

//         }
//     }

//     Group(){

//     }

//     using GroupInfo = std::map<int, Group>;
//     static GroupInfo & loadGroups(DatabaseManager& dbManager, GroupInfo & groups) {

//         try{
//             const QString query_command = "SELECT * FROM 'Group'";
//             QSqlQuery query = dbManager.executeQuery(query_command);
//             while (query.next()) {
//                 int id = query.value(0).toInt();

//                 std::string name = query.value(1).toString().toStdString();
//                 std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//                 std::wstring nsource = converter.from_bytes(name);
//                 wchar_t name_c[101];
//                 //std::wmemset(name_c, 0, sizeof(name_c));
//                 size_t name_len = nsource.size();
//                 std::wcsncpy(name_c, nsource.c_str(), name_len);
//                 name_c[name_len] = L'\0';

//                 std::string description = query.value(2).toString().toStdString();
//                 std::wstring descrptn_source = converter.from_bytes(description);
//                 wchar_t descrptn_c[1001];
//                 //std::wmemset(name_c, 0, sizeof(name_c));
//                 size_t descrptn_len = descrptn_source.size();
//                 std::wcsncpy(descrptn_c, descrptn_source.c_str(), descrptn_len);
//                 descrptn_c[descrptn_len] = L'\0';

//                 bool isActive = query.value(3).toBool();


//                 groups[id] = Group {id , name_c, isActive, descrptn_c};
//             }
//             qDebug() << "Loaded groups successfully.";
//             return groups;
//         }

//         catch(...){
//             qDebug() << "Error Occurred while loading 'Group' Data";
//             exit(1);
//         }

//     }



    // static void saveGroupsToFile(const std::string& fileName, const GroupInfo& groups ) {

    //     try{
    //         std::ofstream file(fileName, std::ios::binary);
    //         if (!file.is_open()) {
    //             qDebug() << "Error opening file for writing:" << QString::fromStdString(fileName);
    //             return;
    //         }

    //         for(auto [_, group] : groups)
    //         {
    //             file.write(reinterpret_cast<const char*>(&group), sizeof(group));
    //         }


    //         file.close();
    //         qDebug() << "Groups saved to file" << QString::fromStdString(fileName) << "successfully.";
    //     }
    //     catch (...) {
    //         qDebug() << "Error occurred while saving Groups to file.";
    //     }

    // }

    // static void loadGroupsFromFile(const std::string& filename, GroupInfo& groups) {

    //     try{
    //         std::ifstream file(filename, std::ios::binary);
    //         if (!file.is_open()) {
    //             qDebug() << "Error opening file for reading:" << QString::fromStdString(filename);
    //             return;

    //         }


    //         Group group;
    //         while (file.read(reinterpret_cast<char*>(&group), sizeof(group))) {


    //             groups[group.ID] = group;
    //         }

    //         file.close();
    //         qDebug() << "Loaded groups from file:" << QString::fromStdString(filename);
    //     }

    //     catch (...) {
    //         qDebug() << "Error occurred while loading Groups from file.";
    //     }

    // }

//     static void saveGroupsToDatabase(DatabaseManager& dbManager, const GroupInfo& groups) {
//         try{
//             for (const auto& pair : groups) {
//                 int id = pair.first;
//                 const Group group = pair.second;

//                 QSqlQuery query;
//                 query.prepare("INSERT INTO 'Group' (name, description, is_active) VALUES (:Name, :Description, :Is_Active);");
//                 query.bindValue(":Name", QString::fromWCharArray(group.Name));
//                 query.bindValue(":Description", std::wcslen(group.Description) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(group.Description));
//                 query.bindValue(":Is_Active", group.Is_Active ? 1 : 0);

//                 if (!query.exec()) {
//                     qDebug() << "Error inserting data into Group:" << query.lastError().text() << "for group ID:" << QString::number(group.ID);
//                     continue;
//                 } else {
//                     QString success_msg = QString("Group with ID '%1' inserted successfully").arg(id);
//                     qDebug() << success_msg;

//                 }
//             }
//         }
//         catch (...) {
//             qDebug() << "Error occurred while saving groups to database.";
//         }

//     }
// };

// class DetailPersonalInfo{
// public:
//     int ID;
//     wchar_t FirstName [101];
//     wchar_t LastName [101];
//     wchar_t Office [101];
//     wchar_t Phone [21];
//     wchar_t PersonnelCode [11];
//     wchar_t Address[1001];

//     DetailPersonalInfo(int UserID, wchar_t FirstName [101], wchar_t LastName [101] , wchar_t Office [101],wchar_t Phone[21],
//                        wchar_t PersonnelCode [11], wchar_t Address [1001]){
//         try{

//             this->ID = UserID;

//             std::wmemset(this->FirstName, 0, sizeof(this->FirstName) / sizeof(this->FirstName[0]));
//             size_t len_fname = std::wcslen(FirstName);
//             std::wcsncpy(this->FirstName, FirstName, len_fname);
//             this->FirstName[len_fname] = L'\0';

//             std::wmemset(this->LastName, 0, sizeof(this->LastName) / sizeof(this->LastName[0]));
//             size_t len_lname = std::wcslen(LastName);
//             std::wcsncpy(this->LastName, LastName, len_lname);
//             this->LastName[len_lname] = L'\0';

//             std::wmemset(this->Office, 0, sizeof(this->Office) / sizeof(this->Office[0]));
//             size_t len_office = std::wcslen(Office);
//             std::wcsncpy(this->Office, Office, len_office);
//             this->Office[len_office] = L'\0';

//             std::wmemset(this->Phone, 0, sizeof(this->Phone) / sizeof(this->Phone[0]));
//             size_t len_phone = std::wcslen(Phone);
//             std::wcsncpy(this->Phone, Phone, len_phone);
//             this->Phone[len_phone] = L'\0';

//             std::wmemset(this->PersonnelCode, 0, sizeof(this->PersonnelCode) / sizeof(this->PersonnelCode[0]));
//             size_t len_personnelcode = std::wcslen(PersonnelCode);
//             std::wcsncpy(this->PersonnelCode, PersonnelCode, len_personnelcode);
//             this->PersonnelCode[len_personnelcode] = L'\0';

//             std::wmemset(this->Address, 0, sizeof(this->Address) / sizeof(this->Address[0]));
//             size_t len_address = std::wcslen(Address);
//             std::wcsncpy(this->Address, Address, len_address);
//             this->Address[len_address] = L'\0';

//         }

//         catch(...){

//             qDebug() << "Error occured while setting value for DetailPersonalInfo object";

//         }
//     }


//     DetailPersonalInfo(){

//     }

//     using DetailInfo = std::map<int, DetailPersonalInfo>;

//     static DetailInfo loadDetailPersonalInfo(DatabaseManager& dbManager,
//                                              DetailInfo& details) {

//         try{
//             const QString query_command = "SELECT * FROM 'DetailPersonalInfo'";
//             QSqlQuery query = dbManager.executeQuery(query_command);
//             while (query.next()) {
//                 int userID = query.value(0).toInt();

//                 std::string firstName = query.value(1).toString().toStdString();
//                 std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//                 std::wstring fnsource = converter.from_bytes(firstName);
//                 wchar_t firstName_c[101];
//                 //std::wmemset(name_c, 0, sizeof(name_c));
//                 size_t fname_len = fnsource.size();
//                 std::wcsncpy(firstName_c, fnsource.c_str(), fname_len);
//                 firstName_c[fname_len] = L'\0';

//                 std::string lastName = query.value(2).toString().toStdString();
//                 std::wstring lnsource = converter.from_bytes(lastName);
//                 wchar_t lastName_c[101];
//                 //std::wmemset(name_c, 0, sizeof(name_c));
//                 size_t lname_len = lnsource.size();
//                 std::wcsncpy(lastName_c, lnsource.c_str(), lname_len);
//                 lastName_c[lname_len] = L'\0';

//                 std::string office = query.value(3).toString().toStdString();
//                 std::wstring office_source = converter.from_bytes(office);
//                 wchar_t office_c[101];
//                 //std::wmemset(name_c, 0, sizeof(name_c));
//                 size_t office_len = office_source.size();
//                 std::wcsncpy(office_c, office_source.c_str(), office_len);
//                 office_c[office_len] = L'\0';

//                 std::string phone = query.value(4).toString().toStdString();
//                 std::wstring phone_source = converter.from_bytes(phone);
//                 wchar_t phone_c[21];
//                 //std::wmemset(name_c, 0, sizeof(name_c));
//                 size_t phone_len = phone_source.size();
//                 std::wcsncpy(phone_c, phone_source.c_str(), phone_len);
//                 phone_c[phone_len] = L'\0';

//                 std::string personnelCode = query.value(5).toString().toStdString();
//                 std::wstring personnelCode_source = converter.from_bytes(personnelCode);
//                 wchar_t personnelCode_c[11];
//                 //std::wmemset(name_c, 0, sizeof(name_c));
//                 size_t pc_len = personnelCode_source.size();
//                 std::wcsncpy(personnelCode_c, personnelCode_source.c_str(), pc_len);
//                 personnelCode_c[pc_len] = L'\0';

//                 std::string address = query.value(6).toString().toStdString();
//                 std::wstring address_source = converter.from_bytes(address);
//                 wchar_t address_c[1001];
//                 //std::wmemset(name_c, 0, sizeof(name_c));
//                 size_t address_len = address_source.size();
//                 std::wcsncpy(address_c, address_source.c_str(), address_len);
//                 address_c[address_len] = L'\0';


//                 details[userID] = (DetailPersonalInfo {userID, firstName_c, lastName_c, office_c, phone_c, personnelCode_c, address_c});
//             }
//             qDebug() << "Loaded DetailPersonalInfos successfully.";
//             return details;
//         }

//         catch(...){
//             qDebug() << "Error Occurred while loading 'DetailPersonalInfo' Data";
//             exit(1);
//         }

//     }

    // static void saveDetailPersonalInfosToFile(const std::string& fileName, DetailInfo& details) {
    //     try {
    //         std::ofstream file(fileName, std::ios::binary);
    //         if (!file.is_open()) {
    //             qDebug() << "Error opening file for writing:" << QString::fromStdString(fileName);
    //             return;
    //         }

    //         for(auto [_, detail] : details)
    //         {
    //             file.write(reinterpret_cast<const char*>(&detail), sizeof(detail));
    //         }

    //         file.close();
    //         qDebug() << "DetailPersonalInfos saved to file" << QString::fromStdString(fileName) << "successfully.";
    //     } catch (...) {
    //         qDebug() << "Error occurred while saving DetailPersonalInfos to file.";
    //     }
    // }

    // static void loadDetailPersonalInfosFromFile(const std::string& filename,
    //                                             DetailInfo& details) {
    //     try {
    //         std::ifstream file(filename, std::ios::binary);
    //         if (!file.is_open()) {
    //             qDebug() << "Error opening file for reading:" << QString::fromStdString(filename);
    //             return;
    //         }


    //         DetailPersonalInfo detail;
    //         while (file.read(reinterpret_cast<char*>(&detail), sizeof(detail))) {


    //             details[detail.ID] = detail;
    //         }

    //         file.close();
    //         qDebug() << "Loaded DetailPersonalInfos from file:" << QString::fromStdString(filename);
    //     } catch (...) {
    //         qDebug() << "Error occurred while loading DetailPersonalInfos from file.";
    //     }


    // }

//     static void saveDetailPersonalInfosToDatabase(DatabaseManager& dbManager, const DetailInfo& details) {

//         try{
//             for (const auto& pair : details) {
//                 int userID = pair.first;
//                 const DetailPersonalInfo& detail = pair.second;

//                 QSqlQuery query;
//                 query.prepare("INSERT INTO 'DetailPersonalInfo' (userid, firstname, lastname, office, phone, personnelcode, address) "
//                               "VALUES (:UserID, :FirstName, :LastName, :Office, :Phone, :PersonnelCode, :Address)");

//                 query.bindValue(":UserID", detail.ID);
//                 query.bindValue(":FirstName", std::wcslen(detail.FirstName) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.FirstName));
//                 query.bindValue(":LastName", std::wcslen(detail.LastName) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.LastName));
//                 query.bindValue(":Office", std::wcslen(detail.Office) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.Office));
//                 query.bindValue(":Phone", std::wcslen(detail.Phone) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.Phone));
//                 query.bindValue(":PersonnelCode", std::wcslen(detail.PersonnelCode) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.PersonnelCode));
//                 query.bindValue(":Address", std::wcslen(detail.Address) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.Address));

//                 if (!query.exec()) {
//                     qDebug() << "Error inserting data into DetailPersonalInfo:" << query.lastError().text() << "for UserID:" << userID;
//                     continue;
//                 } else {
//                     QString success_msg = QString("DetailPersonalInfo with UserID '%1' inserted successfully").arg(detail.ID);
//                     qDebug() << success_msg;
//                 }

//             }
//         }
//         catch (...) {
//             qDebug() << "Error occurred while saving DetailPersonalInfos to database.";
//         }

//     }


// };





int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);

    std::locale::global(std::locale(""));


    std::string mode = "";

    QString source_db = "sourceDB.db";
    QString target_db = "targetDB.db";

    std::string user_file = "User.dat";
    std::string group_file = "Group.dat";
    std::string DetailPersonalInfo_file = "DetailPersonalInfo.dat";
    while(1){
        qDebug() << "Please Enter the mode:";
        std::cin >> mode;
        if (mode == "exporter"|| mode == "Exporter"){
            DatabaseManager sDB(source_db);

            std::map<int, User> users;
            User::loadUsers(sDB, users);
            //User::saveUsersToFile(user_file, users);
            SaveAndLoadToFile<User>::saveToFile(user_file, users);

            std::map<int, Group> groups;
            Group::loadGroups(sDB, groups);
            //Group::saveGroupsToFile(group_file, groups);
            SaveAndLoadToFile<Group>::saveToFile(group_file, groups);

            std::map<int, DetailPersonalInfo> DetailPersonalInfol;
            DetailPersonalInfo::loadDetailPersonalInfo(sDB, DetailPersonalInfol);
            //DetailPersonalInfo::saveDetailPersonalInfosToFile(DetailPersonalInfo_file,DetailPersonalInfol);
            SaveAndLoadToFile<DetailPersonalInfo>::saveToFile(DetailPersonalInfo_file, DetailPersonalInfol);

        }
        else if (mode == "importer" || mode == "Importer"){
            DatabaseManager tDB(target_db);

            std::map<int, User> luser;
            SaveAndLoadToFile<User>::loadFromFile(user_file, luser);

            std::map<int, Group> lgroup;
            SaveAndLoadToFile<Group>::loadFromFile(group_file, lgroup);

            std::map<int, DetailPersonalInfo> lDetailPersonalInfo;
            SaveAndLoadToFile<DetailPersonalInfo>::loadFromFile(DetailPersonalInfo_file, lDetailPersonalInfo);

            //Group::saveGroupsToDatabase(tDB, lgroup,luser);
            User::saveUsersToDatabase(tDB, luser, lDetailPersonalInfo);
            DetailPersonalInfo::saveDetailPersonalInfosToDatabase(tDB, lDetailPersonalInfo);

        }

        else{
            break;
        }
    }


    return 0;

}
