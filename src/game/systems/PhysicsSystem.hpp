#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

// BEGONE FORMATTER
#include <Jolt/Jolt.h>
// BEGONE FORMATTER
#include <Jolt/Core/JobSystemThreadPool.h> // For JPH::JobSystemThreadPool
#include <Jolt/Core/TempAllocator.h> // For JPH::TempAllocatorImpl
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem
#include <Jolt/Physics/Body/BodyInterface.h> // For JPH::BodyInterface

// For Entity Component System
#include <entt/entt.hpp>

// For reference_wrapper
#include <functional>

// For core components which is a natural prequisite of the ecs
#include <game/components/CoreComponents.hpp>


namespace RlClone {

  
class PhysicsSystem {
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
    ~PhysicsSystem();


    void Update(const float delta_time);
    void CleanUp();
};

  
} // namespace RlClone

#endif
