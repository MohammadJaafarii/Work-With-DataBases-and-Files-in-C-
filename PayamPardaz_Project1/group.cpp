#include "group.h"
#include <iostream>
#include <cwchar>
#include <locale>
#include <codecvt>

Group::Group() {}

Group::Group(int ID, wchar_t Name [101], bool Is_Active, wchar_t Description[1001]){
    try{
        this->ID = ID;

        std::wmemset(this->Name, 0, sizeof(this->Name) / sizeof(this->Name[0]));
        size_t len_name = std::wcslen(Name);
        std::wcsncpy(this->Name, Name, len_name);
        this->Name[len_name] = L'\0';

        std::wmemset(this->Description, 0, sizeof(this->Description) / sizeof(this->Description[0]));
        size_t len_description = std::wcslen(Description);
        std::wcsncpy(this->Description, Description, len_description);
        this->Description[len_description] = L'\0';

        this->Is_Active = Is_Active;
    }
    catch(...){
        qDebug() << "Error occured while setting value for Group object";

    }
}

using GroupInfo = std::map<int, Group>;
GroupInfo & Group::loadGroups(DatabaseManager& dbManager, GroupInfo & groups) {

    try{
        const QString query_command = "SELECT * FROM 'Group'";
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

            std::string description = query.value(2).toString().toStdString();
            std::wstring descrptn_source = converter.from_bytes(description);
            wchar_t descrptn_c[1001];
            //std::wmemset(name_c, 0, sizeof(name_c));
            size_t descrptn_len = descrptn_source.size();
            std::wcsncpy(descrptn_c, descrptn_source.c_str(), descrptn_len);
            descrptn_c[descrptn_len] = L'\0';

            bool isActive = query.value(3).toBool();


            groups[id] = Group {id , name_c, isActive, descrptn_c};
        }
        qDebug() << "Loaded groups successfully.";
        return groups;
    }

    catch(...){
        qDebug() << "Error Occurred while loading 'Group' Data";
        exit(1);
    }

}


void Group::saveGroupsToDatabase(DatabaseManager& dbManager, const GroupInfo& groups, std::map<int, User>& userInfo) {
    try{
        for (const auto& pair : groups) {
            int id = pair.first;
            const Group group = pair.second;

            QSqlQuery query;
            query.prepare("INSERT INTO 'Group' (name, description, is_active) VALUES (:Name, :Description, :Is_Active);");
            query.bindValue(":Name", QString::fromWCharArray(group.Name));
            query.bindValue(":Description", std::wcslen(group.Description) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(group.Description));
            query.bindValue(":Is_Active", group.Is_Active ? 1 : 0);

            if (!query.exec()) {
                qDebug() << "Error inserting data into Group:" << query.lastError().text() << "for group ID:" << QString::number(group.ID);
                continue;
            }
            else {
                // Retrieve the last inserted ID
                QVariant lastId = query.lastInsertId();
                if (lastId.isValid()) {
                    int new_id;
                    new_id = lastId.toInt();
                    auto it = userInfo.find(id);
                    if (it != userInfo.end()) {
                        // Get the user associated with oldKey
                        User user = it->second;

                        // Erase the oldKey from the map
                        userInfo.erase(it);

                        // Insert user with the newKey into the map
                        userInfo[new_id] = user;

                        // Update the user's ID to be the newKey
                        user.ID = new_id;

                        // Print success message
                        std::cout << "User with ID " << id << " updated to ID " << new_id << std::endl;
                    } else {
                        std::cerr << "Key " << id << " not found in map!" << std::endl;
                    }
                }
                QString success_msg = QString("Group with ID '%1' inserted successfully").arg(id);
                qDebug() << success_msg;
            }
        }
    }
    catch (...) {
        qDebug() << "Error occurred while saving groups to database.";
    }

}


