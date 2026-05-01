#include <game.hpp>

void RlClone::TraceImpl(const char* inFMT, ...) {
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
bool RlClone::AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, uint inLine) {
    // Print to the TTY
    cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << endl;

    // Breakpoint
    return true;
};
#endif // JPH_ENABLE_ASSERTS


bool RlClone::ObjectLayerPairFilterImpl::ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const {
    switch (inObject1) {
        case Layers::NON_MOVING: return inObject2 == Layers::MOVING; // Non moving only collides with moving
        case Layers::MOVING: return true; // Moving collides with everything
        default: JPH_ASSERT(false); return false;
    }
}


RlClone::BPLayerInterfaceImpl::BPLayerInterfaceImpl() {
    // Create a mapping table from object to broad phase layer
    mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
    mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
}


uint RlClone::BPLayerInterfaceImpl::GetNumBroadPhaseLayers() const {
    return BroadPhaseLayers::NUM_LAYERS;
}


BroadPhaseLayer RlClone::BPLayerInterfaceImpl::GetBroadPhaseLayer(ObjectLayer inLayer) const {
    JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
    return mObjectToBroadPhase[inLayer];
}


#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
const char* RlClone::BPLayerInterfaceImpl::GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const {
    switch ((BroadPhaseLayer::Type)inLayer) {
        case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING: return "NON_MOVING";
        case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING: return "MOVING";
        default: JPH_ASSERT(false); return "INVALID";
    }
}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED


bool RlClone::ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const {
    switch (inLayer1) {
        case Layers::NON_MOVING: return inLayer2 == BroadPhaseLayers::MOVING;
        case Layers::MOVING: return true;
        default: JPH_ASSERT(false); return false;
    }
}


ValidateResult RlClone::MyContactListener::OnContactValidate(
    const Body& inBody1,
    const Body& inBody2,
    RVec3Arg inBaseOffset,
    const CollideShapeResult& inCollisionResult) {
    cout << "Contact validate callback" << endl;

    // Allows you to ignore a contact before it is created (using layers to not
    // make objects collide is cheaper!)
    return ValidateResult::AcceptAllContactsForThisBodyPair;
}


void RlClone::MyContactListener::OnContactAdded(
    const Body& inBody1,
    const Body& inBody2,
    const ContactManifold& inManifold,
    ContactSettings& ioSettings) {
    cout << "A contact was added" << endl;
}


void RlClone::MyContactListener::OnContactPersisted(
    const Body& inBody1,
    const Body& inBody2,
    const ContactManifold& inManifold,
    ContactSettings& ioSettings) {
    cout << "A contact was persisted" << endl;
}


void RlClone::MyContactListener::OnContactRemoved(const SubShapeIDPair& inSubShapePair) {
    cout << "A contact was removed" << endl;
}


void RlClone::MyBodyActivationListener::OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) {
    cout << "A body got activated" << endl;
}


void RlClone::MyBodyActivationListener::OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData) {
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


RlClone::Game::Game(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    : game_context()
    , temp_allocator(AllocatorMaxSize)
    , job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1) {

    this->physics_system.Init(
        cMaxBodies,
        cNumBodyMutexes,
        cMaxBodyPairs,
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


void RlClone::Game::Init() {
    this->InitDemo();
}


void RlClone::Game::Cleanup() {
    this->CleanupDemo();
}


void RlClone::Game::MainLoop() {
    // while(this->ShouldGameStop())
}


bool RlClone::Game::ShouldGameStop() {
    static uint counter = 60*10;
    for (; counter; counter--) {
    }
}


void RlClone::Game::Update() {
    this->physics_system.Update(delta_time, 1, &this->temp_allocator, &this->job_system);
}


void RlClone::Game::Render() {}


void RlClone::Game::InitDemo() {
	// A body activation listener gets notified when bodies activate and go to sleep
	// Note that this is called from a job so whatever you do here needs to be thread safe.
	// Registering one is entirely optional.
    MyBodyActivationListener body_activation_listener;
	physics_system.SetBodyActivationListener(&body_activation_listener);

    
	// A contact listener gets notified when bodies (are about to) collide, and when they separate again.
	// Note that this is called from a job so whatever you do here needs to be thread safe.
	// Registering one is entirely optional.
	MyContactListener contact_listener;
	physics_system.SetContactListener(&contact_listener);

    
    // The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
	// variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
	BodyInterface &body_interface = physics_system.GetBodyInterface();

    
	// Next we can create a rigid body to serve as the floor, we make a large box
	// Create the settings for the collision volume (the shape).
	// Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
	BoxShapeSettings floor_shape_settings(Vec3(100.0f, 1.0f, 100.0f));
	floor_shape_settings.SetEmbedded(); // A ref counted object on the stack (base class RefTarget) should be marked as such to prevent it from being freed when its reference count goes to 0.

    
	// Create the shape
	ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
	ShapeRefC floor_shape = floor_shape_result.Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

    
	// Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
	BodyCreationSettings floor_settings(floor_shape, RVec3(0.0_r, -1.0_r, 0.0_r), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);

    
	// Create the actual rigid body
	Body *floor = body_interface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr


    // Add it to the world
	body_interface.AddBody(floor->GetID(), EActivation::DontActivate);

    
	// Now create a dynamic body to bounce on the floor
	// Note that this uses the shorthand version of creating and adding a body to the world
	BodyCreationSettings sphere_settings(new SphereShape(0.5f), RVec3(0.0_r, 2.0_r, 0.0_r), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
	BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

    
	// Now you can interact with the dynamic body, in this case we're going to give it a velocity.
	// (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
	body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));


	// Optional step: Before starting the physics simulation you can optimize the broad phase. This improves collision detection performance (it's pointless here because we only have 2 bodies).
	// You should definitely not call this every frame or when e.g. streaming in a new level section as it is an expensive operation.
	// Instead insert all new objects in batches instead of 1 at a time to keep the broad phase efficient.
	physics_system.OptimizeBroadPhase();
}


void RlClone::Game::CleanupDemo() {

    BodyInterface &body_interface = this->physics_system.GetBodyInterface();
    BodyIDVector &bodies 

}
