#ifndef POWER_CAR_UPDATER_SYSTEM_HPP
#define POWER_CAR_UPDATER_SYSTEM_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/ShapeCast.h>
#include <Jolt/Physics/Vehicle/WheeledVehicleController.h>
#include <Jolt/Physics/Vehicle/VehicleCollisionTester.h>

#include "components/PowerCarComponents.hpp"
#include "components/CoreComponents.hpp"
#include "physics/GamePhysicsBackend.hpp"

#include <entt/entt.hpp>
#include <functional>

namespace RlClone {

class PowerCarUpdaterSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    PowerCarUpdaterSystem(entt::registry& entity_registry_ref);
    ~PowerCarUpdaterSystem();

    void PrePhysicsUpdate();
    void Update();
};

} // namespace RlClone

#endif /* POWERCARUPDATERSYSTEM_HPP */
