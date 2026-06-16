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
#include <game/AssetManager.hpp>

// For core components which is a natural prequisite of the ecs
#include <game/components/CoreComponents.hpp>


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
     * Renders objects that have the components :
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
     * BeginMode3D,EndMode3D bracket
     *
     * Throws exception if it cannot find asset manager
     * in the entity_registry.ctx()
     */
    void Render();
};


} // namespace RlClone


#endif
