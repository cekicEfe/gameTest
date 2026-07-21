#include "PowerCarBuilder.hpp"


entt::entity RlClone::PowerCarBuilder(entt::registry& entity_registry) {
    std::cout << "Creating PowerCar entity" << std::endl;
    std::cout << "PowerCarBuilder: Acquiring ctx objects" << std::endl;
    auto& asset_manager = entity_registry.ctx().get<RlClone::AssetManager>();
    auto& physics_system_backend =
        entity_registry.ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();
    auto& physics_system = physics_system_backend.GetPhysicsSystem();
    auto& body_interface = physics_system.GetBodyInterface();
    std::cout << "PowerCarBuilder: Acquired ctx objects successfully" << std::endl;

    // Initialize entity
    auto power_car_entity = entity_registry.create();

    auto& car_controller_component =
        entity_registry.emplace<RlClone::BaseCarControllerComponent>(power_car_entity);

    auto& power_car_component =
        entity_registry.emplace<RlClone::PowerCarComponent>(power_car_entity);

    auto& power_car_physics_component =
        entity_registry.emplace<RlClone::PhysicsComponent>(power_car_entity);

    auto& power_car_transform_component =
        entity_registry.emplace<RlClone::TransformComponent>(power_car_entity);

    auto& power_car_model_component =
        entity_registry.emplace<RlClone::ModelComponent>(power_car_entity);

    auto& power_car_texture_component =
        entity_registry.emplace<RlClone::TextureComponent>(power_car_entity);

    auto& power_car_shader_component =
        entity_registry.emplace<RlClone::ShaderComponent>(power_car_entity);

    auto& wheel_radius = power_car_component.wheel_radius;
    auto& wheel_width = power_car_component.wheel_width;
    auto& half_vehicle_length = power_car_component.half_vehicle_length;
    auto& half_vehicle_width = power_car_component.half_vehicle_width;
    auto& half_vehicle_height = power_car_component.half_vehicle_height;

    power_car_component.testers[0] =
        new JPH::VehicleCollisionTesterRay(RlClone::PhysicsBackend::Layers::MOVING);

    power_car_component.testers[1] = new JPH::VehicleCollisionTesterCastSphere(
        RlClone::PhysicsBackend::Layers::MOVING,
        0.5f * wheel_width);

    power_car_component.testers[2] =
        new JPH::VehicleCollisionTesterCastCylinder(RlClone::PhysicsBackend::Layers::MOVING);

    // Create vehicle body
    JPH::RVec3 position(0, 5, 0);

    power_car_transform_component.position = position;

    // JPH::RefConst<JPH::Shape> car_shape =
    //     JPH::OffsetCenterOfMassShapeSettings(
    //         JPH::Vec3(0, -half_vehicle_height, 0),
    //         new JPH::BoxShape(
    //             JPH::Vec3(half_vehicle_width, half_vehicle_height, half_vehicle_length)))
    //         .Create()
    //         .Get();

    JPH::RefConst<JPH::Shape> car_shape =
        new JPH::BoxShape(JPH::Vec3(half_vehicle_width, half_vehicle_height, half_vehicle_length));

    JPH::BodyCreationSettings car_body_settings(
        car_shape,
        position,
        JPH::Quat::sRotation(JPH::Vec3::sAxisZ(), power_car_component.initial_roll_angle),
        JPH::EMotionType::Dynamic,
        RlClone::PhysicsBackend::Layers::MOVING);

    car_body_settings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
    car_body_settings.mMassPropertiesOverride.mMass = 1500.0f;
    auto* mCarBody = body_interface.CreateBody(car_body_settings);
    body_interface.AddBody(mCarBody->GetID(), JPH::EActivation::Activate);

    // Create vehicle constraint
    JPH::VehicleConstraintSettings vehicle;
    vehicle.mDrawConstraintSize = 0.1f;
    vehicle.mMaxPitchRollAngle = power_car_component.max_roll_angle;

    // Suspension direction
    JPH::Vec3 front_suspension_dir =
        JPH::Vec3(
            JPH::Tan(power_car_component.front_suspension_sideways_angle),
            -1,
            JPH::Tan(power_car_component.front_suspension_forward_angle))
            .Normalized();
    JPH::Vec3 front_steering_axis = JPH::Vec3(
                                        -JPH::Tan(power_car_component.front_king_pin_angle),
                                        1,
                                        -JPH::Tan(power_car_component.front_caster_angle))
                                        .Normalized();
    JPH::Vec3 front_wheel_up = JPH::Vec3(
        JPH::Sin(power_car_component.front_camber),
        JPH::Cos(power_car_component.front_camber),
        0);
    JPH::Vec3 front_wheel_forward = JPH::Vec3(
        -JPH::Sin(power_car_component.front_toe),
        0,
        JPH::Cos(power_car_component.front_toe));
    JPH::Vec3 rear_suspension_dir =
        JPH::Vec3(
            JPH::Tan(power_car_component.rear_suspension_sideways_angle),
            -1,
            JPH::Tan(power_car_component.rear_suspension_forward_angle))
            .Normalized();
    JPH::Vec3 rear_steering_axis = JPH::Vec3(
                                       -JPH::Tan(power_car_component.rear_king_pin_angle),
                                       1,
                                       -JPH::Tan(power_car_component.rear_caster_angle))
                                       .Normalized();
    JPH::Vec3 rear_wheel_up = JPH::Vec3(
        JPH::Sin(power_car_component.rear_camber),
        JPH::Cos(power_car_component.rear_camber),
        0);
    JPH::Vec3 rear_wheel_forward = JPH::Vec3(
        -JPH::Sin(power_car_component.rear_toe),
        0,
        JPH::Cos(power_car_component.rear_toe));

    JPH::Vec3 flip_x(-1, 1, 1);

    // Wheels, left front
    JPH::WheelSettingsWV* w1 = new JPH::WheelSettingsWV;
    w1->mPosition = JPH::Vec3(
        half_vehicle_width,
        -0.9f * half_vehicle_height,
        half_vehicle_length - 2.0f * wheel_radius);
    w1->mSuspensionDirection = front_suspension_dir;
    w1->mSteeringAxis = front_steering_axis;
    w1->mWheelUp = front_wheel_up;
    w1->mWheelForward = front_wheel_forward;
    w1->mSuspensionMinLength = power_car_component.front_suspension_min_length;
    w1->mSuspensionMaxLength = power_car_component.front_suspension_max_length;
    w1->mSuspensionSpring.mFrequency = power_car_component.front_suspension_frequency;
    w1->mSuspensionSpring.mDamping = power_car_component.front_suspension_damping;
    w1->mMaxSteerAngle = power_car_component.max_steering_angle;
    w1->mMaxHandBrakeTorque = 0.0f; // Front wheel doesn't have hand brake

    // Right front
    JPH::WheelSettingsWV* w2 = new JPH::WheelSettingsWV;
    w2->mPosition = JPH::Vec3(
        -half_vehicle_width,
        -0.9f * half_vehicle_height,
        half_vehicle_length - 2.0f * wheel_radius);
    w2->mSuspensionDirection = flip_x * front_suspension_dir;
    w2->mSteeringAxis = flip_x * front_steering_axis;
    w2->mWheelUp = flip_x * front_wheel_up;
    w2->mWheelForward = flip_x * front_wheel_forward;
    w2->mSuspensionMinLength = power_car_component.front_suspension_min_length;
    w2->mSuspensionMaxLength = power_car_component.front_suspension_max_length;
    w2->mSuspensionSpring.mFrequency = power_car_component.front_suspension_frequency;
    w2->mSuspensionSpring.mDamping = power_car_component.front_suspension_damping;
    w2->mMaxSteerAngle = power_car_component.max_steering_angle;
    w2->mMaxHandBrakeTorque = 0.0f; // Front wheel doesn't have hand brake

    // Left rear
    JPH::WheelSettingsWV* w3 = new JPH::WheelSettingsWV;
    w3->mPosition = JPH::Vec3(
        half_vehicle_width,
        -0.9f * half_vehicle_height,
        -half_vehicle_length + 2.0f * wheel_radius);
    w3->mSuspensionDirection = rear_suspension_dir;
    w3->mSteeringAxis = rear_steering_axis;
    w3->mWheelUp = rear_wheel_up;
    w3->mWheelForward = rear_wheel_forward;
    w3->mSuspensionMinLength = power_car_component.rear_suspension_min_length;
    w3->mSuspensionMaxLength = power_car_component.rear_suspension_max_length;
    w3->mSuspensionSpring.mFrequency = power_car_component.rear_suspension_frequency;
    w3->mSuspensionSpring.mDamping = power_car_component.rear_suspension_damping;
    w3->mMaxSteerAngle = 0.0f;

    // Right rear
    JPH::WheelSettingsWV* w4 = new JPH::WheelSettingsWV;
    w4->mPosition = JPH::Vec3(
        -half_vehicle_width,
        -0.9f * half_vehicle_height,
        -half_vehicle_length + 2.0f * wheel_radius);
    w4->mSuspensionDirection = flip_x * rear_suspension_dir;
    w4->mSteeringAxis = flip_x * rear_steering_axis;
    w4->mWheelUp = flip_x * rear_wheel_up;
    w4->mWheelForward = flip_x * rear_wheel_forward;
    w4->mSuspensionMinLength = power_car_component.rear_suspension_min_length;
    w4->mSuspensionMaxLength = power_car_component.rear_suspension_max_length;
    w4->mSuspensionSpring.mFrequency = power_car_component.rear_suspension_frequency;
    w4->mSuspensionSpring.mDamping = power_car_component.rear_suspension_damping;
    w4->mMaxSteerAngle = 0.0f;

    vehicle.mWheels = {w1, w2, w3, w4};

    for (JPH::WheelSettings* w : vehicle.mWheels) {
        w->mRadius = wheel_radius;
        w->mWidth = wheel_width;
    }

    JPH::WheeledVehicleControllerSettings* controller = new JPH::WheeledVehicleControllerSettings;
    vehicle.mController = controller;

    // Differential
    controller->mDifferentials.resize(power_car_component.four_wheel_drive ? 2 : 1);
    controller->mDifferentials[0].mLeftWheel = 0;
    controller->mDifferentials[0].mRightWheel = 1;
    if (power_car_component.four_wheel_drive) {
        controller->mDifferentials[1].mLeftWheel = 2;
        controller->mDifferentials[1].mRightWheel = 3;

        // Split engine torque
        controller->mDifferentials[0].mEngineTorqueRatio =
            controller->mDifferentials[1].mEngineTorqueRatio = 0.5f;
    }

    // Anti rollbars
    if (power_car_component.anti_rollbar) {
        vehicle.mAntiRollBars.resize(2);
        vehicle.mAntiRollBars[0].mLeftWheel = 0;
        vehicle.mAntiRollBars[0].mRightWheel = 1;
        vehicle.mAntiRollBars[1].mLeftWheel = 2;
        vehicle.mAntiRollBars[1].mRightWheel = 3;
    }

    power_car_component.vehicle_constraint = new JPH::VehicleConstraint(*mCarBody, vehicle);

    // The vehicle settings were tweaked with a buggy implementation of the longitudinal tire
    // impulses, this meant that PhysicsSettings::mNumVelocitySteps times more impulse could be
    // applied than intended. To keep the behavior of the vehicle the same we increase the max
    // longitudinal impulse by the same factor. In a future version the vehicle will be retweaked.
    static_cast<JPH::WheeledVehicleController*>(
        power_car_component.vehicle_constraint->GetController())
        ->SetTireMaxImpulseCallback(
            [](uint,
               float& outLongitudinalImpulse,
               float& outLateralImpulse,
               float inSuspensionImpulse,
               float inLongitudinalFriction,
               float inLateralFriction,
               float,
               float,
               float)
            {
                outLongitudinalImpulse = 10.0f * inLongitudinalFriction * inSuspensionImpulse;
                outLateralImpulse = inLateralFriction * inSuspensionImpulse;
            });

    physics_system.AddConstraint(power_car_component.vehicle_constraint);
    physics_system.AddStepListener(power_car_component.vehicle_constraint);


    JPH::WheeledVehicleController* car_controller = static_cast<JPH::WheeledVehicleController*>(
        power_car_component.vehicle_constraint->GetController());

    // Update vehicle statistics
    car_controller->GetEngine().mMaxTorque = power_car_component.max_engine_torque;
    car_controller->GetTransmission().mClutchStrength = power_car_component.clutch_strength;

    // Set slip ratios to the same for everything
    float limited_slip_ratio = power_car_component.limited_slip_differentials ? 1.4f : FLT_MAX;
    car_controller->SetDifferentialLimitedSlipRatio(limited_slip_ratio);
    for (JPH::VehicleDifferentialSettings& d : car_controller->GetDifferentials())
        d.mLimitedSlipRatio = limited_slip_ratio;

    // Pass the input on to the constraint
    car_controller->SetDriverInput(
        car_controller_component.forward,
        car_controller_component.right,
        car_controller_component.brake,
        car_controller_component.hand_brake);

    // Set the collision tester
    power_car_component.vehicle_constraint->SetVehicleCollisionTester(
        power_car_component.testers[power_car_component.collision_mode]);

    power_car_physics_component.body_id = mCarBody->GetID();

    power_car_model_component.model_id = *asset_manager.PutModel(RlClone::POWER_CAR_MODEL);

    power_car_texture_component.texture_id =
        *asset_manager.PutTexture(RlClone::POWER_CAR_MODEL_TEXTURE);

    power_car_shader_component.shader_id =
        *asset_manager.PutShader(); // Default shader will be used

    std::cout << "Created PowerCar entity successfully" << std::endl;
    return power_car_entity;
}
