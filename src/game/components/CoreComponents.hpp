#ifndef CORE_COMPONENTS_HPP
#define CORE_COMPONENTS_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Math/Quat.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include <OGRE/Bites/OgreCameraMan.h>
#include <OGRE/Bites/OgreInput.h>
#include <OGRE/Ogre.h>

#include <entt/entt.hpp>
#include <cstdint>


namespace RlClone {


struct TransformComponent {
    JPH::RVec3 position = JPH::RVec3(0.0f, 0.0f, 0.0f);
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
    float forward = 0.0f; /// Cars forward direction is +Z ({0.0f, 0.0f, 1.0f} towards us) 
    float previous_forward =
        1.0f; ///< Keeps track of last car direction so we know when to brake and when to accelerate
    float right = 0.0f;
    float brake = 0.0f;
    float hand_brake = 0.0f;
};


struct SceneComponent {
    Ogre::SceneNode* scene_node = nullptr;
};
  

// Entities with this tag will not be updated in any circumstance
// struct UnusedTag {};


// Entities with this tag will be destroyed 
// struct GarbageTag{};  
  
  
}; // namespace RlClone


#endif
