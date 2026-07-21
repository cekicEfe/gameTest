#ifndef VELOCITY_SYSTEM_HPP
#define VELOCITY_SYSTEM_HPP

#include "physics/GamePhysicsBackend.hpp"
#include "components/CoreComponents.hpp"

#include <entt/entt.hpp>
#include <functional>

namespace RlClone {

  
class VelocitySystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    VelocitySystem(entt::registry& entity_registry_ref);

    ~VelocitySystem();

    void Update(const float delta_time);
};

  
}; // namespace RlClone


#endif
