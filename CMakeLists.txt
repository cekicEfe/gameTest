cmake_minimum_required(VERSION 3.20)

    
project(RevEngineProject)

    
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

    
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -g")

        
add_subdirectory($ENV{JOLT_REPO}/Build include/)    
target_compile_options(Jolt PRIVATE
    -Wno-array-bounds
)

    
set(RevEngineDependencies Jolt glfw raylib)     

    
add_executable(RevEngine)
    
target_include_directories(RevEngine PRIVATE $ENV{JOLT_REPO}/)
target_include_directories(RevEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    
add_subdirectory(src)
    
target_link_libraries(RevEngine PRIVATE ${RevEngineDependencies})

    
           
install(TARGETS RevEngine DESTINATION bin)
