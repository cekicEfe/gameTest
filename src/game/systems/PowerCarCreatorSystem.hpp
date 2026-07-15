#ifndef POWER_CAR_CREATOR_SYSTEM_HPP
#define POWER_CAR_CREATOR_SYSTEM_HPP

// For ecs
#include <entt/entt.hpp>

// For reference_wrapper
#include <functional>

// For asset manager
#include "AssetManager.hpp"

// For physics engine
#include "GamePhysicsBackend.hpp"

#include "CoreComponents.hpp"


namespace RlClone {


class PowerCarCreatorSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    PowerCarCreatorSystem(entt::registry& entity_registry_ref);

    ~PowerCarCreatorSystem();

    void Create();
};


}; // namespace RlClone


#endif
