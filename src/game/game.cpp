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
    : game_context(), temp_allocator(DEFAULT_BUFFER_SIZE),
      job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers,
                 thread::hardware_concurrency() - 1) {

  this->physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs,
                            cMaxContactConstraints,
                            this->broad_phase_layer_interface,
                            this->object_vs_broadphase_layer_filter,
                            this->object_vs_object_layer_filter);

  std::cout << "LOG: Initialized the physics system" << std::endl;
}

RlClone::Game::~Game() {
  //
  this->registry.clear();
}

void RlClone::Game::InitDemo() {
  // Crate test entity !!!
  // Get the interface to create bodies
  BodyInterface &body_interface = this->physics_system.GetBodyInterface();

  // --- Create a Static Floor ---
  // A 100x1x100 box at y=-1 (so the top is at y=0)
  BoxShapeSettings floor_shape_settings(Vec3(100.0f, 1.0f, 100.0f));
  ShapeRefC floor_shape = floor_shape_settings.Create().Get();
  BodyCreationSettings floor_settings(floor_shape, RVec3(0.0f, -1.0f, 0.0f),
                                      Quat::sIdentity(), EMotionType::Static,
                                      Layers::NON_MOVING);
  BodyID floor_id = body_interface.CreateAndAddBody(floor_settings,
                                                    EActivation::DontActivate);
  body_interface.SetFriction(floor_id, 0.5f);
  std::cout << "LOG: Created floor " << __FILE__ << " " << __LINE__ << std::endl;

  // --- Create a Dynamic Sphere ---
  // A sphere with radius 0.5m starting at y=10
  SphereShapeSettings sphere_shape_settings(0.5f);
  ShapeRefC sphere_shape = sphere_shape_settings.Create().Get();
  BodyCreationSettings sphere_settings(sphere_shape, RVec3(0.0f, 70.0f, 0.0f),
                                       Quat::sIdentity(), EMotionType::Dynamic,
                                       Layers::MOVING);
  JPH::BodyID sphere_id =
      body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);
  body_interface.SetRestitution(sphere_id, 0.60f);
  std::cout << "LOG: Created sphere " << __FILE__ << " " << __LINE__
            << std::endl;

  // --- Put sphere into registry ---
  auto sphere_entity = this->registry.create();
  this->registry.emplace<RlClone::Sphere>(sphere_entity,
                                          (RlClone::Sphere){.radius = 0.5f});
  this->registry.emplace<JPH::BodyID>(sphere_entity, sphere_id);
  std::cout << "LOG: Pushed sphere to the registry " << __FILE__ << " "
            << __LINE__ << std::endl;

  // --- Put floor into registry ---
  auto floor_entity = this->registry.create();
  this->registry.emplace<RlClone::Cube>(
      floor_entity,
      (RlClone::Cube){.height = 1.0f, .width = 100.0f, .length = 100.0f});
  this->registry.emplace<JPH::BodyID>(floor_entity, floor_id);
  std::cout << "LOG: Pushed floor to the registry " << __FILE__ << " "
            << __LINE__ << std::endl;
}

void RlClone::Game::Update(const float delta_time) {
  this->physics_system.Update(delta_time, 1, &this->temp_allocator,
                              &this->job_system);
}

void RlClone::Game::Render() {
  BodyInterface &body_interface = physics_system.GetBodyInterface();

  // We render spheres here
  auto spheres = this->registry.view<RlClone::Sphere, JPH::BodyID>();
  for (auto entity : spheres) {
    auto [bodySphere, bodyId] = spheres.get<Sphere, BodyID>(entity);
    RVec3 pos = body_interface.GetPosition(bodyId);
  }

  // We render cubes here
  auto cubes = this->registry.view<Cube, BodyID>();
  for (auto entity : cubes) {
    auto [bodyCube, bodyId] = cubes.get<Cube, BodyID>(entity);
    RVec3 pos = body_interface.GetPosition(bodyId);
  }
}
