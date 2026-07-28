#ifndef PHYSICS_COMPONENT_DESTROYER_HPP
#define PHYSICS_COMPONENT_DESTROYER_HPP

#include "components/CoreComponents.hpp"
#include "physics/GamePhysicsBackend.hpp"

#include <entt/entt.hpp>
#include <functional>
#include <vector>

namespace RlClone {

class PhysicsComponentDestroyer final {
public:
    PhysicsComponentDestroyer(entt::registry& entity_registry_ref);
    ~PhysicsComponentDestroyer();

    void DestroyAll();

    /*!
     * \brief Dont use this for big batches its slow
     */
    void Destroy(entt::entity entity);

    void DestroyBatch(std::vector<entt::entity> entities);
  
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
};

} // namespace RlClone


#endif /* PHYSICS_SYSTEM_DESTROYER_HPP */
