cmake_minimum_required(VERSION 3.16)
project(JoltTemplate LANGUAGES CXX)

# Force Clang/Ninja users to use modern C++
set(CMAKE_CXX_STANDARD 20)
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
add_executable(${PROJECT_NAME}
  src/main.cpp
  
  src/game/game.hpp
  src/game/game.cpp
  
  src/app/app.cpp  
  src/app/app.hpp

  src/core/render/vulkan_backend.cpp
  src/core/render/vulkan_backend.hpp

  src/core/render/render.hpp
  src/core/render/render.cpp
    
  src/core/render/backend_interface.hpp
)

# Link Jolt and its dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC Jolt raylib glfw vulkan)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  extern/JoltPhysics/Jolt
  
  src/app
  src/game
  src/core/render
)
    
target_compile_definitions(${PROJECT_NAME} PRIVATE
   USE_VULKAN_BACKEND
   VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
   VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1
)

# Jolt requires specific defines to work correctly
# target_compile_definitions(${PROJECT_NAME} PRIVATE
#     JPH_DEBUG_RENDERER
#     JPH_PROFILE_ENABLED
# )
# JPH_DOUBLE_PRECISION use this for big worlds
