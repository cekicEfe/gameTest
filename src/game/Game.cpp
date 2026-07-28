#include "Game.hpp"


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    // Create the systems here
    : velocity_system(this->entity_registry)
    , transform_to_kinematic_syncer(this->entity_registry)
    , physics_component_updater(this->entity_registry)
    , physics_to_transform_syncer(this->entity_registry)
    , physics_component_destroyer(this->entity_registry) {
    std::cout << "LOG: Creating game object" << std::endl;

    // Inject game physics backend to the registry
    this->entity_registry.ctx().emplace<RlClone::PhysicsBackend::GamePhysicsBackend>(
        AllocatorMaxSize,
        cMaxBodies,
        cNumBodyMutexes,
        cMaxBodyPairs,
        cMaxContactConstraints);

    // Inject render backend to the registry
    this->entity_registry.ctx().emplace<RlClone::RenderBackend>();

    // Create main camera
    RlClone::SetActiveCamera(
        this->entity_registry,
        RlClone::BuildBaseCamera(this->entity_registry));

    std::cout << "LOG: Created game object successfully" << std::endl;
}


RlClone::Game::~Game() {
    std::cout << "LOG: Destroying game object" << std::endl;

    // Destroy physics components
    this->physics_component_destroyer.DestroyAll();

    // Destroy render backend
    this->entity_registry.ctx().erase<RlClone::RenderBackend>();

    // Destroy context objects
    this->entity_registry.ctx().erase<RlClone::PhysicsBackend::GamePhysicsBackend>();

    std::cout << "LOG: Destroyed game object successfully" << std::endl;
}


void RlClone::Game::Run() {
    auto& render_backend = this->entity_registry.ctx().get<RlClone::RenderBackend>();
    auto* root = render_backend.ctx.getRoot();
    auto* window = render_backend.ctx.getRenderWindow();
    auto* view_port = render_backend.main_viewport;
    auto& key_handler = render_backend.key_handler;

    while (is_running) {
        render_backend.ctx.pollEvents();

        if (window->isClosed() || render_backend.key_handler.IsKeyPressed(OgreBites::SDLK_ESCAPE)) {
            this->is_running = false;
            break;
        }

        // Update game
        this->velocity_system.Update(RlClone::Game::delta_time);
        this->transform_to_kinematic_syncer.Update(RlClone::Game::delta_time);
        this->physics_component_updater.Update(RlClone::Game::delta_time);
        this->physics_to_transform_syncer.Update(/*Does not take delta time*/);

        // Synchronize transform -> ogre3d
        
        
        // Renders one frame
        if (!root->renderOneFrame()) this->is_running = false;
    }
}
