#include <game.hpp>

RlClone::Game::GameContext::GameContext() {
  // Initialize the Factory
  RegisterDefaultAllocator();
  Factory::sInstance = new Factory();
  RegisterTypes();
}

RlClone::Game::GameContext::~GameContext() {
  // Delete the factory
  delete Factory::sInstance;
}

RlClone::Game::Game(const uint AllocatorMaxSize, const uint cMaxBodies,
                    const uint cNumBodyMutexes, const uint cMaxBodyPairs,
                    const uint cMaxContactConstraints)
    : game_context(GameContext()), temp_allocator(DEFAULT_BUFFER_SIZE),
      job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers,
                 thread::hardware_concurrency() - 1) {
  RlClone::BPLayerInterfaceImpl broad_phase_layer_interface;
  RlClone::ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
  RlClone::ObjectLayerPairFilterImpl object_vs_object_layer_filter;

  this->physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs,
                            cMaxContactConstraints, broad_phase_layer_interface,
                            object_vs_broadphase_layer_filter,
                            object_vs_object_layer_filter);

  std::cout << "LOG: Initialized the physics system" << std::endl;
}

RlClone::Game::~Game() {
  //
}

void RlClone::Game::init_demo() {
  //
  
}

void RlClone::Game::update(const float delta_time) {
  this->physics_system.Update(delta_time, 1, &this->temp_allocator,
                              &this->job_system);
}

void RlClone::Game::render() {
  // Draw
  //----------------------------------------------------------------------------------
  raylib::BeginDrawing();
  raylib::ClearBackground(raylib::RAYWHITE);
  raylib::EndDrawing();
}
