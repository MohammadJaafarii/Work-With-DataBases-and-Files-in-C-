cmake_minimum_required(VERSION 3.5)

project(PayamPardaz_Project1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Core Gui Sql Widgets REQUIRED)

add_executable(PayamPardaz_Project1 main.cpp)
target_link_libraries(PayamPardaz_Project1 Qt5::Core Qt5::Gui Qt5::Sql Qt5::Widgets)

include(GNUInstallDirs)
install(TARGETS PayamPardaz_Project1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
