#include <game/Game.hpp>


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    : game_physics_backend(
          AllocatorMaxSize, cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints)
    , render_system(
          this->game_physics_backend.GetPhysicsSystem(),
          this->entity_registry,
          this->asset_manager) {
    std::cout << "LOG: Creating game object" << std::endl;


    std::cout << "LOG: Created game object successfully" << std::endl;
}


RlClone::Game::~Game() {
    std::cout << "LOG: Destroying game object" << std::endl;


    std::cout << "LOG: Destroyed game object successfully" << std::endl;
}


void RlClone::Game::Init() {
    std::cout << "LOG: Initializing the game" << std::endl;


    std::cout << "LOG: Initialized the game successfully" << std::endl;
}


// Our game object can use raylib related (or in the future vulkan related)
// resources, for this reason we use this function to cleanup before calling the
// object deconstructor on the app
void RlClone::Game::Cleanup() {
    std::cout << "LOG: Cleaning up game" << std::endl;


    std::cout << "LOG: Cleaned up game successfully" << std::endl;
}


void RlClone::Game::MainLoop() {
    while (!raylib::WindowShouldClose()) // Will use ShouldGameStop in the future
    {
        this->Update();
        this->Render();
    }
}


bool RlClone::Game::ShouldGameStop() { // Will be more complex in the future
    return false;
}


void RlClone::Game::Update() {
    // Update the physics objects in physics system
    this->game_physics_backend.GetPhysicsSystem().Update(
        RlClone::Game::delta_time,
        1,
        &this->game_physics_backend.GetTempAllocator(),
        &this->game_physics_backend.GetJobSystemThreadPool());
}


void RlClone::Game::Render() {
    raylib::BeginDrawing();
    raylib::ClearBackground(raylib::RAYWHITE);


    raylib::DrawFPS(20, 20);
    raylib::DrawText("Hello world", 50, 50, 20, raylib::DARKGRAY);

    
    // We render objects via render system
    this->render_system.Update(RlClone::Game::delta_time);

    
    raylib::EndDrawing();
}
