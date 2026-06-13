#ifndef CORE_SYSTEMS_HPP
#define CORE_SYSTEMS_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem

// For reference_wrapper
#include <functional>

// For Entity Component System
#include <entt/entt.hpp>

// For core components which is a natural prequisite of the ecs
#include <game/components/CoreComponents.hpp>

// For asset manager
#include <game/AssetManager.hpp>

// For rendering and shit
namespace raylib {
#include <raylib.h>
};


namespace RlClone {


class AbstractSystem {
protected:
    std::reference_wrapper<JPH::PhysicsSystem> physics_system_ref;
    std::reference_wrapper<entt::registry> entity_registry_ref;
    std::reference_wrapper<RlClone::AssetManager> asset_manager_ref;
public:
    AbstractSystem(
        JPH::PhysicsSystem& physics_system_ref,
        entt::registry& entity_registry_ref,
        RlClone::AssetManager& asset_manager_ref);
    virtual ~AbstractSystem() {};
    virtual void Update(const float delta_time) {};
};


class RenderSystem : public RlClone::AbstractSystem {
public:
    RenderSystem(
        JPH::PhysicsSystem& physics_system_ref,
        entt::registry& entity_registry_ref,
        RlClone::AssetManager& asset_manager_ref);
    virtual ~RenderSystem() override;

    virtual void Update(const float delta_time) override;
};


} // namespace RlClone


#endif
