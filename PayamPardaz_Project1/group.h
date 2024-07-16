#ifndef GROUP_H
#define GROUP_H
#include <iostream>
#include <map>
#include <unordered_map>
#include "databasemanager.h"
#include "user.h"
#include "logger.h"

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
    static GroupInfo & loadGroups(DatabaseManager& dbManager, GroupInfo & groups, Logger& logger);
    static void saveGroupsToDatabase(DatabaseManager& dbManager, const GroupInfo& groups, std::unordered_map<int, int>& update_keys, Logger& logger);

};

#endif // GROUP_H
