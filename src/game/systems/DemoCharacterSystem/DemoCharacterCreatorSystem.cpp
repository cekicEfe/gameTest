#include "DemoCharacterCreatorSystem.hpp"


RlClone::Demo::DemoCharacterCreatorSystem::DemoCharacterCreatorSystem(
    entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::Demo::DemoCharacterCreatorSystem::~DemoCharacterCreatorSystem() {}


void RlClone::Demo::DemoCharacterCreatorSystem::Create() {
    // Get backend
    auto* physics_backend_ptr =
        this->entity_registry_ref.get().ctx().find<RlClone::PhysicsBackend::GamePhysicsBackend>();

    // Get asset_manager
    auto* asset_manager_ptr = this->entity_registry_ref.get().ctx().find<RlClone::AssetManager>();

    if (physics_backend_ptr && asset_manager_ptr) {
        auto& physics_backend = *physics_backend_ptr;
        auto& body_interface = physics_backend.GetPhysicsSystem().GetBodyInterface();

        

    }
    else {
        std::cout << "[[[FATAL]]]Some thing went wrong" << std::endl;
        throw std::exception(
            "[[[FATAL]]]Could not acquire the neccessary resources for "
            "RlClone::Demo::DemoCharacterCreatorSystem::Create");
    }
}


void RlClone::Demo::DemoCharacterCreatorSystem::CleanUp() {}
