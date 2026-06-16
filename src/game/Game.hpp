#ifndef GAME_HPP
#define GAME_HPP

// For the physics backend
#include <core/physics/GamePhysicsBackend.hpp>

// For asset manager
#include <game/AssetManager.hpp>

// For Render3D System
#include <game/systems/Render3DSystem.hpp>

// For Physics System
#include <game/systems/PhysicsSystem.hpp>

// For entity component system
#include <entt/entt.hpp>

// For rendering and audio
#include <raylib.h>

// For std::cout std::endl
#include <iostream>


namespace RlClone {


class Game {
protected:
    entt::registry entity_registry;
    RlClone::AssetManager asset_manager;
    RlClone::PhysicsBackend::GamePhysicsBackend game_physics_backend;

  
    RlClone::Render3DSystem render_3d_system;
    RlClone::PhysicsSystem physics_system;

  
public:
    Game(
        const uint AllocatorMaxSize = (1024 * 1024 * 10),
        const uint cMaxBodies = 1024,
        const uint cNumBodyMutexes = 0,
        const uint cMaxBodyPairs = 1024,
        const uint cMaxContactConstraints = 1024);
    ~Game();


    static const constexpr float delta_time = 1 / 60;

  
    void Run();
};


} // namespace RlClone


#endif
