target_include_directories(RevEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(RevEngine PRIVATE core)    
target_include_directories(RevEngine PRIVATE game)
            
target_sources(RevEngine PRIVATE main.cpp)

add_subdirectory(core)
add_subdirectory(game)    
