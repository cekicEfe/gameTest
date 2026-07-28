#ifndef FOLLOWCAMERAUPDATER_HPP
#define FOLLOWCAMERAUPDATER_HPP

#include "render_backend/RenderBackend.hpp"
#include "components/BaseCameraComponents.hpp"
#include "components/CoreComponents.hpp"


namespace RlClone {


extern void UpdateActiveFollowCamera(entt::registry& entity_registry, float delta_time);


}

#endif /* CAMERAUPDATER_HPP */
