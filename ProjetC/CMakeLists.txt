cmake_minimum_required(VERSION 3.22.1)
project(ProjetC C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MYSQL REQUIRED mysqlclient)

include_directories(${MYSQL_INCLUDE_DIRS})
link_directories(${MYSQL_LIBRARY_DIRS})

add_executable(ProjetC main.c test.c db_connect.h
        db_connect.c
        db_operations.c)

target_link_libraries(ProjetC ${MYSQL_LIBRARIES})
