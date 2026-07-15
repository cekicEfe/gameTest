#include "PowerCarBuilder.hpp"


entt::entity RlClone::PowerCarBuilder(entt::registry &entity_registry){

    auto &asset_manager = entity_registry.ctx().get<RlClone::AssetManager>();
    
    
	const float wheel_radius = 0.3f;
	const float wheel_width = 0.1f;
	const float half_vehicle_length = 2.0f;
	const float half_vehicle_width = 0.9f;
	const float half_vehicle_height = 0.2f;

    RlClone::PowerCarBuilder power_car_component;
    
	// Create collision testers
	power_car_component.testers[0] = new VehicleCollisionTesterRay(RlClone::PhysicsBackend::Layers::MOVING);
	power_car_component.testers[1] = new VehicleCollisionTesterCastSphere(RlClone::PhysicsBackend::Layers::MOVING, 0.5f * wheel_width);
	power_car_component.testers[2] = new VehicleCollisionTesterCastCylinder(RlClone::PhysicsBackend::Layers::MOVING);    

	// Create vehicle body
    JPH::RVec3 position(0, 2, 0);
	JPH::RefConst<JPH::Shape> car_shape = OffsetCenterOfMassShapeSettings(JPH::Vec3(0, -half_vehicle_height, 0), new JPH::BoxShape(JPH::Vec3(half_vehicle_width, half_vehicle_height, half_vehicle_length))).Create().Get();
	JPH::BodyCreationSettings car_body_settings(car_shape, position, JPH::Quat::sRotation(JPH::Vec3::sAxisZ(), sInitialRollAngle), JPH::EMotionType::Dynamic, RlClone::PhysicsBackend::Layers::MOVING);
	car_body_settings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
	car_body_settings.mMassPropertiesOverride.mMass = 1500.0f;
    JPH::Body* mCarBody = mBodyInterface->CreateBody(car_body_settings);
    JPH::BodyID body_id = mCarBody.getID();
	mBodyInterface->AddBody(body_id, JPH::EActivation::Activate);

	// Create vehicle constraint
    JPH::VehicleConstraintSettings vehicle;
	vehicle.mDrawConstraintSize = 0.1f;
	vehicle.mMaxPitchRollAngle = max_roll_angle;
    
	// Suspension direction
    JPH::Vec3 front_suspension_dir = JPH::Vec3(JPH::Tan(front_suspension_sideways_angle), -1, JPH::Tan(front_suspension_forward_angle)).Normalized();
    JPH::Vec3 front_steering_axis = JPH::Vec3(-JPH::Tan(front_king_pin_angle), 1, -JPH::Tan(front_caster_angle)).Normalized();
    JPH::Vec3 front_wheel_up = JPH::Vec3(JPH::Sin(front_camber), JPH::Cos(front_camber), 0);
    JPH::Vec3 front_wheel_forward = JPH::Vec3(-JPH::Sin(front_toe), 0, JPH::Cos(front_toe));
    JPH::Vec3 rear_suspension_dir = JPH::Vec3(JPH::Tan(rear_suspension_sideways_angle), -1, JPH::Tan(rear_suspension_forward_angle)).Normalized();
    JPH::Vec3 rear_steering_axis = JPH::Vec3(-JPH::Tan(rear_king_pin_angle), 1, -JPH::Tan(rear_caster_angle)).Normalized();
    JPH::Vec3 rear_wheel_up = JPH::Vec3(JPH::Sin(rear_camber), JPH::Cos(rear_camber), 0);
    JPH::Vec3 rear_wheel_forward = JPH::Vec3(-JPH::Sin(rear_toe), 0, JPH::Cos(rear_toe));
    JPH::Vec3 flip_x(-1, 1, 1);
    
}
