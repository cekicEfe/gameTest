#include "Game.hpp"


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    // Create the systems here
    : power_car_creator_system(this->entity_registry)
    , velocity_system(this->entity_registry)
    , transform_to_kinematic_syncer(this->entity_registry)
    , power_car_updater_system(this->entity_registry)
    , physics_component_updater(this->entity_registry)
    , physics_to_transform_syncer(this->entity_registry)
    , render_3d_system(this->entity_registry)
    , physics_component_destroyer(this->entity_registry) {
    std::cout << "LOG: Creating game object" << std::endl;

    // Initialize the raylib
    std::cout << "LOG: Initializing raylib" << std::endl;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
    InitWindow(1920, 1080, "RevEngine");
    SetTargetFPS(60);
    HideCursor();
    DisableCursor();
    std::cout << "LOG: Initialized raylib" << std::endl;

    // Inject game physics backend to the registry
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

    // Test builder systems
    RlClone::DirectionSphereBuilder(this->entity_registry, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f});
    RlClone::TemplateFloorBuilder(this->entity_registry);

    this->power_car_creator_system.Create();
    
    std::cout << "LOG: Created game object successfully" << std::endl;
}


RlClone::Game::~Game() {
    std::cout << "LOG: Destroying game object" << std::endl;

    // Destroy components
    std::cout << "LOG: Destroying PhysicsComponents" << std::endl;
    this->physics_component_destroyer.Destroy();
    std::cout << "LOG: Destroyed PhysicsComponents successfully" << std::endl;

    // Destroy context objects
    this->entity_registry.ctx().erase<RlClone::PhysicsBackend::GamePhysicsBackend>();
    this->entity_registry.ctx().erase<RlClone::AssetManager>();
    this->entity_registry.ctx().erase<RlClone::MainCameraComponent>();

    // Close window and OpenGL context
    std::cout << "LOG: Destroying raylib" << std::endl;
    CloseWindow();
    std::cout << "LOG: Destroyed raylib" << std::endl;

    std::cout << "LOG: Destroyed game object successfully" << std::endl;
}


void RlClone::Game::Run() {
    while (!WindowShouldClose()) {
        this->velocity_system.Update(RlClone::Game::delta_time);
        this->transform_to_kinematic_syncer.Update(RlClone::Game::delta_time);
        this->power_car_updater_system.PrePhysicsUpdate(/*Does not take delta time*/);
        this->physics_component_updater.Update(RlClone::Game::delta_time);
        this->physics_to_transform_syncer.Update(/*Does not take delta time*/);

        // Start drawing after here
        BeginDrawing();
        ClearBackground(BLACK);

        // Render UIs and 2d objects
        DrawText(TextFormat("Hello world"), 20, 20, 20, RED);

        // Render 3d objects.
        {
            auto& main_camera = this->entity_registry.ctx().get<RlClone::MainCameraComponent>();
            Camera3D& camera_part = main_camera.camera_part;
            UpdateCamera(&camera_part, CAMERA_FREE);
            {
                BeginMode3D(camera_part);
                this->render_3d_system.Render();

                DrawGrid(1000.0f, 1.0f);
                DrawLine3D((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){500.0f, 0.0f, 0.0f}, RED);
                DrawLine3D((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 500.0f, 0.0f}, GREEN);
                DrawLine3D((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 500.0f}, BLUE);

                EndMode3D();
            }
        }
        EndDrawing();
    }
}
