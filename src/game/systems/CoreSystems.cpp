#include "CoreSystems.hpp"


RlClone::AbstractSystem::AbstractSystem(
    JPH::PhysicsSystem& physics_system_ref,
    entt::registry& entity_registry_ref,
    RlClone::AssetManager& asset_manager_ref)
    : physics_system_ref(std::ref(physics_system_ref))
    , entity_registry_ref(std::ref(entity_registry_ref))
    , asset_manager_ref(std::ref(asset_manager_ref)) {}


RlClone::RenderSystem::RenderSystem(
    JPH::PhysicsSystem& physics_system_ref,
    entt::registry& entity_registry_ref,
    RlClone::AssetManager& asset_manager_ref)
    : AbstractSystem(physics_system_ref, entity_registry_ref, asset_manager_ref) {}


RlClone::RenderSystem::~RenderSystem() {}


void RlClone::RenderSystem::Update(const float delta_time) {
    this->entity_registry_ref.get().sort<RlClone::ShaderComponent>(
        [](const RlClone::ShaderComponent& val_l, const RlClone::ShaderComponent& val_r)
        { return val_l.shader_id < val_r.shader_id; });


    auto view = this->entity_registry_ref.get()
                    .view<
                        RlClone::TransformComponent,
                        RlClone::ModelComponent,
                        RlClone::ShaderComponent,
                        RlClone::Renderable>();


    for (auto entity_it = view.begin(); entity_it != view.end(); entity_it++) {
        auto [transform_comp, model_comp, shader_comp] = view.get<
            RlClone::TransformComponent,
            RlClone::ModelComponent,
            RlClone::ShaderComponent>(*entity_it);

        auto maybe_model_ref = this->asset_manager_ref.get().GetModel(model_comp.model_id);
        auto maybe_shader_ref = this->asset_manager_ref.get().GetShader(shader_comp.shader_id);

        // If the model or shader does not exists skip
        if (!maybe_model_ref.has_value() && !maybe_shader_ref.has_value()) continue;

        // Set current models current shader
        (*maybe_model_ref).get().materials[0].shader = *maybe_shader_ref;

        // Draw the model
        raylib::DrawModel(
            *maybe_model_ref,
            (raylib::Vector3){transform_comp.position.GetX(),
                              transform_comp.position.GetY(),
                              transform_comp.position.GetZ()},
            transform_comp.scale,
            raylib::WHITE);
    }
}
