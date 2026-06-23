#include <game/Game.hpp>


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    // Create the systems here
    : render_3d_system(this->entity_registry)
    , physics_system(this->entity_registry)
    , transform_to_kinematic_syncer(this->entity_registry)
    , physics_to_transform_syncer(this->entity_registry)
    , velocity_system(this->entity_registry) {
    std::cout << "LOG: Creating game object" << std::endl;
    std::cout << "LOG: Initializing raylib" << std::endl;

    // Initialize the raylib
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
    InitWindow(1920, 1080, "RevEngine");
    SetTargetFPS(60);
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
    camera_part.position = (Vector3){0.0f, 5.0f, 10.0f};
    camera_part.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera_part.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera_part.fovy = 45.0f;
    camera_part.projection = CAMERA_PERSPECTIVE;

    // Create main camera
    this->entity_registry.ctx().emplace<RlClone::MainCameraComponent>(camera_part);

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

    CloseWindow(); // Close window and OpenGL context

    std::cout << "LOG: Destroyed raylib" << std::endl;
    std::cout << "LOG: Destroyed game object successfully" << std::endl;
}


void RlClone::Game::Run() {
    while (!WindowShouldClose()) {
        this->velocity_system.Update(RlClone::Game::delta_time);
        this->transform_to_kinematic_syncer.Update(RlClone::Game::delta_time);
        this->physics_system.Update(RlClone::Game::delta_time);
        this->physics_to_transform_syncer.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(TextFormat("Hello world"), 20, 20, 20, RED);

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
