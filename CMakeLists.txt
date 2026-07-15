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

        
add_subdirectory($ENV{JOLT_REPO}/Build include/)    
target_compile_options(Jolt PRIVATE
    -Wno-array-bounds
)

    
set(CoreDependencies Jolt glfw raylib)     


set(CoreIncludeDirs
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/src/core/physics/
    
    ${CMAKE_SOURCE_DIR}/src/game/
    
    ${CMAKE_SOURCE_DIR}/src/game/systems/
    
    ${CMAKE_SOURCE_DIR}/src/game/components/
    ${CMAKE_SOURCE_DIR}/src/game/entity_builders/
            
    $ENV{JOLT_REPO}/
)

    
set(EngineCoreFiles
    core/physics/GamePhysicsBackend.hpp
    core/physics/GamePhysicsBackend.cpp
    core/physics/Listener.hpp
    core/physics/Listener.cpp    
    core/physics/Layers.hpp
    core/physics/Layers.cpp
    game/systems/PhysicsToTransformSyncer.hpp
    game/systems/PhysicsToTransformSyncer.cpp
    game/systems/TransformToKinematicSyncer.hpp
    game/systems/TransformToKinematicSyncer.cpp
    game/systems/Render3DSystem.hpp    
    game/systems/Render3DSystem.cpp
    game/systems/VelocitySystem.hpp
    game/systems/VelocitySystem.cpp
    game/systems/PowerCarCreatorSystem.hpp
    game/systems/PowerCarCreatorSystem.cpp
    game/components/CoreComponents.hpp
    game/entity_builders/AbstractCar.hpp    
    game/entity_builders/PowerCarBuilder.hpp
    game/entity_builders/PowerCarBuilder.cpp
    game/AssetManager.hpp
    game/AssetManager.cpp
    game/Game.hpp
    game/Game.cpp
)
        
    
# For main RevEngineCore library        
add_subdirectory(src) 
    

add_executable(RevEngine
    src/main.cpp    
)


target_include_directories (
    RevEngine    
    PUBLIC
    ${CoreIncludeDirs}
)


target_link_libraries(RevEngine PUBLIC ${CoreDependencies} RevEngineCore)    

       
install(TARGETS RevEngine DESTINATION bin)
