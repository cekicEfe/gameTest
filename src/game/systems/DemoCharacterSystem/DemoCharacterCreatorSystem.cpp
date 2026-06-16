#include "DemoCharacterCreatorSystem.hpp"


RlClone::Demo::DemoCharacterCreatorSystem::DemoCharacterCreatorSystem(
    entt::registry& entity_registry_ref,
    JPH::PhysicsSystem& physics_system_ref,
    RlClone::AssetManager& asset_manager_ref)
    : entity_registry_ref(entity_registry_ref)
    , physics_system_ref(physics_system_ref)
    , asset_manager_ref(asset_manager_ref) {}


RlClone::Demo::DemoCharacterCreatorSystem::~DemoCharacterCreatorSystem() {}


void RlClone::Demo::DemoCharacterCreatorSystem::SetUp() {}


void RlClone::Demo::DemoCharacterCreatorSystem::CleanUp() {}
