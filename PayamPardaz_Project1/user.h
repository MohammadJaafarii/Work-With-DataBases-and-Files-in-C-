#ifndef USER_H
#define USER_H
#include <iostream>
#include "databasemanager.h"
#include "detailpersonalinfo.h"
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

    static UserInfo& loadUsers(DatabaseManager& dbManager, UserInfo& users);
    static void saveUsersToDatabase(DatabaseManager& dbManager, const UserInfo& users,
                                    std::map<int, DetailPersonalInfo>& PersonalInfo);

};

#endif // USER_H
