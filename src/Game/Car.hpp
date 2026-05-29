#ifndef CAR_HPP
#define CAR_HPP

// The Jolt headers don't include Jolt.h. Always include Jolt.h before including
// any other Jolt header. You can use Jolt.h in your precompiled header to speed
// up compilation.
#include <Jolt/Jolt.h>

#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/ShapeCast.h>
#include <Jolt/Physics/Vehicle/WheeledVehicleController.h>

// For Layer implementation
#include <Game/Layers.hpp>

// For the physics backend
#include <Game/GamePhysicsBackend.hpp>

// For core traits
#include <Game/CoreTraits.hpp>

// For Entity Component System
#include <entt/entt.hpp>

// For concepts
#include <concepts>

namespace raylib {
#include <raylib.h>
};

namespace RlClone {

struct CarTag {};

class AbstractCarTemplate {
public:
    float wheel_radius = 0.3f;
    float wheel_width = 0.1f;
    float half_vehicle_length = 2.0f;
    float half_vehicle_width = 0.9f;
    float half_vehicle_height = 0.2f;


    RVec3 position(0, 2, 0);
    RefConst<Shape> car_shape;
    BodyCreationSettings car_body_settings;
    VehicleConstraintSettings vehicle_settings;


    Vec3 front_suspension_dir;
    Vec3 front_steering_axis;
    Vec3 front_wheel_up;
    Vec3 front_wheel_forward;
    Vec3 rear_suspension_dir;
    Vec3 rear_steering_axis;
    Vec3 rear_wheel_up;
    Vec3 rear_wheel_forward;
    Vec3 flip_x(-1, 1, 1);


    float initial_roll_angle = 0;
    float max_roll_angle = JPH::DegreesToRadians(60.0f);
    float max_steering_angle = JPH::DegreesToRadians(30.0f);
    int collision_mode = 2;
    bool four_wheel_drive = false;
    bool anti_rollbar = true;
    bool limited_slip_differentials = true;
    bool override_gravity =
        false; ///< If true, gravity is overridden to always oppose the ground normal
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


    JPH::Body* car_body; ///< The vehicle
    JPH::Ref<JPH::VehicleConstraint> vehicle_constraint; ///< The vehicle constraint
    JPH::Ref<JPH::VehicleCollisionTester> testers[3]; ///< Collision testers for the wheel
}


class AbstractCarBuilder {
private:
public:
    AbstractCarBuilder();
    virtual ~AbstractCarBuilder() = 0;

    virtual void SetWheelRadius() = 0;
    virtual void SetWheelWidth() = 0;
    virtual void SetCarHitbox() = 0;
    virtual void SetCarPosition() = 0;

    virtual void SetRenderer() = 0;
    virtual void SetUpdater() = 0;
    virtual void SetDeconstructor() = 0;

    virtual entt::entity CreateCar() = 0;
};


class AbstractCarDirector {
private:
public:
    AbstractCarBuilder();
    virtual ~AbstractCarBuilder() = 0;

    virtual entt::entity Construct() = 0;
};


} // namespace RlClone

#endif
