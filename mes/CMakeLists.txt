cmake_minimum_required(VERSION 3.10)
project(II)

# Set C++ version
#set(CMAKE_CXX_STANDARD 17)

#Turn on warnings
#set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Wall")

#Set your directories
set(SOURCE_DIR src)

# Include directories
include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE HEADER_FILES ${SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} pq pqxx)
