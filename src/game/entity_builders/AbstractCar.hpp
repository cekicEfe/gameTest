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
#include <core/physics/Layers.hpp>

// For the physics backend
#include <core/physics/GamePhysicsBackend.hpp>

// For core traits
#include <game/components/CoreComponents.hpp>

// For Entity Component System
#include <entt/entt.hpp>


namespace RlClone {

struct CarTag {};    
  
struct AbstractCarTemplate {
    float wheel_radius = 0.3f;
    float wheel_width = 0.1f;
    float half_vehicle_length = 2.0f;
    float half_vehicle_width = 0.9f;
    float half_vehicle_height = 0.2f;


    JPH::RVec3 position;
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


    JPH::Body* car_body; ///< The vehicle
    JPH::Ref<JPH::VehicleConstraint> vehicle_constraint; ///< The vehicle constraint
    JPH::Ref<JPH::VehicleCollisionTester> testers[3]; ///< Collision testers for the wheel
};


class AbstractCarBuilder {
protected:
    entt::entity current_car_id = entt::null;

public:
    AbstractCarBuilder();
    virtual ~AbstractCarBuilder() = 0;
  
    virtual void InitilizeCar() = 0;

    virtual void SetWheelRadius() = 0;
    virtual void SetWheelWidth() = 0;
    virtual void SetWheelModel() = 0;
  
    virtual void SetCarHitbox() = 0;
    virtual void SetCarPosition() = 0;
    virtual void SetCarModel() = 0;
  
    virtual void SetRenderer() = 0;
    virtual void SetUpdater() = 0;
    virtual void SetDeconstructor() = 0;

    virtual entt::entity CreateCar() = 0;
};


// Optional to use 
class AbstractCarDirector {
public:
    AbstractCarDirector();
    virtual ~AbstractCarDirector() = 0;

    virtual entt::entity Construct() = 0;
};


} // namespace RlClone

#endif
