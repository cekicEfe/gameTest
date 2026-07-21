#include "PhysicsComponentDestroyer.hpp"

RlClone::PhysicsComponentDestroyer::PhysicsComponentDestroyer(entt::registry& entity_registry_ref):
    entity_registry_ref(entity_registry_ref) {
}

RlClone::PhysicsComponentDestroyer::~PhysicsComponentDestroyer() {}

void RlClone::PhysicsComponentDestroyer::Destroy() {
    static auto& physics_system_backend =
      entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();

    JPH::BodyInterface& body_interface =
        physics_system_backend.GetPhysicsSystem().GetBodyInterface();

    auto view = this->entity_registry_ref.get().view<RlClone::PhysicsComponent>();
    for (auto entity : view) {
      auto& body_id = this->entity_registry_ref.get().get<RlClone::PhysicsComponent>(entity);
        if (body_interface.IsAdded(body_id.body_id)) {
            body_interface.RemoveBody(body_id.body_id);
            body_interface.DestroyBody(body_id.body_id);
        }
        this->entity_registry_ref.get().erase<RlClone::PhysicsComponent>(entity);
    }
}
