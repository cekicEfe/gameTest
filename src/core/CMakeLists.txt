target_include_directories(RevEngine PRIVATE physics)
target_include_directories(RevEngine PRIVATE render_backend)    
target_include_directories(RevEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
        
add_subdirectory(physics)
add_subdirectory(render_backend)
