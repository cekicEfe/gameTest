#pragma once // I am not writing a lot this time

// BEGONE FORMATTER
#include <Jolt/Jolt.h>
// BEGONE FORMATTER
#include <Jolt/Core/JobSystemThreadPool.h> // For JPH::JobSystemThreadPool
#include <Jolt/Core/TempAllocator.h> // For JPH::TempAllocatorImpl
#include <Jolt/Physics/Body/BodyInterface.h> // For JPH::BodyInterface
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem
#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>

// For Entity Component System
#include <entt/entt.hpp>

// For reference_wrapper
#include <functional>

// For nullopt
#include <optional>

// For rendering
#include <raylib.h>

// For asset manager
#include <game/AssetManager.hpp>

// For core components which is a natural prequisite of the ecs
#include <game/components/CoreComponents.hpp>


namespace RlClone::Demo {


class DemoCharacterCreatorSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
    std::reference_wrapper<JPH::PhysicsSystem> physics_system_ref;
    std::reference_wrapper<RlClone::AssetManager> asset_manager_ref;
public:
    DemoCharacterCreatorSystem(
        entt::registry& entity_registry_ref,
        JPH::PhysicsSystem& physics_system_ref,
        RlClone::AssetManager& asset_manager_ref);


    ~DemoCharacterCreatorSystem();


    void SetUp();


    void CleanUp();
};


}; // namespace RlClone::Demo
