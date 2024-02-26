cmake_minimum_required(VERSION 3.10)

project(Reactor_cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories("./")

file(GLOB_RECURSE SOURCES "utils/*.cpp")

add_executable(server ${SOURCES} main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(server PRIVATE Threads::Threads)

