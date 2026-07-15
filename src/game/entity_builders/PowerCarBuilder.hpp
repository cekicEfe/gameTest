#ifndef POWERCAR_BUILDER_HPP
#define POWERCAR_BUILDER_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/ShapeCast.h>
#include <Jolt/Physics/Vehicle/WheeledVehicleController.h>
#include <Jolt/Physics/Vehicle/VehicleCollisionTester.h>

#include "physics/Layers.hpp"
#include "physics/GamePhysicsBackend.hpp"

#include "components/CoreComponents.hpp"
#include "components/PowerCarComponents.hpp"

#include <entt/entt.hpp>


namespace RlClone {

  
extern entt::entity PowerCarBuilder(entt::registry &entity_registry);

  
} // namespace RlClone


#endif
