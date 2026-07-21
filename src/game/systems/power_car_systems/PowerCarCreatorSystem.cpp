#include "PowerCarCreatorSystem.hpp"


RlClone::PowerCarCreatorSystem::PowerCarCreatorSystem(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::PowerCarCreatorSystem::~PowerCarCreatorSystem() {}


void RlClone::PowerCarCreatorSystem::Create() {
    entt::entity power_car_entity = RlClone::PowerCarBuilder(this->entity_registry_ref.get());  
}
