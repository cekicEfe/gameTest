#ifndef BASECAMERAUTILS_HPP
#define BASECAMERAUTILS_HPP

#include "components/BaseCameraComponents.hpp"
#include "components/CoreComponents.hpp"
#include "render_backend/RenderBackend.hpp"


namespace RlClone {


extern bool SetActiveCamera(entt::registry& entity_registry, entt::entity camera);


extern entt::entity GetActiveCamera(entt::registry& entity_registry);
  

}


#endif /* BASECAMERAUTILS_HPP */
