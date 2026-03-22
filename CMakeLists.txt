cmake_minimum_required(VERSION 3.5)

project(TEST_GAME C CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MAIN_SOURCES
)
               
add_executable(MAIN_EXEC
  ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
  ${MAIN_SOURCES}
)

target_link_libraries(MAIN_EXEC
  flecs
)

target_compile_options(MAIN_EXEC PUBLIC -Wall -g)

target_include_directories(MAIN_EXEC PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)


