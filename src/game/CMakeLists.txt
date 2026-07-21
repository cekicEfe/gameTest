add_subdirectory(components)
add_subdirectory(entity_builders)
add_subdirectory(events)
add_subdirectory(systems)

    
target_include_directories(RevEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    
target_include_directories(RevEngine
    PRIVATE
    components
    entity_builders
    events
    systems)    


target_sources(RevEngine
    PRIVATE
    Game.hpp
    Game.cpp)
        
