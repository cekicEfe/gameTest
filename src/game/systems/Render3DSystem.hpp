#ifndef RENDER3D_SYSTEM_HPP
#define RENDER3D_SYSTEM_HPP

// For Entity Component System
#include <entt/entt.hpp>

// For reference_wrapper
#include <functional>

// For nullopt
#include <optional>

// For rendering
#include <raylib.h>

// For asset manager
#include <game/AssetManager.hpp>

// For core components which is a natural prequisite of the ecs
#include <game/components/CoreComponents.hpp>


namespace RlClone {


class Render3DSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
    std::reference_wrapper<RlClone::AssetManager> asset_manager_ref;
public:
    Render3DSystem(entt::registry& entity_registry_ref, RlClone::AssetManager& asset_manager_ref);
    ~Render3DSystem();


    void Render();
};


} // namespace RlClone


#endif
