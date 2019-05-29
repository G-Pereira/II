cmake_minimum_required(VERSION 2.8)
project(database)

set(CMAKE_CXX_STANDARD 14)

add_executable(database main.cpp Database.cpp Database.h)

target_link_libraries (database pqxx pq)