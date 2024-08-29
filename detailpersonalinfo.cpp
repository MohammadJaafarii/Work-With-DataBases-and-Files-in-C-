#include "detailpersonalinfo.h"
#include <string>
#include <locale>
#include <codecvt>


DetailPersonalInfo::DetailPersonalInfo() {}

DetailPersonalInfo::    DetailPersonalInfo(int UserID, wchar_t FirstName [101], wchar_t LastName [101] , wchar_t Office [101],wchar_t Phone[21],
                                       wchar_t PersonnelCode [11], wchar_t Address [1001]){
    try{

        this->ID = UserID;

        std::wmemset(this->FirstName, 0, sizeof(this->FirstName) / sizeof(this->FirstName[0]));
        size_t len_fname = std::wcslen(FirstName);
        std::wcsncpy(this->FirstName, FirstName, len_fname);
        this->FirstName[len_fname] = L'\0';

        std::wmemset(this->LastName, 0, sizeof(this->LastName) / sizeof(this->LastName[0]));
        size_t len_lname = std::wcslen(LastName);
        std::wcsncpy(this->LastName, LastName, len_lname);
        this->LastName[len_lname] = L'\0';

        std::wmemset(this->Office, 0, sizeof(this->Office) / sizeof(this->Office[0]));
        size_t len_office = std::wcslen(Office);
        std::wcsncpy(this->Office, Office, len_office);
        this->Office[len_office] = L'\0';

        std::wmemset(this->Phone, 0, sizeof(this->Phone) / sizeof(this->Phone[0]));
        size_t len_phone = std::wcslen(Phone);
        std::wcsncpy(this->Phone, Phone, len_phone);
        this->Phone[len_phone] = L'\0';

        std::wmemset(this->PersonnelCode, 0, sizeof(this->PersonnelCode) / sizeof(this->PersonnelCode[0]));
        size_t len_personnelcode = std::wcslen(PersonnelCode);
        std::wcsncpy(this->PersonnelCode, PersonnelCode, len_personnelcode);
        this->PersonnelCode[len_personnelcode] = L'\0';

        std::wmemset(this->Address, 0, sizeof(this->Address) / sizeof(this->Address[0]));
        size_t len_address = std::wcslen(Address);
        std::wcsncpy(this->Address, Address, len_address);
        this->Address[len_address] = L'\0';

    }

    catch(...){

        qDebug() << "Error occured while setting value for DetailPersonalInfo object";

    }
}


using DetailInfo = std::map<int, DetailPersonalInfo>;

DetailInfo DetailPersonalInfo::loadDetailPersonalInfo(DatabaseManager& dbManager,
                                         DetailInfo& details, Logger& logger) {

    try{
        logger.info("______________________________DetailPersonalInfo (loadDetailPersonalInfo function)______________________________");

        const QString query_command = "SELECT * FROM 'DetailPersonalInfo'";
        QSqlQuery query = dbManager.executeQuery(query_command);
        while (query.next()) {
            int userID = query.value(0).toInt();

            std::string firstName = query.value(1).toString().toStdString();
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring fnsource = converter.from_bytes(firstName);
            wchar_t firstName_c[101];
            //std::wmemset(name_c, 0, sizeof(name_c));
            size_t fname_len = fnsource.size();
            std::wcsncpy(firstName_c, fnsource.c_str(), fname_len);
            firstName_c[fname_len] = L'\0';

            std::string lastName = query.value(2).toString().toStdString();
            std::wstring lnsource = converter.from_bytes(lastName);
            wchar_t lastName_c[101];
            //std::wmemset(name_c, 0, sizeof(name_c));
            size_t lname_len = lnsource.size();
            std::wcsncpy(lastName_c, lnsource.c_str(), lname_len);
            lastName_c[lname_len] = L'\0';

            std::string office = query.value(3).toString().toStdString();
            std::wstring office_source = converter.from_bytes(office);
            wchar_t office_c[101];
            //std::wmemset(name_c, 0, sizeof(name_c));
            size_t office_len = office_source.size();
            std::wcsncpy(office_c, office_source.c_str(), office_len);
            office_c[office_len] = L'\0';

            std::string phone = query.value(4).toString().toStdString();
            std::wstring phone_source = converter.from_bytes(phone);
            wchar_t phone_c[21];
            //std::wmemset(name_c, 0, sizeof(name_c));
            size_t phone_len = phone_source.size();
            std::wcsncpy(phone_c, phone_source.c_str(), phone_len);
            phone_c[phone_len] = L'\0';

            std::string personnelCode = query.value(5).toString().toStdString();
            std::wstring personnelCode_source = converter.from_bytes(personnelCode);
            wchar_t personnelCode_c[11];
            //std::wmemset(name_c, 0, sizeof(name_c));
            size_t pc_len = personnelCode_source.size();
            std::wcsncpy(personnelCode_c, personnelCode_source.c_str(), pc_len);
            personnelCode_c[pc_len] = L'\0';

            std::string address = query.value(6).toString().toStdString();
            std::wstring address_source = converter.from_bytes(address);
            wchar_t address_c[1001];
            //std::wmemset(name_c, 0, sizeof(name_c));
            size_t address_len = address_source.size();
            std::wcsncpy(address_c, address_source.c_str(), address_len);
            address_c[address_len] = L'\0';


            details[userID] = (DetailPersonalInfo {userID, firstName_c, lastName_c, office_c, phone_c, personnelCode_c, address_c});
        }
        logger.info("DetailPersonalInfos are Loaded successfully from Database!");
        return details;
    }

    catch(...){
        logger.error("Error Occurred while loading 'DetailPersonalInfo' Data from Database");
        exit(1);
    }

}

void DetailPersonalInfo::saveDetailPersonalInfosToDatabase(DatabaseManager& dbManager, const DetailInfo& details, Logger& logger) {



    try{
        int success = 0,
            failed = 0;
        logger.info("______________________________DetailPersonalInfo (saveDetailPersonalInfosToDatabase function)______________________________");

        for (const auto& pair : details) {
            int userID = pair.first;
            const DetailPersonalInfo& detail = pair.second;




            QSqlQuery query;
            query.prepare("INSERT INTO 'DetailPersonalInfo' (userid, firstname, lastname, office, phone, personnelcode, address) "
                          "VALUES (:UserID, :FirstName, :LastName, :Office, :Phone, :PersonnelCode, :Address)");

            query.bindValue(":UserID", detail.ID);
            query.bindValue(":FirstName", std::wcslen(detail.FirstName) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.FirstName));
            query.bindValue(":LastName", std::wcslen(detail.LastName) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.LastName));
            query.bindValue(":Office", std::wcslen(detail.Office) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.Office));
            query.bindValue(":Phone", std::wcslen(detail.Phone) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.Phone));
            query.bindValue(":PersonnelCode", std::wcslen(detail.PersonnelCode) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.PersonnelCode));
            query.bindValue(":Address", std::wcslen(detail.Address) == 0 ? QVariant(QVariant::String) : QString::fromWCharArray(detail.Address));

            if (!query.exec()) {
                logger.error("Error inserting data into DetailPersonalInfo: " + query.lastError().text() + " for UserID: " + QString::number(userID));
                failed ++;
                continue;
            } else {
                success ++;

            }

        }
        logger.info(QString::number(success) + " Items are inserted successfuly and " + QString::number(failed) + " Items failed to be inserted!");
    }
    catch (...) {
        logger.error("Error occurred while saving DetailPersonalInfos to database.");
    }

}







