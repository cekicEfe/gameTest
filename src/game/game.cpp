#include <game.hpp>


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    : game_physics_backend(
          AllocatorMaxSize,
          cMaxBodies,
          cNumBodyMutexes,
          cMaxBodyPairs,
          cMaxContactConstraints) {
    std::cout << "LOG: Creating game object" << std::endl;
    std::cout << "LOG: Created game object successfully" << std::endl;
}


RlClone::Game::~Game() {
    std::cout << "LOG: Destroying game object" << std::endl;
    std::cout << "LOG: Destroyed game object successfully" << std::endl;
}


void RlClone::Game::Init() {
    std::cout << "LOG: Initializing the game" << std::endl;
    this->InitDemo();
    std::cout << "LOG: Initialized the game successfully" << std::endl;
}

// Our game object can use raylib related (or in the future vulkan related)
// resources, for this reason we use this function to cleanup before calling the
// object deconstructor on the app
void RlClone::Game::Cleanup() {
    std::cout << "LOG: Cleaning up game" << std::endl;
    this->CleanupDemo();
    std::cout << "LOG: Cleaned up game successfully" << std::endl;
}


void RlClone::Game::MainLoop() {
    while (!raylib::WindowShouldClose()) {
        this->Update();
        this->Render();
    }
}


bool RlClone::Game::ShouldGameStop() {
    static uint counter = 60 * 10;
    if (counter != 0) {
        return false;
    }
    else {
        counter--;
        return true;
    }
}


void RlClone::Game::Update() {
    this->game_physics_backend.GetPhysicsSystem().Update(
        PhysicsBackend::GamePhysicsBackend::delta_time,
        1,
        &this->game_physics_backend.GetTempAllocator(),
        &this->game_physics_backend.GetJobSystemThreadPool());
}


void RlClone::Game::Render() {
    raylib::BeginDrawing();


    raylib::ClearBackground(raylib::RAYWHITE);


    raylib::DrawFPS(20, 20);
    raylib::DrawText("Vro or Cro", 50, 50, 20, raylib::DARKGRAY);

    
    raylib::BeginMode3D(this->main_camera);
    raylib::EndMode3D();

    
    raylib::EndDrawing();
}


void RlClone::Game::InitDemo() {
    std::cout << "LOG: Initializing Demo" << std::endl;


    // Optional step: Before starting the physics simulation you can optimize the broad phase.
    // This improves collision detection performance.
    // You should definitely not call this every frame or when e.g. streaming in a new level section
    // as it is an expensive operation. Instead insert all new objects in batches instead of 1 at a
    // time to keep the broad phase efficient.
    this->game_physics_backend.GetPhysicsSystem().OptimizeBroadPhase();


    std::cout << "LOG: Initialized Demo successfully" << std::endl;
}


void RlClone::Game::CleanupDemo() {
    std::cout << "LOG: Cleaning up Demo" << std::endl;


    std::cout << "LOG: Cleaned up demo successfully" << std::endl;
}
