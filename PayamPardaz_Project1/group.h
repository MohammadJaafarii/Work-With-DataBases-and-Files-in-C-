#ifndef GROUP_H
#define GROUP_H
#include <iostream>
#include <map>
#include "databasemanager.h"
#include "user.h"
class Group
{
public:
    int ID;
    wchar_t Name[101];
    wchar_t Description [1001];
    bool Is_Active;

    Group(int ID, wchar_t Name [101], bool Is_Active, wchar_t Description[1001] = nullptr);
    Group();

    using GroupInfo = std::map<int, Group>;
    static GroupInfo & loadGroups(DatabaseManager& dbManager, GroupInfo & groups);
    static void saveGroupsToDatabase(DatabaseManager& dbManager, const GroupInfo& groups, std::map<int, User>& userInfo);

};

#endif // GROUP_H
