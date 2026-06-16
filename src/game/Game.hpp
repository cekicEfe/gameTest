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

  
    RlClone::Render3DSystem render_3d_system;
    RlClone::PhysicsSystem physics_system;

  
public:

    /*!
     * \brief Creates the game object 
     * * \details 
     * Initializes raylib main window
     * Creates game physics backend
     * Creates asset manager
     * Creates the ecs Systems
     * Creates the main camera
     * 
     */
    Game(
        const uint AllocatorMaxSize = (1024 * 1024 * 10),
        const uint cMaxBodies = 1024,
        const uint cNumBodyMutexes = 0,
        const uint cMaxBodyPairs = 1024,
        const uint cMaxContactConstraints = 1024);
    ~Game();


    static const constexpr float delta_time = 1 / 60;

    /*!
     * \brief Runs the game loop
     * * \details
     * 1. Polls events
     * 2. Updates objects
     * 3. Renders renderables
     * 3.1 Renders 2d objects (like gui)
     * 3.2 Renders 3d objects (like characters)
     *
     * Note:
     * process 3.2 NEEDS RlClone::MainCameraComponent to exist in entity_registry.ctx()
     *
     * Does not throw an error on its own
     *
     */
    void Run();
};


} // namespace RlClone


#endif
