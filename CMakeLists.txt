cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER "clang++")

project(CENG C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES  
  ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/*.c
  ${CMAKE_CURRENT_LIST_DIR}/src/*.h
  ${CMAKE_CURRENT_LIST_DIR}/src/*.hpp
)
               
add_executable(MAIN_EXEC ${SOURCES})

target_compile_options(MAIN_EXEC PUBLIC -std=c++17 -Wall -g)

target_link_libraries(MAIN_EXEC
  Jolt
)

target_include_directories(MAIN_EXEC PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
)


