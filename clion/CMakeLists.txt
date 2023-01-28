cmake_minimum_required(VERSION 3.23)
project(clion)
add_executable(clion main.cpp test.cpp base64.cpp base64.h userOperation.h mysqlOperation.h /usr/include/mysql/mysql.h json.hpp constructOperation.h tokenOperation.h tool.h judgeOperation.h poolOperation.h logOperation.h)
target_link_libraries(clion pthread seccomp)