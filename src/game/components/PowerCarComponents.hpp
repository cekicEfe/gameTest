#ifndef POWER_CAR_COMPONENTS_HPP
#define POWER_CAR_COMPONENTS_HPP


namespace RlClone {


inline const std::string POWER_CAR_MODEL "resources/models/power_car/Koenigsegg.obj";


struct PowerCarComponent {
    float initial_roll_angle = 0;
    float max_roll_angle = DegreesToRadians(60.0f);
    float max_steering_angle = DegreesToRadians(30.0f);
    int collision_mode = 2;
    bool four_wheel_drive = false;
    bool anti_rollbar = true;
    bool limited_slip_differentials = true;
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

    //Body* car_body; ///< expected here but it will be in the PhysicsComponent
    JPH::Ref<JPH::VehicleConstraint> vehicle_constraint; ///< The vehicle constraint
    JPH::Ref<JPH::VehicleCollisionTester> testers[3]; ///< Collision testers for the wheel
    JPH::RMat44 camera_pivot = JPH::RMat44::sIdentity();

    float forward = 0.0f;
    float previous_forward =
        1.0f; ///< Keeps track of last car direction so we know when to brake and when to accelerate
    float right = 0.0f;
    float brake = 0.0f;
    float hand_brake = 0.0f;
};


} // namespace RlClone


#endif
