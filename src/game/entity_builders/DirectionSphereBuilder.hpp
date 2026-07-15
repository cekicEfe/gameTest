#ifndef DIRECTION_SPHERE_BUILDER_HPP
#define DIRECTION_SPHERE_BUILDER_HPP

#include "components/CoreComponents.hpp"
#include "game/AssetManager.hpp"
#include "physics/GamePhysicsBackend.hpp"
#include "components/DirectionSphereComponents.hpp"

#include <Jolt/Jolt.h>
#include <Jolt/Math/Quat.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include <entt/entt.hpp>
#include <raylib.h>
#include <exception>
#include <iostream>

namespace RlClone {
extern entt::entity DirectionSphereBuilder(entt::registry &entity_registry, JPH::RVec3 position, JPH::Vec3 scale);
};

#endif
