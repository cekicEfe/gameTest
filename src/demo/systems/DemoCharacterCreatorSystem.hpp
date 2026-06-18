#ifndef DEMO_CHARACTER_CREATOR_SYSTEM_HPP
#define DEMO_CHARACTER_CREATOR_SYSTEM_HPP

// BEGONE FORMATTER
#include <Jolt/Jolt.h>
// BEGONE FORMATTER
#include <Jolt/Core/TempAllocator.h> // For JPH::TempAllocatorImpl
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem
#include <Jolt/Core/JobSystemThreadPool.h> // For JPH::JobSystemThreadPool
#include <Jolt/Physics/Body/BodyInterface.h> // For JPH::BodyInterface

#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>


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

// For physics engine
#include <core/physics/GamePhysicsBackend.hpp>

// For Layers
#include <core/physics/Layers.hpp>

// For base components
#include <game/components/CoreComponents.hpp>

// For demo compononets
#include <demo/components/DemoCharacterComponents.hpp>


namespace RlClone::Demo {


class DemoCharacterCreatorSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;

  
public:
    DemoCharacterCreatorSystem(entt::registry& entity_registry_ref);


    ~DemoCharacterCreatorSystem();


    void Create();


    void CleanUp();
};


}; // namespace RlClone::Demo

#endif
