#include "CoreSystems.hpp"


RlClone::RenderSystem::RenderSystem(
    JPH::PhysicsSystem& physics_system_ref,
    entt::registry& entity_registry_ref,
    RlClone::AssetManager& asset_manager_ref) {}


RlClone::RenderSystem::~RenderSystem() {}


void RlClone::RenderSystem::Update(const float delta_time) {
    this->entity_registry_ref.sort<RlClone::ModelComponent>(
        [](const RlClone::ModelComponent& val_l, const RlClone::ModelComponent& val_r)
        { val_l.model_id < val_r.model_id; });

    this->entity_registry_ref.sort<RlClone::ShaderComponent>(
        [](const RlClone::ShaderComponent& val_l, const RlClone::ShaderComponent& val_r)
        { val_l.shader_id < val_r.shader_id; });

    auto view = this->entity_registry_ref.view<
        RlClone::TransformComponent,
        RlClone::ModelComponent,
        RlClone::ShaderComponent,
        RlClone::Renderable>();

    // Render simple objects first cuz whynot this is a demo after all
    for (auto&& [entity, transform, model_comp, shader_comp, dont_care] : view.each()) {
        auto maybe_model_ref = this->asset_manager_ref.GetModel(model_comp.model_id);
        auto maybe_shader_ref = this->asset_manager_ref.GetShader(shader_comp.shader_id);

        if (maybe_model_ref.has_value() && maybe_shader_ref.has_value()) {
            *maybe_model_ref.materials[0].shader = *maybe_shader_ref;
            raylib::DrawModel(
                *maybe_model_ref,
                (raylib::Vector3){transform.position.GetX(),
                                  transform.position.GetY(),
                                  transform.position.GetZ()},
                transform.scale,
                BLACK);
        }
    }
}
