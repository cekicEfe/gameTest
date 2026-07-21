#include "PhysicsComponentUpdater.hpp"


RlClone::PhysicsComponentUpdater::PhysicsComponentUpdater(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::PhysicsComponentUpdater::~PhysicsComponentUpdater() {}


void RlClone::PhysicsComponentUpdater::Update(const float delta_time) {
    // Get physics backend
    static auto& physics_system_backend =
        this->entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();

    // Update all physics objects
    physics_system_backend.GetPhysicsSystem().Update(
        delta_time,
        1,
        &physics_system_backend.GetTempAllocator(),
        &physics_system_backend.GetJobSystemThreadPool());
}
