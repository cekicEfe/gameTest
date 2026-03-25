cmake_minimum_required(VERSION 3.16)
project(JoltTemplate LANGUAGES CXX)


# Force Clang/Ninja users to use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Jolt Configuration Options
# We enable SIMD (SSE4.2/AVX) for performance; ensure your CPU supports it.
set(TARGET_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(TARGET_SAMPLES OFF CACHE BOOL "" FORCE)

# Add Jolt as a subdirectory
# Note: You must have the Jolt source in 'extern/JoltPhysics'
add_subdirectory(extern/JoltPhysics/Build/)

# Our Main Executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link Jolt and its dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE Jolt)

# Jolt requires specific defines to work correctly
# target_compile_definitions(${PROJECT_NAME} PRIVATE
#     JPH_DEBUG_RENDERER
#     JPH_PROFILE_ENABLED
# )
