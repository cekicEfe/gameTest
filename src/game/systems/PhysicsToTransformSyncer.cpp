#include "PhysicsToTransformSyncer.hpp"


RlClone::PhysicsToTransformSyncer::PhysicsToTransformSyncer(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::PhysicsToTransformSyncer::~PhysicsToTransformSyncer() {}


void RlClone::PhysicsToTransformSyncer::Update() {
    // Get physics system backend
    auto& physics_system_backend =
        this->entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();

    // Get body interface
    auto& body_interface = physics_system_backend.GetPhysicsSystem().GetBodyInterface();

    // We only get the entites with transform and physics body
    // And we also make sure that the body is not kinematic
    auto view = this->entity_registry_ref.get()
                    .view<RlClone::TransformComponent, RlClone::PhysicsComponent>(
                        entt::exclude<RlClone::KinematicTag>);

    // Update positions
    for (auto entity : view) {
        auto [transform, physics] =
            view.get<RlClone::TransformComponent, RlClone::PhysicsComponent>(entity);

        if (body_interface.IsAdded(physics.body_id)) {
            JPH::RVec3 pos = body_interface.GetPosition(physics.body_id);
            JPH::Quat rot = body_interface.GetRotation(physics.body_id);
            transform.position = pos;
            transform.rotation = rot;
        }
    }
}
