#ifndef CORE_TRAITS_HPP
#define CORE_TRAITS_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem

// For ECS
#include <entt/entt.hpp>

namespace RlClone {

struct RenderableTag {
    void (*render_function)(entt::entity, const entt::registry&, const JPH::PhysicsSystem&);
};

struct UpdatableTag {
    void (*update_function)(entt::entity, const entt::registry&, const JPH::PhysicsSystem&);
};

struct DeconstructableTag {
    void (*deconstructor_function)(entt::entity, const entt::registry&, const JPH::PhysicsSystem&);
}

}; // namespace RlClone

#endif
