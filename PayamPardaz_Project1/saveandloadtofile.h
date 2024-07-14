#ifndef SAVEANDLOADTOFILE_H
#define SAVEANDLOADTOFILE_H
#include <iostream>
#include <map>
#include <cwchar>
#include <locale>
#include <codecvt>
#include <fstream> // Ensure fstream is included
#include <iostream>

template <class T>
class SaveAndLoadToFile
{
public:

    static void saveToFile(const std::string& fileName, std::map<int, T> & infos){
        try {
            std::ofstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "Error opening file for writing: " << fileName << std::endl;
                return;
            }
            for(auto [_, info] : infos) {
                file.write(reinterpret_cast<const char*>(&info), sizeof(info));
            }

            std::cout << "Users saved to file " << fileName << " successfully." << std::endl;
            file.close();
        }
        catch (...) {
            std::cerr << "Error occurred while saving users to file." << std::endl;
        }
    }
    //template <typename T>
    static void loadFromFile(const std::string& fileName, std::map<int, T> & infos){
        try {
            std::ifstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "Error: Unable to open file for reading " << fileName << std::endl;
                return;
            }

            T info;
            while (file.read(reinterpret_cast<char*>(&info), sizeof(info))) {
                infos[info.ID] = info;
            }

            file.close();
            std::cout << "Loaded groups from file: " << fileName << std::endl;
        }
        catch (...) {
            std::cerr << "Error occurred while loading users from file." << std::endl;
        }
    }


};

//template class SaveAndLoadToFile<class T>;

#endif // SAVEANDLOADTOFILE_H
