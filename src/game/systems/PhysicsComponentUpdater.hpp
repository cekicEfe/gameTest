#ifndef PHYSICS_COMPONENT_UPDATER_HPP
#define PHYSICS_COMPONENT_UPDATER_HPP

#include "physics/GamePhysicsBackend.hpp"
#include "components/CoreComponents.hpp"

#include <entt/entt.hpp>
#include <functional>

namespace RlClone {

class PhysicsComponentUpdater {
public:
    PhysicsComponentUpdater(entt::registry& entity_registry_ref);
    ~PhysicsComponentUpdater();

    void Update(const float delta_time);
private:
  
    std::reference_wrapper<entt::registry> entity_registry_ref;
};


} // namespace RlClone

#endif /* PHYSICSCOMPONENTUPDATER_HPP */
