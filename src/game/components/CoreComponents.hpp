#ifndef CORE_COMPONENTS_HPP
#define CORE_COMPONENTS_HPP


#include <Jolt/Jolt.h>
#include <Jolt/Math/Quat.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Physics/Body/BodyID.h> // For BodyID
#include <Jolt/Physics/PhysicsSettings.h>
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
    JPH::Quat rotation;
    float scale;
};


struct PhysicsComponent {
    JPH::BodyID body_id;
};


struct VelocityComponent {
    JPH::Vec3 velocity_vector;
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


// These components works as a toggle
struct Renderable {};
struct Updatable {};


}; // namespace RlClone


#endif
