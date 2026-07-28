#include "VelocitySystem.hpp"


RlClone::VelocitySystem::VelocitySystem(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::VelocitySystem::~VelocitySystem() {}


void RlClone::VelocitySystem::Update(const float delta_time) {
    // We are sure that RlClone::PhysicsBackend::GamePhysicsBackend always exists
    auto& physics_system_backend =
        this->entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();

    // Lock physics system
    auto& body_interface = physics_system_backend.GetPhysicsSystem().GetBodyInterface();

    
    // Update the entities without physics component
    // Get the entities that does not have physics component
    auto non_physicals_view = this->entity_registry_ref.get()
                                  .view<RlClone::TransformComponent, RlClone::VelocityComponent>(
                                      entt::exclude<RlClone::PhysicsComponent>);

    for (auto& entity : non_physicals_view) {
        auto& transform_component = non_physicals_view.get<RlClone::TransformComponent>(entity);
        auto& velocity_component = non_physicals_view.get<RlClone::VelocityComponent>(entity);

        transform_component.position = velocity_component.velocity * delta_time;
    }

    
    // Update kinematic objects
    auto kinematic_view = this->entity_registry_ref.get()
                              .view<
                                  RlClone::TransformComponent,
                                  RlClone::VelocityComponent,
                                  RlClone::KinematicTag,
                                  RlClone::PhysicsComponent>();
    for (auto& entity : kinematic_view) {
        auto& transform_component = kinematic_view.get<RlClone::TransformComponent>(entity);
        auto& velocity_component = kinematic_view.get<RlClone::VelocityComponent>(entity);

        transform_component.position = velocity_component.velocity * delta_time;
    }

    
    // Update the entities with physics component
    // Get entities with physics component
    auto physical_view =
        this->entity_registry_ref.get().view<RlClone::VelocityComponent, RlClone::PhysicsComponent>(
            entt::exclude<RlClone::KinematicTag>);
    for (auto& entity : physical_view) {
        auto& physics_component = physical_view.get<RlClone::PhysicsComponent>(entity);
        auto& velocity_component = physical_view.get<RlClone::VelocityComponent>(entity);

        if (body_interface.IsAdded(physics_component.body_id)) {
            // If body is not active activate it
            if (body_interface.IsActive(physics_component.body_id))
                body_interface.ActivateBody(physics_component.body_id);

            body_interface.SetLinearVelocity(
                physics_component.body_id,
                velocity_component.velocity);
            // We do not synchronize transform with physics components position
        }
    }
}
