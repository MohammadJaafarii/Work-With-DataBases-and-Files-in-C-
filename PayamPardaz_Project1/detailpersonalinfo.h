#ifndef DETAILPERSONALINFO_H
#define DETAILPERSONALINFO_H
#include <map>
#include "databasemanager.h"

class DetailPersonalInfo
{
public:
    int ID;
    wchar_t FirstName [101];
    wchar_t LastName [101];
    wchar_t Office [101];
    wchar_t Phone [21];
    wchar_t PersonnelCode [11];
    wchar_t Address[1001];

    DetailPersonalInfo(int UserID, wchar_t FirstName [101], wchar_t LastName [101] , wchar_t Office [101],wchar_t Phone[21],
                       wchar_t PersonnelCode [11], wchar_t Address [1001]);
    DetailPersonalInfo();

    using DetailInfo = std::map<int, DetailPersonalInfo>;

    static DetailInfo loadDetailPersonalInfo(DatabaseManager& dbManager,DetailInfo& details);
    static void saveDetailPersonalInfosToDatabase(DatabaseManager& dbManager, const DetailInfo& details);


};

#endif // DETAILPERSONALINFO_H
