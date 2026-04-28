#include <game.hpp>



void RlClone::TraceImpl(const char *inFMT, ...) {
  // Format the message
  va_list list;
  va_start(list, inFMT);
  char buffer[1024];
  vsnprintf(buffer, sizeof(buffer), inFMT, list);
  va_end(list);

  // Print to the TTY
  cout << buffer << endl;
}



#ifdef JPH_ENABLE_ASSERTS
// Callback for asserts, connect this to your own assert handler if you have one
bool RlClone::AssertFailedImpl(const char *inExpression, const char *inMessage,
                             const char *inFile, uint inLine) {
  // Print to the TTY
  cout << inFile << ":" << inLine << ": (" << inExpression << ") "
       << (inMessage != nullptr ? inMessage : "") << endl;

  // Breakpoint
  return true;
};
#endif // JPH_ENABLE_ASSERTS



bool RlClone::ObjectLayerPairFilterImpl::ShouldCollide(
    ObjectLayer inObject1, ObjectLayer inObject2) const  {
  switch (inObject1) {
  case Layers::NON_MOVING:
    return inObject2 == Layers::MOVING; // Non moving only collides with moving
  case Layers::MOVING:
    return true; // Moving collides with everything
  default:
    JPH_ASSERT(false);
    return false;
  }
}



RlClone::BPLayerInterfaceImpl::BPLayerInterfaceImpl() {
  // Create a mapping table from object to broad phase layer
  mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
  mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
}



uint RlClone::BPLayerInterfaceImpl::GetNumBroadPhaseLayers() const  {
  return BroadPhaseLayers::NUM_LAYERS;
}



BroadPhaseLayer RlClone::BPLayerInterfaceImpl::GetBroadPhaseLayer(
    ObjectLayer inLayer) const  {
  JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
  return mObjectToBroadPhase[inLayer];
}



#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
const char *RlClone::BPLayerInterfaceImpl::GetBroadPhaseLayerName(
    BroadPhaseLayer inLayer) const  {
  switch ((BroadPhaseLayer::Type)inLayer) {
  case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
    return "NON_MOVING";
  case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
    return "MOVING";
  default:
    JPH_ASSERT(false);
    return "INVALID";
  }
}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED



bool RlClone::ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(
    ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const  {
  switch (inLayer1) {
  case Layers::NON_MOVING:
    return inLayer2 == BroadPhaseLayers::MOVING;
  case Layers::MOVING:
    return true;
  default:
    JPH_ASSERT(false);
    return false;
  }
}



ValidateResult RlClone::MyContactListener::OnContactValidate(
    const Body &inBody1, const Body &inBody2, RVec3Arg inBaseOffset,
    const CollideShapeResult &inCollisionResult)  {
  cout << "Contact validate callback" << endl;

  // Allows you to ignore a contact before it is created (using layers to not
  // make objects collide is cheaper!)
  return ValidateResult::AcceptAllContactsForThisBodyPair;
}



void RlClone::MyContactListener::OnContactAdded(
    const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold,
    ContactSettings &ioSettings)  {
  cout << "A contact was added" << endl;
}



void RlClone::MyContactListener::OnContactPersisted(
    const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold,
    ContactSettings &ioSettings)  {
  cout << "A contact was persisted" << endl;
}



void RlClone::MyContactListener::OnContactRemoved(
    const SubShapeIDPair &inSubShapePair)  {
  cout << "A contact was removed" << endl;
}



void RlClone::MyBodyActivationListener::OnBodyActivated(
    const BodyID &inBodyID, uint64 inBodyUserData)  {
  cout << "A body got activated" << endl;
}



void RlClone::MyBodyActivationListener::OnBodyDeactivated(
    const BodyID &inBodyID, uint64 inBodyUserData)  {
  cout << "A body went to sleep" << endl;
}



RlClone::Game::GameContext::GameContext() {
  // Initialize the Factory
  RegisterDefaultAllocator();
  Factory::sInstance = new Factory();
  RegisterTypes();

  Trace = TraceImpl;
  JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)
}



RlClone::Game::GameContext::~GameContext() {
  // Delete the factory
  UnregisterTypes();
  delete Factory::sInstance;
}



RlClone::Game::Game(const uint AllocatorMaxSize, const uint cMaxBodies,
                    const uint cNumBodyMutexes, const uint cMaxBodyPairs,
                    const uint cMaxContactConstraints)
    : game_context(), temp_allocator(AllocatorMaxSize),
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

}



void RlClone::Game::Update(const float delta_time) {
  if (!(uint32)this->physics_system.Update(delta_time, 1, &this->temp_allocator,
                                  &this->job_system)) {
    std::cout << "Hello" << std::endl;
  }
}



void RlClone::Game::Render() {

}
