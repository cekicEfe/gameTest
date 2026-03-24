cmake_minimum_required(VERSION 3.20)

project(JoltExample C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(MAIN_EXEC ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)

target_link_libraries(MAIN_EXEC
  Jolt
)

target_include_directories(MAIN_EXEC PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
)
