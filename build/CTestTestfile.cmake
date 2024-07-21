# CMake generated Testfile for 
# Source directory: C:/Users/User/QTProjects/PayamPardaz_Project1
# Build directory: C:/Users/User/QTProjects/PayamPardaz_Project1/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(ValidationTest "C:/Users/User/QTProjects/PayamPardaz_Project1/build/Debug/validation_test.exe")
  set_tests_properties(ValidationTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/QTProjects/PayamPardaz_Project1/CMakeLists.txt;50;add_test;C:/Users/User/QTProjects/PayamPardaz_Project1/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(ValidationTest "C:/Users/User/QTProjects/PayamPardaz_Project1/build/Release/validation_test.exe")
  set_tests_properties(ValidationTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/QTProjects/PayamPardaz_Project1/CMakeLists.txt;50;add_test;C:/Users/User/QTProjects/PayamPardaz_Project1/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(ValidationTest "C:/Users/User/QTProjects/PayamPardaz_Project1/build/MinSizeRel/validation_test.exe")
  set_tests_properties(ValidationTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/QTProjects/PayamPardaz_Project1/CMakeLists.txt;50;add_test;C:/Users/User/QTProjects/PayamPardaz_Project1/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(ValidationTest "C:/Users/User/QTProjects/PayamPardaz_Project1/build/RelWithDebInfo/validation_test.exe")
  set_tests_properties(ValidationTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/QTProjects/PayamPardaz_Project1/CMakeLists.txt;50;add_test;C:/Users/User/QTProjects/PayamPardaz_Project1/CMakeLists.txt;0;")
else()
  add_test(ValidationTest NOT_AVAILABLE)
endif()
subdirs("spdlog")
subdirs("_deps/googletest-build")
