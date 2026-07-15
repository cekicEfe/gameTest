#include "Render3DSystem.hpp"

RlClone::Render3DSystem::Render3DSystem(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::Render3DSystem::~Render3DSystem() {}


void RlClone::Render3DSystem::Render() {
    // We get the asset_manager
    auto& asset_manager = this->entity_registry_ref.get().ctx().get<RlClone::AssetManager>();

    // We sort shaders since they are the most costly part of the rendering
    this->entity_registry_ref.get().sort<RlClone::ShaderComponent>(
        [](const RlClone::ShaderComponent& val_l, const RlClone::ShaderComponent& val_r)
        { return val_l.shader_id < val_r.shader_id; });


    // We first get non animatable models
    auto view = this->entity_registry_ref.get()
                    .view<
                        RlClone::TransformComponent,
                        RlClone::ModelComponent,
                        RlClone::ShaderComponent,
                        RlClone::TextureComponent>(entt::exclude<RlClone::ModelAnimationComponent>);

    // We get the entities components
    for (auto entity_it = view.begin(); entity_it != view.end(); entity_it++) {
        auto [transform_comp, model_comp, shader_comp, texture_comp] = view.get<
            RlClone::TransformComponent,
            RlClone::ModelComponent,
            RlClone::ShaderComponent,
            RlClone::TextureComponent>(*entity_it);


        // We only want to change current assets when we stumble accross a new one
        static std::uint32_t current_model_id = UINT32_MAX;
        static std::uint32_t current_shader_id = UINT32_MAX;
        static std::uint32_t current_texture_id = UINT32_MAX;


        static std::optional<std::reference_wrapper<Model>> current_maybe_model_ref = std::nullopt;
        static std::optional<std::reference_wrapper<Shader>> current_maybe_shader_ref =
            std::nullopt;
        static std::optional<std::reference_wrapper<Texture2D>> current_maybe_texture_ref =
            std::nullopt;


        if (current_model_id != model_comp.model_id) {
            current_model_id = model_comp.model_id;
            current_maybe_model_ref = asset_manager.GetModel(model_comp.model_id);
        }
        if (current_shader_id != shader_comp.shader_id) {
            current_shader_id = shader_comp.shader_id;
            current_maybe_shader_ref = asset_manager.GetShader(shader_comp.shader_id);
        }
        if (current_texture_id != texture_comp.texture_id) {
            current_texture_id = texture_comp.texture_id;
            current_maybe_texture_ref = asset_manager.GetTexture(texture_comp.texture_id);
        }


        // If the model, texture, shader does not exists in the memory skip
        if (!current_maybe_model_ref.has_value() || !current_maybe_shader_ref.has_value() ||
            !current_maybe_texture_ref.has_value())
            continue;

        // Set current models current shader
        (*current_maybe_model_ref).get().materials[0].shader = *current_maybe_shader_ref;

        // Set current models texture
        (*current_maybe_model_ref).get().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
            (*current_maybe_texture_ref).get();

        JPH::Quat quat_normalized = transform_comp.rotation.Normalized();
        JPH::Vec3 rotation_axis;
        float rotation_angle_rad;
        quat_normalized.GetAxisAngle(rotation_axis, rotation_angle_rad);

        DrawModelEx(
            *current_maybe_model_ref,
            (Vector3){transform_comp.position.GetX(),
                      transform_comp.position.GetY(),
                      transform_comp.position.GetZ()},
            (Vector3){rotation_axis.GetX(), rotation_axis.GetY(), rotation_axis.GetZ()},
            rotation_angle_rad * RAD2DEG,
            (Vector3){transform_comp.scale.GetX(),
                      transform_comp.scale.GetY(),
                      transform_comp.scale.GetZ()},
            WHITE);
    }
}
