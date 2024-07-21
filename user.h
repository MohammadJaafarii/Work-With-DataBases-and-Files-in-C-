#ifndef USER_H
#define USER_H
#include <iostream>
#include <unordered_map>
#include "databasemanager.h"
#include "detailpersonalinfo.h"
#include "logger.h"

class User
{
public:
    int ID;
    wchar_t  name [101];
    uint32_t IP;
    wchar_t  Password[51];
    int GroupID;
    User(int ID, wchar_t  name[101], uint32_t IP, wchar_t  Password[51], int GroupID);
    User();
    using UserInfo = std::map<int, User>;

    static UserInfo& loadUsers(DatabaseManager& dbManager, UserInfo& users, Logger& logger);
    static void saveUsersToDatabase(DatabaseManager& dbManager, UserInfo& users,
                                    std::map<int, DetailPersonalInfo>& PersonalInfo, std::unordered_map<int, int>& update_keys, Logger& logger);

};

#endif // USER_H
