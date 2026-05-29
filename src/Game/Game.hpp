#ifndef GAME_HPP
#define GAME_HPP

// For entity component system
#include <entt/entt.hpp>

// For random number gen
#include <random>

// For Car 
#include <Game/Car.hpp>

// For the physics backend
#include <Game/GamePhysicsBackend.hpp>

namespace raylib {
#include <raylib.h>
};

namespace RlClone {

struct GameConfig {};
class Game {
private:
    PhysicsBackend::GamePhysicsBackend game_physics_backend;
    entt::registry entity_registry;
public:
    Game(
        const uint AllocatorMaxSize = (1024 * 1024 * 10),
        const uint cMaxBodies = 1024,
        const uint cNumBodyMutexes = 0,
        const uint cMaxBodyPairs = 1024,
        const uint cMaxContactConstraints = 1024);
    Game(GameConfig config);
    ~Game();

    void Init();
    void Cleanup();

    void MainLoop();
    bool ShouldGameStop();
    void Update();
    void Render();
};

} // namespace RlClone

#endif
