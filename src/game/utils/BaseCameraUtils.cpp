#include "BaseCameraUtils.hpp"


bool RlClone::SetActiveCamera(entt::registry& entity_registry, entt::entity entity) {
    // Get rid of previus active camera
    auto active_camera_view =
        entity_registry.view<RlClone::CameraComponent, RlClone::ActiveCameraTag>();

    for (auto camera : active_camera_view) entity_registry.erase<RlClone::ActiveCameraTag>(camera);

    if (entity_registry.valid(entity)) {
        if (auto* camera_comp_ptr = entity_registry.try_get<RlClone::CameraComponent>(entity)) {
            // Make camera active
            entity_registry.emplace_or_replace<RlClone::ActiveCameraTag>(entity);

            // Get render_backend
            auto& render_backend = entity_registry.ctx().get<RlClone::RenderBackend>();

            // Set camera for the main viewport
            render_backend.main_viewport->setCamera(camera_comp_ptr->camera);
            return true;
        }
    }
    return false;
}


entt::entity RlClone::GetActiveCamera(entt::registry& entity_registry) {
    auto active_camera_view =
        entity_registry.view<RlClone::CameraComponent, RlClone::ActiveCameraTag>();

    // There should be only one camera
    for (auto camera : active_camera_view) return camera;
}
