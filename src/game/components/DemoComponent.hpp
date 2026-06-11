#ifndef DEMO_COMPONENT_HPP
#define DEMO_COMPONENT_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Math/Quat.h>
#include <Jolt/Math/Vec3.h>

#include <entt/entt.hpp>

// For uint32_t   
#include <cstdint>


namespace RlClone {

  struct DemoComponentParent {
    float ring_radius;
    JPH::Quat ring_tilt;
    entt::entity ring_parent = entt::null;
    std::uint32_t child_count = 0;
  };

  struct DemoComponentChild {
    float ring_orbit_speed = 0;
    float ring_angle_in_radian; //Very mouthful
    entt::entity parent = entt::null;
    entt::entity next_child = entt::null;
  };
  
};

#endif
