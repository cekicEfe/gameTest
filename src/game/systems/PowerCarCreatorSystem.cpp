#include "PowerCarCreatorSystem.hpp"


RlClone::PowerCarCreatorSystem::PowerCarCreatorSystem(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::PowerCarCreatorSystem::~PowerCarCreatorSystem() {}


void RlClone::PowerCarCreatorSystem::Create() {
    auto& physics_system =
        this->entity_registry_ref.get().ctx().get<RlClone::PhysicsBackend::GamePhysicsBackend>();
    
    auto& asset_manager = this->entity_registry_ref.get().ctx().get<RlClone::AssetManager>();

    
}
