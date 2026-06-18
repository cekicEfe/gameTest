#include <game/Game.hpp>


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    : render_3d_system(this->entity_registry)
    , physics_system(this->entity_registry)
    , transform_to_kinematic_syncer(this->entity_registry)
    , physics_to_transform_syncer(this->entity_registry)
    , demo_creator_system(this->entity_registry)
    , demo_controller_system(this->entity_registry) {
    std::cout << "LOG: Creating game object" << std::endl;
    std::cout << "LOG: Initializing raylib" << std::endl;

    // Initialize the raylib
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
    InitWindow(1920, 1080, "RevEngine");
    SetTargetFPS(60); // Set the game to run at 60 frames-per-second
    HideCursor();
    DisableCursor();

    // Inject game physics to the registry
    this->entity_registry.ctx().emplace<RlClone::PhysicsBackend::GamePhysicsBackend>(
        AllocatorMaxSize,
        cMaxBodies,
        cNumBodyMutexes,
        cMaxBodyPairs,
        cMaxContactConstraints);

    // Inject asset manager to the registry
    this->entity_registry.ctx().emplace<RlClone::AssetManager>();

    Camera3D camera_part = {0};
    camera_part.position = (Vector3){0.0f, 5.0f, 10.0f}; // Camera start position
    camera_part.target = (Vector3){0.0f, 0.0f, 0.0f}; // Camera looking at point
    camera_part.up = (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector
                                                  //(rotation towards target)
    camera_part.fovy = 45.0f; // Camera field-of-view Y
    camera_part.projection = CAMERA_PERSPECTIVE; // Camera mode type

    // Create main camera
    this->entity_registry.ctx().emplace<RlClone::MainCameraComponent>(camera_part);

    // Init demo
    this->demo_creator_system.Create();

    std::cout << "LOG: Initialized raylib" << std::endl;
    std::cout << "LOG: Created game object successfully" << std::endl;
}


RlClone::Game::~Game() {
    std::cout << "LOG: Destroying game object" << std::endl;
    std::cout << "LOG: Destroying raylib" << std::endl;

    this->physics_system.CleanUp();

    if (auto* ptr = this->entity_registry.ctx().find<RlClone::PhysicsBackend::GamePhysicsBackend>())
        this->entity_registry.ctx().erase<RlClone::PhysicsBackend::GamePhysicsBackend>();

    if (auto* ptr = this->entity_registry.ctx().find<RlClone::AssetManager>())
        this->entity_registry.ctx().erase<RlClone::AssetManager>();

    if (auto* ptr = this->entity_registry.ctx().find<RlClone::MainCameraComponent>())
        this->entity_registry.ctx().erase<RlClone::MainCameraComponent>();

    this->demo_creator_system.CleanUp();

    CloseWindow(); // Close window and OpenGL context

    std::cout << "LOG: Destroyed raylib" << std::endl;
    std::cout << "LOG: Destroyed game object successfully" << std::endl;
}


void RlClone::Game::Run() {
    while (!WindowShouldClose()) {
        this->demo_controller_system.GetInput();
        this->demo_controller_system.Update();
        this->transform_to_kinematic_syncer.Update(RlClone::Game::delta_time);
        this->physics_system.Update(RlClone::Game::delta_time);
        this->physics_to_transform_syncer.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        // Rendering 3d objects. But first we need the camera
        // If we don't have the camera pass it
        if (auto* main_camera = this->entity_registry.ctx().find<RlClone::MainCameraComponent>()) {
            Camera3D& camera_part = main_camera->camera_part;
            UpdateCamera(&camera_part, CAMERA_FREE);
            {
                BeginMode3D(camera_part);
                this->render_3d_system.Render();
                EndMode3D();
            }
        }
        EndDrawing();
    }
}
