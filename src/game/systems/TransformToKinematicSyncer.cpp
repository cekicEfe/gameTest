#include "TransformToKinematicSyncer.hpp"


RlClone::TransformToKinematicSyncer::TransformToKinematicSyncer(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::TransformToKinematicSyncer::~TransformToKinematicSyncer() {}


void RlClone::TransformToKinematicSyncer::Update(const float delta_time) {
    // Get physics system
    auto& physics_backend =
        this->entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();
    auto& body_interface = physics_backend.GetPhysicsSystem().GetBodyInterface();

    // We only get the entites with transform and physics body
    // And we also make sure that the body is kinematic
    auto view =
        this->entity_registry_ref.get()
            .view<RlClone::TransformComponent, RlClone::PhysicsComponent, RlClone::KinematicTag>();

    for (auto entity : view) {
        auto& transform = view.get<RlClone::TransformComponent>(entity);
        auto& physics = view.get<RlClone::PhysicsComponent>(entity);

        if (body_interface.IsAdded(physics.body_id)) {
            body_interface
                .MoveKinematic(physics.body_id, transform.position, transform.rotation, delta_time);
        }
    }
}
