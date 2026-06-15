#include "CoreSystems.hpp"


RlClone::AbstractSystem::AbstractSystem() {}


RlClone::AbstractSystem::~AbstractSystem() {}


RlClone::Render3DSystem::Render3DSystem(
    entt::registry& entity_registry_ref, RlClone::AssetManager& asset_manager_ref)
    : entity_registry_ref(entity_registry_ref)
    , asset_manager_ref(asset_manager_ref) {}


RlClone::Render3DSystem::~Render3DSystem() {}


void RlClone::Render3DSystem::Update(const float delta_time) {
    this->entity_registry_ref.get().sort<RlClone::ShaderComponent>(
        [](const RlClone::ShaderComponent& val_l, const RlClone::ShaderComponent& val_r)
        { return val_l.shader_id < val_r.shader_id; });


    // We first render non animatable models
    auto view = this->entity_registry_ref.get()
                    .view<
                        RlClone::TransformComponent,
                        RlClone::ModelComponent,
                        RlClone::ShaderComponent,
                        RlClone::TextureComponent,
                        RlClone::Renderable>(entt::exclude<RlClone::ModelAnimationComponent>);


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


        static std::optional<std::reference_wrapper<Model>> current_maybe_model_ref =
            std::nullopt;
        static std::optional<std::reference_wrapper<Shader>> current_maybe_shader_ref =
            std::nullopt;
        static std::optional<std::reference_wrapper<Texture2D>> current_maybe_texture_ref =
            std::nullopt;


        if (current_model_id != model_comp.model_id) {
            current_model_id = model_comp.model_id;
            current_maybe_model_ref = this->asset_manager_ref.get().GetModel(model_comp.model_id);
        }
        if (current_shader_id != shader_comp.shader_id) {
            current_shader_id = shader_comp.shader_id;
            current_maybe_shader_ref = this->asset_manager_ref.get().GetShader(shader_comp.shader_id);
        }
        if (current_texture_id != texture_comp.texture_id) {
            current_texture_id = texture_comp.texture_id;
            current_maybe_texture_ref = this->asset_manager_ref.get().GetTexture(texture_comp.texture_id);
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

        // Draw the model
        DrawModel(
            *current_maybe_model_ref,
            (Vector3){transform_comp.position.GetX(),
                      transform_comp.position.GetY(),
                      transform_comp.position.GetZ()},
            transform_comp.scale,
            WHITE);
    }
}


RlClone::PhysicsSystem::PhysicsSystem(
    entt::registry& entity_registry_ref,
    JPH::PhysicsSystem& physics_system_ref,
    JPH::TempAllocatorImpl& temp_allocator_ref,
    JPH::JobSystemThreadPool& job_system_ref)
    : entity_registry_ref(std::ref(entity_registry_ref))
    , physics_system_ref(std::ref(physics_system_ref))
    , temp_allocator_ref(std::ref(temp_allocator_ref))
    , job_system_ref(std::ref(job_system_ref)) {}


RlClone::PhysicsSystem::~PhysicsSystem() {}


void RlClone::PhysicsSystem::Update(const float delta_time) {
    this->physics_system_ref.get()
        .Update(delta_time, 1, &this->temp_allocator_ref.get(), &this->job_system_ref.get());
}
