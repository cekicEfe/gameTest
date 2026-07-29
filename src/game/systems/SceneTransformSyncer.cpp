#include "SceneTransformSyncer.hpp"


void RlClone::SyncSceneNodeTransforms(entt::registry& entity_registry) {
    auto view = entity_registry.view<RlClone::TransformComponent, RlClone::SceneComponent>();

    for (auto entity : view) {
        auto [transform_comp, scene_comp] =
            entity_registry.get<RlClone::TransformComponent, RlClone::SceneComponent>(entity);

        if (scene_comp.scene_node != nullptr) {
            scene_comp.scene_node->setPosition(
                {transform_comp.position.GetX(),
                 transform_comp.position.GetY(),
                 transform_comp.position.GetZ()});

            scene_comp.scene_node->setOrientation(
                transform_comp.rotation.GetW(),
                transform_comp.rotation.GetX(),
                transform_comp.rotation.GetY(),
                transform_comp.rotation.GetZ());

            scene_comp.scene_node->setScale(
                {transform_comp.scale.GetX(),
                 transform_comp.scale.GetY(),
                 transform_comp.scale.GetZ()});
        }
    }
}
