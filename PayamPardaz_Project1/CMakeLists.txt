cmake_minimum_required(VERSION 3.5)

project(PayamPardaz_Project1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Core Gui Sql Widgets REQUIRED)
add_subdirectory(spdlog)
add_subdirectory(googletest)

add_executable(PayamPardaz_Project1 main.cpp
    databasemanager.h databasemanager.cpp
    saveandloadtofile.h
    user.h user.cpp
    group.h group.cpp
    detailpersonalinfo.h detailpersonalinfo.cpp
    ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/DetailPersonalInfo.dat ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/Group.dat ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/sourceDB.db ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/targetDB.db ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/User.dat
    validation.h validation.cpp
    logger.h logger.cpp
    ../build-PayamPardaz_Project1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/Log.txt

)

target_link_libraries(PayamPardaz_Project1 PRIVATE
    Qt5::Core Qt5::Gui Qt5::Sql Qt5::Widgets
    spdlog::spdlog
)

include(GNUInstallDirs)
install(TARGETS PayamPardaz_Project1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
