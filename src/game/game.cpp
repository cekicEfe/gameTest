#include <game.hpp>


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    : game_physics_backend() {
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
    raylib::DrawText("Hello vro or cro", 10, 10, 20, raylib::DARKGRAY);
    raylib::EndDrawing();
}


void RlClone::Game::InitDemo() {
    std::cout << "LOG: Initializing Demo" << std::endl;
    // A body activation listener gets notified when bodies activate and go to sleep
    // Note that this is called from a job so whatever you do here needs to be thread safe.
    // Registering one is entirely optional.

    // MyBodyActivationListener body_activation_listener;
    // this->game_physics_backend.GetPhysicsSystem().SetBodyActivationListener(&body_activation_listener);


    // A contact listener gets notified when bodies (are about to) collide, and when they separate again.
    // Note that this is called from a job so whatever you do here needs to be thread safe.
    // Registering one is entirely optional.

    // MyContactListener contact_listener;
    // this->game_physics_backend.GetPhysicsSystem().SetContactListener(&contact_listener);


    // The main way to interact with the bodies in the physics system is through the body interface. There is a locking
    // and a non-locking variant of this. We're going to use the locking version (even though we're not planning to
    // access bodies from multiple threads)
    BodyInterface& body_interface = this->game_physics_backend.GetPhysicsSystem().GetBodyInterface();


    // Now create a dynamic body to bounce on the floor
    // Note that this uses the shorthand version of creating and adding a body to the world
    BodyCreationSettings sphere_settings(
        new SphereShape(0.5f),
        RVec3(0.0_r, 2.0_r, 0.0_r),
        Quat::sIdentity(),
        EMotionType::Dynamic,
        PhysicsBackend::Layers::MOVING);
    BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);


    // Now you can interact with the dynamic body, in this case we're going to give it a velocity.
    // (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to
    // the physics system)
    body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));


    // Optional step: Before starting the physics simulation you can optimize the broad phase. This improves collision
    // detection performance (it's pointless here because we only have 2 bodies). You should definitely not call this
    // every frame or when e.g. streaming in a new level section as it is an expensive operation. Instead insert all new
    // objects in batches instead of 1 at a time to keep the broad phase efficient.
    this->game_physics_backend.GetPhysicsSystem().OptimizeBroadPhase();

    //this->entity_registry
    
    std::cout << "LOG: Initialized Demo successfully" << std::endl;
}


void RlClone::Game::CleanupDemo() {
    std::cout << "LOG: Cleaning up Demo" << std::endl;

    std::cout << "LOG: Cleaned up demo successfully" << std::endl;
}
