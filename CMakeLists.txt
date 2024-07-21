cmake_minimum_required(VERSION 3.5)

project(PayamPardaz_Project1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # Use C++17 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt5 Configuration (adjust paths if necessary)
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")
find_package(Qt5 REQUIRED COMPONENTS Core Sql)
set(Qt5_DIR "C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")

# spdlog Integration
add_subdirectory(spdlog)  # Assuming spdlog is a subdirectory with CMakeLists.txt

# gtest Integration (FetchContent approach)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Validation Library
add_library(validation STATIC validation.h validation.cpp)

# Main Executable
add_executable(PayamPardaz_Project1
               main.cpp
               databasemanager.h databasemanager.cpp
               saveandloadtofile.h
               user.h user.cpp
               group.h group.cpp
               detailpersonalinfo.h detailpersonalinfo.cpp
               logger.h logger.cpp
               ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/DetailPersonalInfo.dat ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/Group.dat ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/Log.txt ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/sourceDB.db ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/targetDB.db ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/User.dat)

target_link_libraries(PayamPardaz_Project1
                     Qt5::Core Qt5::Sql
                     spdlog::spdlog
                     validation)

# Unit Tests
add_executable(validation_test validation_test.cpp validation_test.h)
target_link_libraries(validation_test gtest_main gtest validation)

add_test(NAME ValidationTest COMMAND validation_test)
