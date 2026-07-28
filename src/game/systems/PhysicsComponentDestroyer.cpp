#include "PhysicsComponentDestroyer.hpp"


RlClone::PhysicsComponentDestroyer::PhysicsComponentDestroyer(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::PhysicsComponentDestroyer::~PhysicsComponentDestroyer() {}


void RlClone::PhysicsComponentDestroyer::DestroyAll() {
    auto& physics_system_backend =
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


void RlClone::PhysicsComponentDestroyer::Destroy(entt::entity entity) {
    if (this->entity_registry_ref.get().valid(entity)) {
        if (auto* physics_body =
                this->entity_registry_ref.get().try_get<RlClone::PhysicsComponent>(entity)) {
          
            auto& physics_system_backend =
                entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();

            JPH::BodyInterface& body_interface =
                physics_system_backend.GetPhysicsSystem().GetBodyInterface();

            if (body_interface.IsAdded(physics_body->body_id)) {
                body_interface.RemoveBody(physics_body->body_id);
                body_interface.DestroyBody(physics_body->body_id);
            }

            this->entity_registry_ref.get().erase<RlClone::PhysicsComponent>(entity);
        }
    }
}


void RlClone::PhysicsComponentDestroyer::DestroyBatch(std::vector<entt::entity> entities) {
    auto& physics_system_backend =
        entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();

    JPH::BodyInterface& body_interface =
        physics_system_backend.GetPhysicsSystem().GetBodyInterface();

    for (auto entity : entities) {
        if (this->entity_registry_ref.get().valid(entity)) {
            if (auto* physics_body =
                    this->entity_registry_ref.get().try_get<RlClone::PhysicsComponent>(entity)) {
                if (body_interface.IsAdded(physics_body->body_id)) {
                    body_interface.RemoveBody(physics_body->body_id);
                    body_interface.DestroyBody(physics_body->body_id);
                }

                this->entity_registry_ref.get().erase<RlClone::PhysicsComponent>(entity);
            }
        }
    }
}
