#ifndef POWER_CAR_COMPONENTS_HPP
#define POWER_CAR_COMPONENTS_HPP


namespace RlClone {

  
inline const std::string POWER_CAR_MODEL ("media/models/power_car/uploads_files_2792345_Koenigsegg.obj");
inline const std::string POWER_CAR_MODEL_TEXTURE ("media/models/power_car/PowerCarTexture.png");
  
  
struct PowerCarComponent {

    float wheel_radius = 0.1f;
    float wheel_width = 0.05f;
    float half_vehicle_length = 0.9f;
    float half_vehicle_width = 0.4f;
    float half_vehicle_height = 0.3f;
  
    float initial_roll_angle = 0;
    float max_roll_angle = JPH::DegreesToRadians(60.0f);
    float max_steering_angle = JPH::DegreesToRadians(30.0f);
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
};


} // namespace RlClone


#endif
