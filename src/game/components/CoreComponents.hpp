#ifndef CORE_COMPONENTS_HPP
#define CORE_COMPONENTS_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Math/Quat.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Physics/Body/BodyID.h> // For BodyID
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem

// For ecs
#include <entt/entt.hpp>

// For uint32_t
#include <cstdint>

namespace RlClone {


struct TransformComponent {
    JPH::RVec3 position;
    JPH::Quat rotation = JPH::Quat::sIdentity();
    JPH::Vec3 scale = JPH::Vec3(1.0f, 1.0f, 1.0f);
};


struct VelocityComponent {
    JPH::Vec3 velocity;
};


struct KinematicTag {};


struct PhysicsComponent {
    JPH::BodyID body_id;
};

  
struct BaseCarControllerComponent {
    float forward = 0.0f;
    float previous_forward =
        1.0f; ///< Keeps track of last car direction so we know when to brake and when to accelerate
    float right = 0.0f;
    float brake = 0.0f;
    float hand_brake = 0.0f;
};


}; // namespace RlClone


#endif
