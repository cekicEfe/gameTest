#ifndef POWERCAR_BUILDER_HPP
#define POWERCAR_BUILDER_HPP

#include "AbstractCar.hpp"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/ShapeCast.h>
#include <Jolt/Physics/Vehicle/WheeledVehicleController.h>

// For Layer implementation
#include <core/physics/Layers.hpp>

// For the physics backend
#include <core/physics/GamePhysicsBackend.hpp>

// For core components
#include <game/components/CoreComponents.hpp>

// For Entity Component System
#include <entt/entt.hpp>


namespace RlClone {


class PowerCarTemplate : private AbstractCarTemplate {};


class PowerCarBuilder : public AbstractCarBuilder {
public:
    PowerCarBuilder(PowerCarTemplate power_car_template);
    virtual ~PowerCarBuilder() override;

    virtual entt::entity CreateCar(entt::registry& entity_registry) override;
    friend class PowerCarDirector;
};


class PowerCarDirector : public AbstractCarDirector {
public:
    PowerCarDirector(PowerCarBuilder&& power_car_builder);
    virtual ~PowerCarDirector() override;

    virtual entt::entity Construct(entt::registry& entity_registry) override;
};


} // namespace RlClone


#endif
