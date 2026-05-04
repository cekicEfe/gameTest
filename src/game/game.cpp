#include <game.hpp>


#include <ctime> // For time()
#include <iostream> // For std::cout std::endl

#include <glm/glm.hpp> //For glm
#include <glm/gtc/quaternion.hpp> //For glm


namespace raylib {
#include <raylib.h>
};


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
          cMaxContactConstraints)
    , rand_dev(time(nullptr)) {
    std::cout << "LOG: Creating game object" << std::endl;


    std::cout << "LOG: Created game object successfully" << std::endl;
}


RlClone::Game::~Game() {
    std::cout << "LOG: Destroying game object" << std::endl;


    std::cout << "LOG: Destroyed game object successfully" << std::endl;
}


void RlClone::Game::Init() {
    std::cout << "LOG: Initializing the game" << std::endl;


    auto entity = this->entity_registry.create();
    

    std::cout << "LOG: Initialized the game successfully" << std::endl;
}


// Our game object can use raylib related (or in the future vulkan related)
// resources, for this reason we use this function to cleanup before calling the
// object deconstructor on the app
void RlClone::Game::Cleanup() {
    std::cout << "LOG: Cleaning up game" << std::endl;

    
    BodyInterface& body_interface =
        this->game_physics_backend.GetPhysicsSystem().GetBodyInterface();

    
    auto view = this->entity_registry.view<BodyID>();

    
    std::cout << "LOG: Cleaning bodies" << std::endl;
    for (auto& view_element : view) {
        body_interface.RemoveBody(this->entity_registry.get<BodyID>(view_element));
        body_interface.DestroyBody(this->entity_registry.get<BodyID>(view_element));
        this->entity_registry.erase<BodyID>(view_element);
    }
    std::cout << "LOG: Cleaned up bodies successfully" << std::endl;
    

    std::cout << "LOG: Cleaned up game successfully" << std::endl;
}


void RlClone::Game::MainLoop() {
    while (!raylib::WindowShouldClose()) {
        this->Update();
        this->Render();
    }
}


bool RlClone::Game::ShouldGameStop() {
    return false;
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
    raylib::DrawText("Hello world", 50, 50, 20, raylib::DARKGRAY);


    // raylib::BeginMode3D(this->main_camera);
    // raylib::EndMode3D();


    raylib::EndDrawing();
}
