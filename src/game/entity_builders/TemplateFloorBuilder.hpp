#ifndef TEMPLATE_FLOOR_BUILDER_HPP
#define TEMPLATE_FLOOR_BUILDER_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

#include "physics/GamePhysicsBackend.hpp"

#include "AssetManager.hpp"
#include "components/CoreComponents.hpp"

#include <entt/entt.hpp>

namespace RlClone {

  extern entt::entity TemplateFloorBuilder(entt::registry& entity_registry_ref);
  
}

#endif /* TEMPLATEFLOORBUILDER_HPP */
