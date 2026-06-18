#include "PhysicsToTransformSyncer.hpp"


RlClone::PhysicsToTransformSyncer::PhysicsToTransformSyncer(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::PhysicsToTransformSyncer::~PhysicsToTransformSyncer() {}


void RlClone::PhysicsToTransformSyncer::Update() {
    // Get physics system
    if (auto* physics_backend_ptr = this->entity_registry_ref.get()
                                        .ctx()
                                        .find<RlClone::PhysicsBackend::GamePhysicsBackend>()) {
        // Rename it why not
        auto& physics_backend = *physics_backend_ptr;
        auto& body_interface = physics_backend.GetPhysicsSystem().GetBodyInterface();

        
        // We only get the entites with transform and physics body
        // And we also make sure that the body is not kinematic
        auto view = this->entity_registry_ref.get()
                        .view<RlClone::TransformComponent, RlClone::PhysicsComponent>(
                            entt::exclude<RlClone::KinematicTag>);

        for (auto entity : view) {
            auto [transform, physics] =
                view.get<RlClone::TransformComponent, RlClone::PhysicsComponent>(entity);
            if (body_interface.IsActive(physics.body_id) &&
                body_interface.IsAdded(physics.body_id)) {

                JPH::RVec3 pos = body_interface.GetPosition(physics.body_id);
                JPH::Quat rot = body_interface.GetRotation(physics.body_id);
                transform.position = pos;
                transform.rotation = rot;
            }
        }
    }
    else {
        throw std::runtime_error("[[[FATAL]]] Could not find the physics backend");
    }
}
