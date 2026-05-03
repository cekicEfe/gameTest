#ifndef GAME_HPP
#define GAME_HPP


// STL includes
#include <iostream>
#include <thread>


// The physics backend
#include <game/game_physics_backend.hpp>


// For entity component system
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace raylib {
#include <raylib.h>
};


// All Jolt symbols are in the JPH namespace
using namespace JPH;


// If you want your code to compile using single or double precision write 0.0_r
// to get a Real value that compiles to double or float depending if
// JPH_DOUBLE_PRECISION is set or not.
using namespace JPH::literals;


namespace RlClone {

  
struct GameConfig {};  

  
class Game {
private:
    PhysicsBackend::GamePhysicsBackend game_physics_backend;
    entt::registry entity_registry;
    raylib::Camera3D main_camera;
  
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

  
    void InitDemo();
    void CleanupDemo();
};

  
} // namespace RlClone


#endif
