#ifndef SCENETRANSFORMSYNCER_HPP
#define SCENETRANSFORMSYNCER_HPP

#include "render_backend/RenderBackend.hpp"
#include "components/CoreComponents.hpp"

#include <entt/entt.hpp>


namespace RlClone {

  
extern void SyncSceneNodeTransforms(entt::registry &entity_registry);

  
}


#endif /* SCENETRANSFORMSYNCER_HPP */
