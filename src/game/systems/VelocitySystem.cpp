#include "VelocitySystem.hpp"


RlClone::VelocitySystem::VelocitySystem(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::VelocitySystem::~VelocitySystem() {}


void RlClone::VelocitySystem::Update(const float delta_time) {

    // We are sure that RlClone::PhysicsBackend::GamePhysicsBackend always exists
    auto& physics_system =
        this->entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();

    // Update objects that does not have physics component
    auto non_physicals_view = this->entity_registry_ref.get()
                                  .view<RlClone::TransformComponent, RlClone::VelocityComponent>(
                                      entt::exclude<RlClone::PhysicsComponent>);
    for (auto entity : non_physicals_view) {
        auto& transform_component = non_physicals_view.get<RlClone::TransformComponent>(entity);
        auto& velocity_component = non_physicals_view.get<RlClone::VelocityComponent>(entity);

        transform_component.position = velocity_component.velocity * delta_time;
    }


    auto& body_interface = physics_system.GetPhysicsSystem().GetBodyInterface();
    auto view = this->entity_registry_ref.get()
                    .view<RlClone::VelocityComponent, RlClone::PhysicsComponent>();

    for (auto entity : view) {
        auto& physics_component = view.get<RlClone::PhysicsComponent>(entity);
        if (body_interface.IsAdded(physics_component.body_id)) {
            // If body is not active
            if (body_interface.IsActive(physics_component.body_id))
                body_interface.ActivateBody(physics_component.body_id);

            auto& velocity_component = view.get<RlClone::VelocityComponent>(entity);
            body_interface.SetLinearVelocity(
                physics_component.body_id,
                velocity_component.velocity);
        }
    }
}
