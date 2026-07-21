#ifndef GAME_HPP
#define GAME_HPP

// For Ctx objects
#include "physics/GamePhysicsBackend.hpp"
#include "render_backend/RenderBackend.hpp"

// Update systems
#include "systems/PhysicsComponentUpdater.hpp"
#include "systems/PhysicsToTransformSyncer.hpp"
#include "systems/TransformToKinematicSyncer.hpp"
#include "systems/VelocitySystem.hpp"

// Destroyer systems
#include "systems/PhysicsComponentDestroyer.hpp"

#include <entt/entt.hpp>
#include <iostream>
#include <thread>

namespace RlClone {


class Game {
protected:
    entt::registry entity_registry;

    // Update systems
    RlClone::VelocitySystem velocity_system;
    RlClone::TransformToKinematicSyncer transform_to_kinematic_syncer;
    RlClone::PhysicsComponentUpdater physics_component_updater;
    RlClone::PhysicsToTransformSyncer physics_to_transform_syncer;

    // Destroyer systems
    RlClone::PhysicsComponentDestroyer physics_component_destroyer;
public:
    /*!
     * \brief Creates the game object
     * * \details
     * Initializes raylib main window
     * Creates systems
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
        const uint AllocatorMaxSize = (10 * 1024 * 1024),
        const uint cMaxBodies = 1024,
        const uint cNumBodyMutexes = 0,
        const uint cMaxBodyPairs = 1024,
        const uint cMaxContactConstraints = 1024);
    ~Game();


    static const constexpr float delta_time = 1.0f / 60.0f;

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
