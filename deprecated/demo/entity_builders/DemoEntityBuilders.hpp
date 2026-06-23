#ifndef DEMO_ENTITY_BUILDERS_HPP
#define DEMO_ENTITY_BUILDERS_HPP

// BEGONE FORMATTER
#include <Jolt/Jolt.h>
// BEGONE FORMATTER
#include <Jolt/Physics/Body/BodyInterface.h> // For JPH::BodyInterface
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem

#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>

#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>

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


extern entt::entity CreateDemoFloor(entt::registry& entity_registry);


extern entt::entity CreateDemoBall(entt::registry& entity_registry, JPH::RVec3 position);

extern entt::entity
CreateDemoPlayerControlled(entt::registry& entity_registry, JPH::RVec3 position);

  
}; // namespace RlClone::Demo


#endif
