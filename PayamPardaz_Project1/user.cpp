#include "user.h"
#include <cwchar>
#include <locale>
#include <codecvt>
using UserInfo = std::map<int, User>;

User::User() {}

User::User(int ID, wchar_t  name[101], uint32_t IP, wchar_t  Password[51], int GroupID){
    this->ID = ID;

    std::wmemset(this->name, 0, sizeof(this->name) / sizeof(this->name[0]));
    size_t len_name = std::wcslen(name);
    std::wcsncpy(this->name, name, len_name);
    this->name[len_name] = L'\0';

    this->IP = IP;

    std::wmemset(this->Password, 0, sizeof(this->Password) / sizeof(this->Password[0]));
    size_t len_pass = std::wcslen(Password);
    std::wcsncpy(this->Password, Password, len_pass);
    this->name[len_pass] = L'\0';

    // GroupId could be NULL
    //NULL for integers is defined as -1
    this->GroupID = GroupID;
}

UserInfo& User::loadUsers(DatabaseManager& dbManager, UserInfo& users){
    try{
        const QString query_command = "SELECT * FROM User";
        QSqlQuery query = dbManager.executeQuery(query_command);
        while (query.next()) {

            int id = query.value(0).toInt();

            std::string name = query.value(1).toString().toStdString();
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring nsource = converter.from_bytes(name);
            wchar_t name_c[101];
            //std::wmemset(name_c, 0, sizeof(name_c));
            size_t name_len = nsource.size();
            std::wcsncpy(name_c, nsource.c_str(), name_len);
            name_c[name_len] = L'\0';

            uint32_t IP = static_cast<uint32_t>(query.value(2).toULongLong());

            std::string password = query.value(3).toString().toStdString();
            std::wstring pass_source = converter.from_bytes(password);
            wchar_t pass_c[51];
            //std::wmemset(pass_c, 0, sizeof(pass_c));
            size_t pass_len = pass_source.size();
            std::wcsncpy(pass_c, pass_source.c_str(), pass_len);
            pass_c[pass_len] = L'\0';

            int groupid = query.isNull(4) ? -1 : query.value(4).toInt();
            users[id]= User {id, name_c, IP, pass_c, groupid};



        }
        qDebug() << "Loaded users successfully.";
        return users;
    }

    catch(...){
        qDebug() << "Error Occurred while loading 'User' Data\n";
        exit(1);
    }
}

void User::saveUsersToDatabase(DatabaseManager& dbManager, const UserInfo& users,
                                std::map<int, DetailPersonalInfo>& PersonalInfo) {
    try {
        for (const auto& pair : users) {
            int id = pair.first;
            const User user = pair.second;

            QSqlQuery query;
            query.prepare("INSERT INTO 'User' (name, IP, Password, GroupID) VALUES (:name, :IP, :Password, :GroupID)");
            query.bindValue(":name", QString::fromWCharArray(user.name));
            query.bindValue(":IP", qlonglong(user.IP));
            query.bindValue(":Password", QString::fromWCharArray(user.Password));
            query.bindValue(":GroupID", user.GroupID == -1 ? QVariant(QVariant::Int) : user.GroupID);

            if (!query.exec()) {
                qDebug() << "Error:\nInserting data into User table for UserID:" << user.ID << " - " << query.lastError().text();
                continue;
            }
            else{
                // Retrieve the last inserted ID
                QVariant lastId = query.lastInsertId();
                if (lastId.isValid()) {
                    int new_id;
                    new_id = lastId.toInt();
                    auto it = PersonalInfo.find(id);
                    if (it != PersonalInfo.end()) {
                        // Get the user associated with oldKey
                        DetailPersonalInfo &user = it->second;

                        // Erase the oldKey from the map

                        // Insert user with the newKey into the map
                        PersonalInfo[new_id] = user;

                        // Update the user's ID to be the newKey
                        user.ID = new_id;
                        PersonalInfo.erase(it);

                        // Print success message
                        std::cout << "User ID at Personal information of User with ID " << id << " updated to ID " << new_id << std::endl;
                    } else {
                        std::cerr << "Key " << id << " not found in map!" << std::endl;
                    }
                }
                QString success_msg = QString("Group with ID '%1' inserted successfully").arg(id);
                qDebug() << success_msg;
            }
            QString success_msg = QString("User with UserID '%1' inserted successfully").arg(QString::number(id));
            qDebug() << success_msg;


        }

    }
    catch (...) {
        qDebug() << "Error occurred while saving users to database.";
    }
}






