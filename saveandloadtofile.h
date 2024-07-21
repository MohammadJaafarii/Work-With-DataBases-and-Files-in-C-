#ifndef SAVEANDLOADTOFILE_H
#define SAVEANDLOADTOFILE_H
#include <iostream>
#include <map>
#include <cwchar>
#include <locale>
#include <codecvt>
#include <fstream>
#include <iostream>
#include "logger.h"

template <class T>
class SaveAndLoadToFile
{
public:

    static void saveToFile(const std::string& fileName, std::map<int, T> & infos, Logger& logger){
        try {
            std::ofstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                logger.error("Error opening file for writing: " + QString::fromStdString(fileName));
                return;
            }
            for(auto [_, info] : infos) {
                file.write(reinterpret_cast<const char*>(&info), sizeof(info));
            }

            logger.info("Informations saved to file '" + QString::fromStdString(fileName) + "' successfully.");
            file.close();
        }
        catch (...) {
            logger.error("Error occurred while saving Informations to file.");
        }
    }
    //template <typename T>
    static void loadFromFile(const std::string& fileName, std::map<int, T> & infos, Logger& logger){
        try {
            std::ifstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                logger.error("Error: Unable to open file for reading " + QString::fromStdString(fileName) );
                return;
            }

            T info;
            while (file.read(reinterpret_cast<char*>(&info), sizeof(info))) {
                infos[info.ID] = info;
            }

            file.close();
            logger.info("Informations are loaded from file: " + QString::fromStdString(fileName) + "successfully");
        }
        catch (...) {
            logger.error("Error occurred while loading Informations from file: '" + QString::fromStdString(fileName) + "'");
        }
    }


};

//template class SaveAndLoadToFile<class T>;

#endif // SAVEANDLOADTOFILE_H
