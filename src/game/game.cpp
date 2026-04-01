#include <game.hpp>

RlClone::Game::Game(const uint AllocatorMaxSize, const uint cMaxBodies,
                    const uint cNumBodyMutexes, const uint cMaxBodyPairs,
                    const uint cMaxContactConstraints)
    : temp_allocator(DEFAULT_BUFFER_SIZE),
      job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers,
                 thread::hardware_concurrency() - 1) {

  // TODO: Make sure that we execute lines
  // RegisterDefaultAllocator();
  // Factory::sInstance = new Factory();
  // RegisterTypes();
  // ...
  // BEFORE
  // Initializing job system and temp_allocator !!!
  // This shit somehow causes segfault
  //

  
  // 1. Initialize the Factory
  RegisterDefaultAllocator();
  Factory::sInstance = new Factory();
  RegisterTypes();

  RlClone::BPLayerInterfaceImpl broad_phase_layer_interface;
  RlClone::ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
  RlClone::ObjectLayerPairFilterImpl object_vs_object_layer_filter;

  std::cout << "Hello?" << std::endl;
  
  this->physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs,
                            cMaxContactConstraints,
                            broad_phase_layer_interface,
                            object_vs_broadphase_layer_filter,
                            object_vs_object_layer_filter
  );
}

RlClone::Game::~Game() {
  //
  delete Factory::sInstance;
}

void RlClone::Game::update(const float delta_time) {
  this->physics_system.Update(delta_time, 1, &this->temp_allocator,
                              &this->job_system);
}
