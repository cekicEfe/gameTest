#ifndef GAME_HPP
#define GAME_HPP

// For asset manager
#include <game/AssetManager.hpp>

// For ecs core systems
#include <game/systems/CoreSystems.hpp>

// For the physics backend
#include <core/physics/GamePhysicsBackend.hpp>

// For entity component system
#include <entt/entt.hpp>

// For std::cout std::endl
#include <iostream>

namespace raylib {
#include <raylib.h>
};


namespace RlClone {

class Game {
private:
    PhysicsBackend::GamePhysicsBackend game_physics_backend;
    entt::registry entity_registry;
    RlClone::AssetManager asset_manager;

    RenderSystem render_system;
public:
    Game(
        const uint AllocatorMaxSize = (1024 * 1024 * 10),
        const uint cMaxBodies = 1024,
        const uint cNumBodyMutexes = 0,
        const uint cMaxBodyPairs = 1024,
        const uint cMaxContactConstraints = 1024);
    ~Game();

    static const constexpr float delta_time = 1 / 60;

    void Init();
    void Cleanup();

    void MainLoop();
    bool ShouldGameStop();
    void Update();
    void Render();
};


} // namespace RlClone


#endif
