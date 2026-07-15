#include "entity_builders/DirectionSphereBuilder.hpp"


entt::entity RlClone::DirectionSphereBuilder(
    entt::registry& entity_registry, JPH::RVec3 position, JPH::Vec3 scale) {
    try {
        auto direction_sphere = entity_registry.create();
        auto& asset_manager = entity_registry.ctx().get<RlClone::AssetManager>();

        auto direction_sphere_model = asset_manager.PutModel(RlClone::DIRECTION_SPHERE_MODEL_PATH);
        auto direction_sphere_texture = asset_manager.PutTexture(RlClone::DIRECTION_SPHERE_TEXTURE_PATH);
        auto base_shader = asset_manager.PutShader(); // Use base shader

        entity_registry.emplace<RlClone::TransformComponent>(
            direction_sphere,
            position,
            JPH::Quat::sIdentity(),
            scale);

        entity_registry.emplace<RlClone::ModelComponent>(direction_sphere, *direction_sphere_model);
        entity_registry.emplace<RlClone::TextureComponent>(
            direction_sphere,
            *direction_sphere_texture);
        entity_registry.emplace<RlClone::ShaderComponent>(direction_sphere, *base_shader);
        
        return direction_sphere;
    } catch (std::exception& e) {
        std::cout << "Something went wrong:" << std::endl;
        std::cout << e.what() << std::endl;
        
        return entt::null;
    }
}
