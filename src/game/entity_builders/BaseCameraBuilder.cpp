#include "BaseCameraBuilder.hpp"


entt::entity RlClone::BuildBaseCamera(entt::registry& entity_registry) {
    auto& render_backend = entity_registry.ctx().get<RlClone::RenderBackend>();
    auto* scene_manager = render_backend.main_scene_manager;
    
    entt::entity camera_entity = entt::null;
    Ogre::Camera* cam = nullptr;
    Ogre::SceneNode* node = nullptr;
    
    try {
        camera_entity = entity_registry.create();
        
        cam = scene_manager->createCamera("cam_" + std::to_string((uint32_t)camera_entity));
        cam->setAutoAspectRatio(true);
        cam->setNearClipDistance(0.1f);
        cam->setFarClipDistance(1000.0f);

        node = scene_manager->getRootSceneNode()->createChildSceneNode();
        node->attachObject(cam);

        entity_registry.emplace<RlClone::TransformComponent>(camera_entity);
        entity_registry.emplace<RlClone::SceneComponent>(camera_entity, node);
        entity_registry.emplace<RlClone::CameraComponent>(camera_entity, cam);
        
        return camera_entity;
    } catch (std::exception& e) {
        std::cout << "Something went wrong during entity creation" << std::endl;
        std::cout << e.what() << std::endl;

        if (camera_entity != entt::null) entity_registry.destroy(camera_entity);
        if (cam != nullptr) scene_manager->destroyCamera(cam);
        if (node != nullptr) scene_manager->destroySceneNode(node);
        
        return entt::null;
    }
}
