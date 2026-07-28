#ifndef BASECAMERABUILDER_HPP
#define BASECAMERABUILDER_HPP

#include "render_backend/RenderBackend.hpp"
#include "components/CoreComponents.hpp"
#include "components/BaseCameraComponents.hpp"

#include <entt/entt.hpp>


namespace RlClone {

extern entt::entity BuildBaseCamera(entt::registry& entity_registry);

}

#endif /* BASECAMERABUILDER_HPP */
