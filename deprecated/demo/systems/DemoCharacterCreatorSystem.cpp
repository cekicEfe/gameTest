#include "DemoCharacterCreatorSystem.hpp"


RlClone::Demo::DemoCharacterCreatorSystem::DemoCharacterCreatorSystem(
    entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::Demo::DemoCharacterCreatorSystem::~DemoCharacterCreatorSystem() {}


void RlClone::Demo::DemoCharacterCreatorSystem::Create() {
    try {
        // Get backend
        auto* physics_backend_ptr = this->entity_registry_ref.get()
                                        .ctx()
                                        .find<RlClone::PhysicsBackend::GamePhysicsBackend>();

        // Get asset_manager
        auto* asset_manager_ptr =
            this->entity_registry_ref.get().ctx().find<RlClone::AssetManager>();

        // Check if we have both
        if (physics_backend_ptr && asset_manager_ptr) {
            auto& physics_backend = *physics_backend_ptr;
            auto& asset_manager = *asset_manager_ptr;
            auto& body_interface = physics_backend.GetPhysicsSystem().GetBodyInterface();


            // First create the floor
            auto entity_floor_id = this->entity_registry_ref.get().create();

            JPH::BoxShapeSettings floor_shape_settings(JPH::Vec3(100.0f, 1.0f, 100.0f));
            JPH::ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
            JPH::ShapeRefC floor_shape = floor_shape_result.Get();
            JPH::BodyCreationSettings floor_settings(
                floor_shape,
                JPH::RVec3(0.0f, -1.0f, 0.0f),
                JPH::Quat::sIdentity(),
                JPH::EMotionType::Static,
                RlClone::PhysicsBackend::Layers::NON_MOVING);

            floor_settings.mFriction = 0.5f;
            floor_settings.mRestitution = 0.3f;

            JPH::BodyID floor_body_id =
                body_interface.CreateAndAddBody(floor_settings, JPH::EActivation::Activate);

            auto maybe_shader = asset_manager.PutShader(DEMO_VERTEX_SHADER, DEMO_FRAGMENT_SHADER);
            if (!maybe_shader) throw std::runtime_error("[[[FATAL]]] Could not load shader");

            auto maybe_floor_model = asset_manager.PutModel(DEMO_FLOOR_MODEL);
            if (!maybe_floor_model) throw std::runtime_error("[[[FATAL]]] Could not load model");

            auto maybe_floor_texture = asset_manager.PutTexture(DEMO_FLOOR_TEXTURE);
            if (!maybe_floor_texture)
                throw std::runtime_error("[[[FATAL]]] Could not load texture");

            this->entity_registry_ref.get().emplace<RlClone::TransformComponent>(
                entity_floor_id,
                JPH::RVec3(0.0f, -1.0f, 0.0f),
                JPH::Quat::sIdentity(),
                JPH::Vec3(100.0f, 1.0f, 100.0f));

            this->entity_registry_ref.get().emplace<RlClone::PhysicsComponent>(
                entity_floor_id,
                floor_body_id);

            this->entity_registry_ref.get().emplace<RlClone::ModelComponent>(
                entity_floor_id,
                *maybe_floor_model);

            this->entity_registry_ref.get().emplace<RlClone::TextureComponent>(
                entity_floor_id,
                *maybe_floor_texture);

            this->entity_registry_ref.get().emplace<RlClone::ShaderComponent>(
                entity_floor_id,
                *maybe_shader);


            // Setup character
            auto character_entity = this->entity_registry_ref.get().create();

            JPH::CapsuleShapeSettings capsule_shape_settings(1.0f, 1.0f);
            JPH::ShapeRefC shape_ref = capsule_shape_settings.Create().Get();

            JPH::BodyCreationSettings settings(
                shape_ref,
                JPH::RVec3(5.0f, 5.0f, 5.0f),
                JPH::Quat::sIdentity(),
                JPH::EMotionType::Kinematic,
                RlClone::PhysicsBackend::Layers::MOVING);

            JPH::BodyID cylinder_body_id =
                body_interface.CreateAndAddBody(settings, JPH::EActivation::Activate);

            this->entity_registry_ref.get().emplace<RlClone::KinematicTag>(character_entity);

            this->entity_registry_ref.get().emplace<RlClone::PhysicsComponent>(
                character_entity,
                cylinder_body_id);

            this->entity_registry_ref.get().emplace<RlClone::TransformComponent>(
                character_entity,
                JPH::RVec3(5.0f, 5.0f, 5.0f),
                JPH::Quat::sIdentity(),
                JPH::Vec3(1.0f, 1.0f, 1.0f));

            auto maybe_character_model = asset_manager.PutModel(DEMO_CHARACTER_MODEL);
            if (!maybe_character_model)
                throw std::runtime_error("[[[FATAL]]] Could not load model");

            auto maybe_character_texture = asset_manager.PutTexture(DEMO_CHARACTER_TEXTURE);
            if (!maybe_character_texture)
                throw std::runtime_error("[[[FATAL]]] Could not load texture");

            this->entity_registry_ref.get().emplace<RlClone::ModelComponent>(
                character_entity,
                *maybe_character_model);

            this->entity_registry_ref.get().emplace<RlClone::TextureComponent>(
                character_entity,
                *maybe_character_texture);

            this->entity_registry_ref.get().emplace<RlClone::Demo::DemoCharacterControlComponent>(
                character_entity);

            this->entity_registry_ref.get().emplace<RlClone::ShaderComponent>(
                character_entity,
                *maybe_shader);


            auto sphere_entity = this->entity_registry_ref.get().create();

            JPH::SphereShapeSettings sphere_shape_settings(1.0f);
            JPH::ShapeRefC sphere_shape_ref = sphere_shape_settings.Create().Get();

            JPH::BodyCreationSettings sphere_settings(
                sphere_shape_ref,
                JPH::RVec3(1.1f, 1.1f, 1.1f),
                JPH::Quat::sIdentity(),
                JPH::EMotionType::Dynamic,
                RlClone::PhysicsBackend::Layers::MOVING);

            JPH::BodyID sphere_body_id =
                body_interface.CreateAndAddBody(sphere_settings, JPH::EActivation::Activate);

            this->entity_registry_ref.get().emplace<RlClone::PhysicsComponent>(
                sphere_entity,
                sphere_body_id);

            this->entity_registry_ref.get().emplace<RlClone::TransformComponent>(
                sphere_entity,
                JPH::RVec3(1.1f, 1.1f, 1.1f),
                JPH::Quat::sIdentity(),
                JPH::Vec3(1.0f, 1.0f, 1.0f));

            auto maybe_sphere_model = asset_manager.PutModel(DEMO_SPHERE_MODEL);
            if (!maybe_sphere_model) throw std::runtime_error("[[[FATAL]]] Could not load model");

            auto maybe_sphere_texture = asset_manager.PutTexture(DEMO_SPHERE_TEXTURE);
            if (!maybe_sphere_texture)
                throw std::runtime_error("[[[FATAL]]] Could not load texture");

            this->entity_registry_ref.get().emplace<RlClone::ModelComponent>(
                sphere_entity,
                *maybe_sphere_model);

            this->entity_registry_ref.get().emplace<RlClone::TextureComponent>(
                sphere_entity,
                *maybe_sphere_texture);

            this->entity_registry_ref.get().emplace<RlClone::ShaderComponent>(
                sphere_entity,
                *maybe_shader);













            auto sphere2_entity = this->entity_registry_ref.get().create();

            JPH::SphereShapeSettings sphere2_shape_settings(1.0f);
            JPH::ShapeRefC sphere2_shape_ref = sphere2_shape_settings.Create().Get();

            JPH::BodyCreationSettings sphere2_settings(
                sphere2_shape_ref,
                JPH::RVec3(1.3f, 5.1f, 1.1f),
                JPH::Quat::sIdentity(),
                JPH::EMotionType::Dynamic,
                RlClone::PhysicsBackend::Layers::MOVING);

            JPH::BodyID sphere2_body_id =
                body_interface.CreateAndAddBody(sphere2_settings, JPH::EActivation::Activate);

            this->entity_registry_ref.get().emplace<RlClone::PhysicsComponent>(
                sphere2_entity,
                sphere2_body_id);

            this->entity_registry_ref.get().emplace<RlClone::TransformComponent>(
                sphere2_entity,
                JPH::RVec3(1.3f, 5.1f, 1.1f),
                JPH::Quat::sIdentity(),
                JPH::Vec3(1.0f, 1.0f, 1.0f));

            auto maybe_sphere2_model = asset_manager.PutModel(DEMO_SPHERE_MODEL);
            if (!maybe_sphere2_model) throw std::runtime_error("[[[FATAL]]] Could not load model");

            auto maybe_sphere2_texture = asset_manager.PutTexture(DEMO_SPHERE_TEXTURE);
            if (!maybe_sphere2_texture)
                throw std::runtime_error("[[[FATAL]]] Could not load texture");

            this->entity_registry_ref.get().emplace<RlClone::ModelComponent>(
                sphere2_entity,
                *maybe_sphere2_model);

            this->entity_registry_ref.get().emplace<RlClone::TextureComponent>(
                sphere2_entity,
                *maybe_sphere2_texture);

            this->entity_registry_ref.get().emplace<RlClone::ShaderComponent>(
                sphere2_entity,
                *maybe_shader);

            
        }
        else {
            throw std::runtime_error(
                "[[[FATAL]]]Could not acquire the neccessary resources for "
                "RlClone::Demo::DemoCharacterCreatorSystem::Create");
        }
    } catch (std::exception& e) {
        std::cout << "[[[VERY BAD ERROR]]]Something went wrong!!!" << std::endl;
        std::cout << e.what() << std::endl;
    }
}


void RlClone::Demo::DemoCharacterCreatorSystem::CleanUp() {}
