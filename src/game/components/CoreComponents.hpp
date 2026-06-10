#ifndef CORE_COMPONENTS_HPP
#define CORE_COMPONENTS_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Math/Quat.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Physics/Body/BodyID.h> // For BodyID
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem

// For ECS
#include <entt/entt.hpp>

// For uint32_t
#include <cstdint>

namespace raylib {
#include <raylib.h>
}


namespace RlClone {


struct RenderComponent {
    std::uint32_t main_model_id;
    std::uint32_t shader_id;    
};

struct TransformComponent {
    JPH::RVec3 position;
    JPH::Quat rotation;
};

struct PhysicsComponent {
    JPH::BodyID body_id;
};


// These components works as a toggle 
struct Renderable {};
struct Updatable {};

}; // namespace RlClone

#endif
