#include <iostream>
#include <clipp.h>
#include <map>
#include <unordered_map>
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
#include "logger.h"

Logger logger("Log.txt");

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);

    std::locale::global(std::locale(""));

    std::string mode = "";
    QString source_db = "sourceDB.db";
    QString target_db = "targetDB.db";

    std::string user_file = "User.dat";
    std::string group_file = "Group.dat";
    std::string DetailPersonalInfo_file = "DetailPersonalInfo.dat";

    bool exporter = false;
    bool importer = false;
    bool help = false;

    auto cli = (
        clipp::option("-e", "--exporter").set(exporter).doc("Export Data from Database to File"),
        clipp::option("-i", "--importer").set(importer).doc("Import Data From File to Database"),
        clipp::option("-h", "--help").set(help).doc("Display this help message")

        );

    if (!clipp::parse(argc, argv, cli)) {
        std::cerr << clipp::make_man_page(cli, argv[0]);
        return 1;
    }

    if (exporter){

        DatabaseManager sDB(source_db, logger);

        std::map<int, User> users;
        User::loadUsers(sDB, users, logger);
        //User::saveUsersToFile(user_file, users);
        SaveAndLoadToFile<User>::saveToFile(user_file, users, logger);

        std::map<int, Group> groups;
        Group::loadGroups(sDB, groups, logger);
        //Group::saveGroupsToFile(group_file, groups);
        SaveAndLoadToFile<Group>::saveToFile(group_file, groups, logger);

        std::map<int, DetailPersonalInfo> DetailPersonalInfol;
        DetailPersonalInfo::loadDetailPersonalInfo(sDB, DetailPersonalInfol, logger);
        //DetailPersonalInfo::saveDetailPersonalInfosToFile(DetailPersonalInfo_file,DetailPersonalInfol);
        SaveAndLoadToFile<DetailPersonalInfo>::saveToFile(DetailPersonalInfo_file, DetailPersonalInfol, logger);
        return 0;
    }
    else if (importer){
        DatabaseManager tDB(target_db, logger);

        std::map<int, User> luser;
        SaveAndLoadToFile<User>::loadFromFile(user_file, luser, logger);

        std::map<int, Group> lgroup;
        SaveAndLoadToFile<Group>::loadFromFile(group_file, lgroup, logger);

        std::map<int, DetailPersonalInfo> lDetailPersonalInfo;
        std::unordered_map<int, int> update_groupID;
        SaveAndLoadToFile<DetailPersonalInfo>::loadFromFile(DetailPersonalInfo_file, lDetailPersonalInfo, logger);

        Group::saveGroupsToDatabase(tDB, lgroup, update_groupID, logger);
        User::saveUsersToDatabase(tDB, luser, lDetailPersonalInfo, update_groupID, logger);
        DetailPersonalInfo::saveDetailPersonalInfosToDatabase(tDB, lDetailPersonalInfo, logger);
        return 0;
    }

    if (help) {
        std::cout << "Usage:\n\n" << clipp::usage_lines(cli, "ServiceApp") << "\n\n\n\n";
        std::cout << "Detailed Documentation:\n\n" << clipp::documentation(cli) << "\n\n";

        return 0;
    }



    return 0;

}
