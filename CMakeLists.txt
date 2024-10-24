cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(hashcrack)

add_executable(hashcrack)
file(GLOB_RECURSE HASHCRACK_SOURCES src/*.cpp)
target_sources(hashcrack PRIVATE ${HASHCRACK_SOURCES})
target_include_directories(hashcrack PRIVATE include)

add_subdirectory(lib/light-cli)
target_link_libraries(hashcrack PRIVATE light-cli)