#include "PhysicsSystem.hpp"


RlClone::PhysicsSystem::PhysicsSystem(
    entt::registry& entity_registry_ref,
    JPH::PhysicsSystem& physics_system_ref,
    JPH::TempAllocatorImpl& temp_allocator_ref,
    JPH::JobSystemThreadPool& job_system_ref)
    : entity_registry_ref(std::ref(entity_registry_ref))
    , physics_system_ref(std::ref(physics_system_ref))
    , temp_allocator_ref(std::ref(temp_allocator_ref))
    , job_system_ref(std::ref(job_system_ref)) {}


RlClone::PhysicsSystem::~PhysicsSystem() {}


void RlClone::PhysicsSystem::Update(const float delta_time) {
    this->physics_system_ref.get()
        .Update(delta_time, 1, &this->temp_allocator_ref.get(), &this->job_system_ref.get());
}


void RlClone::PhysicsSystem::CleanUp() {
    JPH::BodyInterface& body_interface = this->physics_system_ref.get().GetBodyInterface();
    auto view = this->entity_registry_ref.get().view<RlClone::PhysicsComponent>();
    for (auto entity : view) {
        auto& body_id = this->entity_registry_ref.get().get<RlClone::PhysicsComponent>(entity);
        if (body_interface.IsAdded(body_id.body_id)) {
            body_interface.RemoveBody(body_id.body_id);
            body_interface.DestroyBody(body_id.body_id);
        }
    }
}
