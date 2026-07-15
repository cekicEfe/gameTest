#ifndef GAME_HPP
#define GAME_HPP

// For asset manager
#include "AssetManager.hpp"

// For the physics backend
#include "GamePhysicsBackend.hpp"

#include "Render3DSystem.hpp"
#include "TransformToKinematicSyncer.hpp"
#include "PhysicsToTransformSyncer.hpp"
#include "VelocitySystem.hpp"

// For entity component system
#include <entt/entt.hpp>

// For rendering and audio


// For std::cout std::endl
#include <iostream>

namespace RlClone {


class Game {
protected:
    entt::registry entity_registry;

    RlClone::Render3DSystem render_3d_system;
    RlClone::TransformToKinematicSyncer transform_to_kinematic_syncer;
    RlClone::PhysicsToTransformSyncer physics_to_transform_syncer;
    RlClone::VelocitySystem velocity_system;
  
public:

    /*!
     * \brief Creates the game object 
     * * \details 
     * Initializes raylib main window
     * Creates game physics backend 
     * Creates asset manager
     * Creates the ecs Systems 
     * Creates the main camera 
     * The game is ran on 60 fps static
     *
     * Important:
     * physicsbackend,
     * asset manager,
     * main camera,
     * will exist during programs lifetime.
     *
     */
    Game(
        const uint AllocatorMaxSize = (1024 * 1024 * 10),
        const uint cMaxBodies = 1024,
        const uint cNumBodyMutexes = 0,
        const uint cMaxBodyPairs = 1024,
        const uint cMaxContactConstraints = 1024);
    ~Game();


    static const constexpr float delta_time = 1.0f/60.0f;

    /*!
     * \brief Runs the game loop
     * * \details
     * 1. Polls events
     * 2. Updates objects
     * 3. Renders renderables entities
     * 3.1 Renders 2d objects
     * 3.2 Renders 3d objects
     *
     */
    void Run();
};


} // namespace RlClone


#endif
