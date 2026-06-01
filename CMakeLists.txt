cmake_minimum_required(VERSION 3.20)
    
project(RevEngine)
        
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -g")
    
add_subdirectory(src)
add_subdirectory($ENV{JOLT_REPO}/Build/ include/Jolt)

target_compile_options(Jolt PRIVATE
    -Wno-array-bounds
)

target_include_directories (
    RevEngine
    PUBLIC
    src/
    src/app/
    src/game/
    $ENV{JOLT_REPO}/
)

target_link_libraries(RevEngine PUBLIC Jolt raylib glfw vulkan)

target_compile_definitions(RevEngine PRIVATE
   USE_VULKAN_BACKEND #This is for the future renderer
   VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
   VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1
)
    
install(TARGETS RevEngine DESTINATION bin)
