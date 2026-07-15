#ifndef CAR_HPP
#define CAR_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/ShapeCast.h>
#include <Jolt/Physics/Vehicle/WheeledVehicleController.h>

// For Layer implementation
#include "Layers.hpp"

// For the physics backend
#include "GamePhysicsBackend.hpp"

// For core components
#include "CoreComponents.hpp"

// For Entity Component System
#include <entt/entt.hpp>


namespace RlClone {


class AbstractCarTemplate {
public:
    float wheel_radius = 0.3f;
    float wheel_width = 0.1f;
    float half_vehicle_length = 2.0f;
    float half_vehicle_width = 0.9f;
    float half_vehicle_height = 0.2f;


    JPH::RefConst<JPH::Shape> car_shape;
    JPH::BodyCreationSettings car_body_settings;
    JPH::VehicleConstraintSettings vehicle_settings;


    JPH::Vec3 front_suspension_dir;
    JPH::Vec3 front_steering_axis;
    JPH::Vec3 front_wheel_up;
    JPH::Vec3 front_wheel_forward;
    JPH::Vec3 rear_suspension_dir;
    JPH::Vec3 rear_steering_axis;
    JPH::Vec3 rear_wheel_up;
    JPH::Vec3 rear_wheel_forward;
    JPH::Vec3 flip_x = JPH::Vec3(-1, 1, 1);


    float initial_roll_angle = 0;
    float max_roll_angle = JPH::DegreesToRadians(60.0f);
    float max_steering_angle = JPH::DegreesToRadians(30.0f);
    int collision_mode = 2;
    bool four_wheel_drive = false;
    bool anti_rollbar = true;
    bool limited_slip_differentials = true;
    bool override_gravity = false;
    float max_engine_torque = 500.0f;
    float clutch_strength = 10.0f;


    float front_caster_angle = 0.0f;
    float front_king_pin_angle = 0.0f;
    float front_camber = 0.0f;
    float front_toe = 0.0f;
    float front_suspension_forward_angle = 0.0f;
    float front_suspension_sideways_angle = 0.0f;
    float front_suspension_min_length = 0.3f;
    float front_suspension_max_length = 0.5f;
    float front_suspension_frequency = 1.5f;
    float front_suspension_damping = 0.5f;
    float rear_suspension_forward_angle = 0.0f;
    float rear_suspension_sideways_angle = 0.0f;
    float rear_caster_angle = 0.0f;
    float rear_king_pin_angle = 0.0f;
    float rear_camber = 0.0f;
    float rear_toe = 0.0f;
    float rear_suspension_min_length = 0.3f;
    float rear_suspension_max_length = 0.5f;
    float rear_suspension_frequency = 1.5f;
    float rear_suspension_damping = 0.5f;


    JPH::BodyID car_body;
    JPH::Ref<JPH::VehicleConstraint> vehicle_constraint;
    JPH::Ref<JPH::VehicleCollisionTester> testers[3];
};


class AbstractCarBuilder {
public:
    AbstractCarBuilder();
    virtual ~AbstractCarBuilder() = 0;

    virtual entt::entity CreateCar(entt::registry& entity_registry) = 0;
};


class AbstractCarDirector {
public:
    AbstractCarDirector();
    virtual ~AbstractCarDirector() = 0;

    virtual entt::entity Construct(entt::registry& entity_registry) = 0;
};


} // namespace RlClone

#endif
