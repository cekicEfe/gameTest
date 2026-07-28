#ifndef GAME_HPP
#define GAME_HPP

// For utils
#include "utils/BaseCameraUtils.hpp"

// For important entity builders
#include "entity_builders/BaseCameraBuilder.hpp"

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

namespace RlClone {


class Game {
private:
    entt::registry entity_registry;

    // Update systems
    RlClone::VelocitySystem velocity_system;
    RlClone::TransformToKinematicSyncer transform_to_kinematic_syncer;
    RlClone::PhysicsComponentUpdater physics_component_updater;
    RlClone::PhysicsToTransformSyncer physics_to_transform_syncer;

    // Destroyer systems
    RlClone::PhysicsComponentDestroyer physics_component_destroyer;

    bool is_running = true;
public:
    /*!
     * \brief Creates the game object
     * * \details
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
     */
    void Run();
};


} // namespace RlClone


#endif
