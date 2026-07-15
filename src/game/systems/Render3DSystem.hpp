#ifndef RENDER3D_SYSTEM_HPP
#define RENDER3D_SYSTEM_HPP

// For Entity Component System
#include <entt/entt.hpp>

// For reference_wrapper
#include <functional>

// For nullopt
#include <optional>

// For rendering
#include <raylib.h>

// For asset manager
#include "AssetManager.hpp"

// For core components which is a natural prequisite of the ecs
#include "components/CoreComponents.hpp"


namespace RlClone {


class Render3DSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    Render3DSystem(entt::registry& entity_registry_ref);
    ~Render3DSystem();


    /*!
     * \brief Renders objects that meets certain requirements
     * * \details
     * Renders objects that have the components:
     *
     * Must have
     * RlClone::TransformComponent,
     * RlClone::ModelComponent,
     * RlClone::ShaderComponent,
     * RlClone::TextureComponent
     *
     * Optional
     * RlClone::ModelAnimationComponent
     *
     * Must be called inside
     * bracket BeginMode3D, EndMode3D bracket
     *
     * During the call the system sorts components based on their shader ids
     * to optimize the render call.
     */
    void Render();
};


} // namespace RlClone


#endif
