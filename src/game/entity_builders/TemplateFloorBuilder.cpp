#include <TemplateFloorBuilder.hpp>


entt::entity RlClone::TemplateFloorBuilder(entt::registry& entity_registry_ref) {
    auto& asset_manager = entity_registry_ref.ctx().get<RlClone::AssetManager>();
    auto& physics_system_backend =
        entity_registry_ref.ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();
    auto& body_interface = physics_system_backend.GetPhysicsSystem().GetBodyInterface();

    // Create a static box shape for the floor
    JPH::RefConst<JPH::Shape> floorShape = new JPH::BoxShape(JPH::Vec3(100.0f, 1.0f, 100.0f));

    // Set up the body creation settings
    JPH::BodyCreationSettings floorSettings(
        floorShape,
        JPH::RVec3(0.0f, -1.0f, 0.0f),
        JPH::Quat::sIdentity(),
        JPH::EMotionType::Static,
        RlClone::PhysicsBackend::Layers::NON_MOVING);

    // Create the body via the body interface
    JPH::Body* floor = body_interface.CreateBody(floorSettings);

    // Add it to the physics system
    body_interface.AddBody(floor->GetID(), JPH::EActivation::DontActivate);

    auto floor_entity = entity_registry_ref.create();

    entity_registry_ref.emplace<RlClone::TransformComponent>(
        floor_entity,
        JPH::RVec3(0.0f, -1.0f, 0.0f),
        JPH::Quat::sIdentity(),
        JPH::Vec3(100.0f, 1.0f, 100.0f));

    entity_registry_ref.emplace<RlClone::PhysicsComponent>(floor_entity, floor->GetID());

    entity_registry_ref.emplace<RlClone::ModelComponent>(
        floor_entity,
        *asset_manager.PutModel(RlClone::AssetManager::DEFAULT_CUBE_MODEL));

    entity_registry_ref.emplace<RlClone::TextureComponent>(
        floor_entity,
        *asset_manager.PutTexture(RlClone::AssetManager::DEFAULT_CUBE_TEXTURE));

    entity_registry_ref.emplace<RlClone::ShaderComponent>(
        floor_entity,
        *asset_manager.PutShader()); // Use default shader

    return floor_entity;
}
