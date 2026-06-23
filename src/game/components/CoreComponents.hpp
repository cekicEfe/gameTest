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

// For rendering
#include <raylib.h>


namespace RlClone {


struct TransformComponent {
    JPH::RVec3 position;
    JPH::Quat rotation = JPH::Quat::sIdentity();
    JPH::Vec3 scale;
};


struct VelocityComponent {
    JPH::Vec3 velocity;
};


struct KinematicTag {};


struct PhysicsComponent {
    JPH::BodyID body_id;
};


struct ModelComponent {
    std::uint32_t model_id;
};


struct TextureComponent {
    std::uint32_t texture_id;
};


struct ShaderComponent {
    std::uint32_t shader_id;
};


struct ModelAnimationComponent {
    std::uint32_t animation_id;
    std::uint32_t current_animation;
    std::uint32_t current_animation_frame;
};


struct MainCameraComponent {
    Camera3D camera_part;
};


}; // namespace RlClone


#endif
