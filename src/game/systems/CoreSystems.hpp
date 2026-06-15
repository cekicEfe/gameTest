#ifndef CORE_SYSTEMS_HPP
#define CORE_SYSTEMS_HPP

// BEGONE FORMATTER
#include <Jolt/Jolt.h>
// BEGONE FORMATTER
#include <Jolt/Core/JobSystemThreadPool.h> // For JPH::JobSystemThreadPool
#include <Jolt/Core/TempAllocator.h> // For JPH::TempAllocatorImpl
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem

// For Entity Component System
#include <entt/entt.hpp>

// For core components which is a natural prequisite of the ecs
#include <game/components/CoreComponents.hpp>

// For asset manager
#include <game/AssetManager.hpp>

// For unique_ptr
#include <memory>

// For std::move
#include <utility>

// For reference_wrapper
#include <functional>

// For rendering
#include <raylib.h>

// For nullopt
#include <optional>

namespace RlClone {


class AbstractSystem {
public:
    AbstractSystem();
    virtual ~AbstractSystem() = 0;


    virtual void Update(const float delta_time) = 0;
};


class Render3DSystem : public RlClone::AbstractSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
    std::reference_wrapper<RlClone::AssetManager> asset_manager_ref;
public:
    Render3DSystem(entt::registry& entity_registry_ref, RlClone::AssetManager& asset_manager_ref);
    virtual ~Render3DSystem() override;


    virtual void Update(const float delta_time) override;
};


class PhysicsSystem : public RlClone::AbstractSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
    std::reference_wrapper<JPH::PhysicsSystem> physics_system_ref;
    std::reference_wrapper<JPH::TempAllocatorImpl> temp_allocator_ref;
    std::reference_wrapper<JPH::JobSystemThreadPool> job_system_ref;
public:
    PhysicsSystem(
        entt::registry& entity_registry_ref,
        JPH::PhysicsSystem& physics_system_ref,
        JPH::TempAllocatorImpl& temp_allocator_ref,
        JPH::JobSystemThreadPool& job_system_ref);
    virtual ~PhysicsSystem() override;


    virtual void Update(const float delta_time) override;
};


} // namespace RlClone


#endif
