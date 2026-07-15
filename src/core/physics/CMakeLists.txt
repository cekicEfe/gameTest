target_include_directories(RevEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(RevEngine PRIVATE
    GamePhysicsBackend.cpp
    GamePhysicsBackend.hpp
    Layers.cpp
    Layers.hpp
    Listener.cpp
    Listener.hpp)

