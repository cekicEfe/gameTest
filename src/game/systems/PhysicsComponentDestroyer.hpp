#ifndef PHYSICS_COMPONENT_DESTROYER_HPP
#define PHYSICS_COMPONENT_DESTROYER_HPP

#include "components/CoreComponents.hpp"
#include "physics/GamePhysicsBackend.hpp"

#include <entt/entt.hpp>

#include <functional>

namespace RlClone {

class PhysicsComponentDestroyer final {
public:
    PhysicsComponentDestroyer(entt::registry& entity_registry_ref);
    ~PhysicsComponentDestroyer();

    void Destroy();
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
};

} // namespace RlClone


#endif /* PHYSICS_SYSTEM_DESTROYER_HPP */
