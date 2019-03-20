# cmake_minimum_required(VERSION <specify CMake version here>)
project(database)

set(CMAKE_CXX_STANDARD 17)

add_executable(database main.cpp Database.cpp Database.h)