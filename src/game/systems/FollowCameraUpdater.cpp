#include "FollowCameraUpdater.hpp"


void RlClone::UpdateActiveFollowCamera(entt::registry& entity_registry, float delta_time) {
    static auto& render_backend = entity_registry.ctx().get<RlClone::RenderBackend>();

    auto active_follow_camera_view /*Expected entity count is just one(1)*/ = entity_registry.view<
        RlClone::TransformComponent,
        RlClone::FollowCameraComponent,
        RlClone::ActiveCameraTag>();

    for (auto camera : active_follow_camera_view) {
        auto [camera_transform_comp, camera_follow_comp] = active_follow_camera_view.get<
            RlClone::TransformComponent,
            RlClone::FollowCameraComponent,
            RlClone::ActiveCameraTag>(camera);

        auto followed_entity = camera_follow_comp.target;

        if (entity_registry.valid(followed_entity)) {
            if (auto* target_pos_comp =
                    entity_registry.try_get<RlClone::TransformComponent>(followed_entity)) {
              
                JPH::Vec3 desired_pos = target_pos_comp->position +
                                        target_pos_comp->rotation * camera_follow_comp.local_offset;

                // Simple exponential smoothing (frame-rate independent)
                float pos_t = 1.0f - std::exp(camera_follow_comp.position_stiffness * delta_time);
                camera_transform_comp.position =
                    camera_transform_comp.position +
                    (desired_pos - camera_transform_comp.position) * pos_t;
            }
        }
        break;
    }
}
