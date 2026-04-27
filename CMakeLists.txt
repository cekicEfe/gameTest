cmake_minimum_required(VERSION 3.20)

project(RevEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Jolt Configuration Options
# We enable SIMD (SSE4.2/AVX) for performance; ensure your CPU supports it.
set(TARGET_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(TARGET_SAMPLES OFF CACHE BOOL "" FORCE)
    
add_subdirectory(src)
add_subdirectory($ENV{JOLT_REPO}/Build/ include/)

target_include_directories (
    RevEngine
    PUBLIC
    src/
    src/app/
    #src/core/render/
    #src/game/
)
    
target_link_libraries(RevEngine PUBLIC Jolt raylib glfw vulkan)

target_compile_definitions(RevEngine PRIVATE
   USE_VULKAN_BACKEND
   VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
   VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1
   #JPH_EXTERNAL_PROFILE=1
   #JPH_PROFILE_ENABLED=0
)
            
install(TARGETS RevEngine DESTINATION bin)
