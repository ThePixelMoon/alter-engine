cmake_minimum_required(VERSION 3.10)

project(alter-engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(alter-engine ${SOURCES})

# wow..
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include) # for .h files

link_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/SDL2.lib)