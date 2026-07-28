#ifndef BASECAMERACOMPONENTS_HPP
#define BASECAMERACOMPONENTS_HPP

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


struct ActiveCameraTag {};


struct CameraComponent {
    Ogre::Camera* camera = nullptr;
    float fov_y_degrees = 60.0f;
    float near_clip = 0.1f;
    float far_clip = 1000.0f;
};


struct FollowCameraComponent {
    entt::entity target = entt::null;
    JPH::Vec3 local_offset{0.0f, 3.0f, -8.0f}; // behind & above, car-space
    float position_stiffness = 8.0f; // higher = snappier follow
    float rotation_stiffness = 6.0f;
};


} // namespace RlClone

#endif /* BASECAMERACOMPONENTS_HPP */
