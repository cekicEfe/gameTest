#include "PhysicsSystem.hpp"


RlClone::PhysicsSystem::PhysicsSystem(entt::registry& entity_registry_ref)
    : entity_registry_ref(std::ref(entity_registry_ref)) {}


RlClone::PhysicsSystem::~PhysicsSystem() {}


void RlClone::PhysicsSystem::Update(const float delta_time) {
    if (auto* physics_backend_ptr = this->entity_registry_ref.get()
                                        .ctx()
                                        .find<RlClone::PhysicsBackend::GamePhysicsBackend>()) {
        auto& physics_backend = *physics_backend_ptr;

        
        physics_backend.GetPhysicsSystem().Update(
            delta_time,
            1,
            &physics_backend.GetTempAllocator(),
            &physics_backend.GetJobSystemThreadPool());

        
    }
    else {
        throw std::runtime_error("[[[FATAL]]] Could not find the physics backend");
    }
}


void RlClone::PhysicsSystem::CleanUp() {
    if (auto* physics_backend_ptr = this->entity_registry_ref.get()
                                        .ctx()
                                        .find<RlClone::PhysicsBackend::GamePhysicsBackend>()) {
        auto& physics_backend = *physics_backend_ptr;
        JPH::BodyInterface& body_interface = physics_backend.GetPhysicsSystem().GetBodyInterface();

        auto view = this->entity_registry_ref.get().view<RlClone::PhysicsComponent>();
        for (auto entity : view) {
            auto& body_id = this->entity_registry_ref.get().get<RlClone::PhysicsComponent>(entity);
            if (body_interface.IsAdded(body_id.body_id)) {
                body_interface.RemoveBody(body_id.body_id);
                body_interface.DestroyBody(body_id.body_id);
            }
            this->entity_registry_ref.get().remove<RlClone::PhysicsComponent>(entity);
        }
    }
    else {
        throw std::runtime_error("[[[FATAL]]] Could not find the physics backend");
    }
}
