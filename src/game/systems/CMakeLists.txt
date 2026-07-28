# add_subdirectory(power_car_systems)

    
target_include_directories(RevEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

        
target_sources(RevEngine
    PRIVATE
    FollowCameraUpdater.cpp
    FollowCameraUpdater.hpp
    PhysicsComponentDestroyer.cpp
    PhysicsComponentDestroyer.hpp
    PhysicsComponentUpdater.cpp
    PhysicsComponentUpdater.hpp
    PhysicsToTransformSyncer.cpp
    PhysicsToTransformSyncer.hpp
    SceneTransformSyncer.cpp
    SceneTransformSyncer.hpp
    TransformToKinematicSyncer.cpp
    TransformToKinematicSyncer.hpp
    VelocitySystem.cpp
    VelocitySystem.hpp)
