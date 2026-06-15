#include <game/Game.hpp>


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    : game_physics_backend(
          AllocatorMaxSize, cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints)
    , render_3d_system(this->entity_registry, this->asset_manager)
    , physics_system(
          this->entity_registry,
          this->game_physics_backend.GetPhysicsSystem(),
          this->game_physics_backend.GetTempAllocator(),
          this->game_physics_backend.GetJobSystemThreadPool()) {
    std::cout << "LOG: Creating game object" << std::endl;
    std::cout << "LOG: Initializing raylib" << std::endl;


    // Initialize the raylib
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
    InitWindow(1920, 1080, "RevEngine");
    SetTargetFPS(60); // Set the game to run at 60 frames-per-second
    HideCursor();
    DisableCursor();


    Camera3D camera_part = {0};
    camera_part.position = (Vector3){0.0f, 5.0f, 10.0f};
    camera_part.target = (Vector3){0.0f, 0.0f, 0.0f}; // Camera looking at point
    camera_part.up = (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector
                                                  //(rotation towards target)
    camera_part.fovy = 45.0f; // Camera field-of-view Y
    camera_part.projection = CAMERA_PERSPECTIVE; // Camera mode type


    entt::entity camera = this->entity_registry.create();
    this->entity_registry.emplace<RlClone::MainCameraComponent>(camera, camera_part);


    std::cout << "LOG: Initialized raylib" << std::endl;
    std::cout << "LOG: Created game object successfully" << std::endl;
}


RlClone::Game::~Game() {
    std::cout << "LOG: Destroying game object" << std::endl;
    std::cout << "LOG: Destroying raylib" << std::endl;


    CloseWindow(); // Close window and OpenGL context


    std::cout << "LOG: Destroyed raylib" << std::endl;
    std::cout << "LOG: Destroyed game object successfully" << std::endl;
}


void RlClone::Game::Run() {
    while (!WindowShouldClose()) {
        this->physics_system.Update(RlClone::Game::delta_time);


        BeginDrawing();
        ClearBackground(BLACK);


        DrawFPS(20, 20);
        DrawText("Hello world", 50, 50, 20, DARKGRAY);


        auto view = this->entity_registry.view<RlClone::MainCameraComponent>();
        for (auto& camera_entity : view) {
            Camera3D& camera_part =
                this->entity_registry.get<RlClone::MainCameraComponent>(camera_entity).camera_part;
            UpdateCamera(&camera_part, CAMERA_FREE);

            {
                BeginMode3D(camera_part);


                this->render_3d_system.Update(RlClone::Game::delta_time);
                DrawCubeWires((Vector3){0.0, 0.0, 0.0}, 1.0f, 1.0f, 1.0f, WHITE);
                DrawGrid(100, 1);


                EndMode3D();
            }
        }


        EndDrawing();
    }
}
