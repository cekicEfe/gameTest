#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

// For Entity Component System
#include <entt/entt.hpp>

// For reference_wrapper
#include <functional>

// For core components which is a natural prequisite of the ecs
#include <core/physics/GamePhysicsBackend.hpp>
#include <game/components/CoreComponents.hpp>

namespace RlClone {


class PhysicsSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    PhysicsSystem(entt::registry& entity_registry_ref);
    ~PhysicsSystem();


    /*!
     * \brief Updates physics objects.
     * * \details
     * Updates objects that have the component:
     *
     * Must have
     * RlClone::PhysicsComponent,
     *
     */
    void Update(const float delta_time);

  
    /*!
     * \brief Destroys ALL physics objects.
     * * \details
     * Destroys ALL objects that have the component:
     *
     * Must have
     * RlClone::PhysicsComponent,
     *
     */
    void CleanUp();
};


} // namespace RlClone

#endif
