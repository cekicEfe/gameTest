#ifndef TRANSFORM_TO_KINEMATIC_SYNCER_HPP
#define TRANSFORM_TO_KINEMATIC_SYNCER_HPP

// For Entity Component System
#include <entt/entt.hpp>

// For reference_wrapper
#include <functional>

// For core components which is a natural prequisite of the ecs
#include "physics/GamePhysicsBackend.hpp"
#include "components/CoreComponents.hpp"


namespace RlClone {


class TransformToKinematicSyncer {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    TransformToKinematicSyncer(entt::registry& entity_registry_ref);


    ~TransformToKinematicSyncer();

    /*!
     * \brief Updates the physics components of entities by getting the data from transform
     * component only includes kinematic objects
     * * \details
     */
    void Update(const float delta_time);
};


} // namespace RlClone


#endif
