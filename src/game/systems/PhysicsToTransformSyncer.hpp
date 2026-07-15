#ifndef PHYSICS_TO_TRANSFORM_SYNCER_HPP
#define PHYSICS_TO_TRANSFORM_SYNCER_HPP

#include <entt/entt.hpp>

#include <functional>

#include "physics/GamePhysicsBackend.hpp"
#include "components/CoreComponents.hpp"


namespace RlClone {

  
class PhysicsToTransformSyncer {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    PhysicsToTransformSyncer(entt::registry& entity_registry_ref);

    ~PhysicsToTransformSyncer();

    /*! \brief Updates transform components based on RlClone::PhysicsComponent, excluding entities
     * marked with RlClone::KinematicTag.
     */
    void Update();
};

  
} // namespace RlClone


#endif
