target_include_directories(RevEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    
target_sources(RevEngine PRIVATE
    AbstractCar.hpp
    DirectionSphereBuilder.cpp
    DirectionSphereBuilder.hpp
    PowerCarBuilder.cpp
    PowerCarBuilder.hpp)

