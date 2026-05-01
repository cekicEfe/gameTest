#include <game_physics_backend.hpp>


void RlClone::PhysicsBackend::TraceImpl(const char* inFMT, ...) {
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
bool RlClone::PhysicsBackend::AssertFailedImpl(
    const char* inExpression,
    const char* inMessage,
    const char* inFile,
    uint inLine) {
    // Print to the TTY
    cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << endl;

    // Breakpoint
    return true;
};
#endif // JPH_ENABLE_ASSERTS


bool RlClone::PhysicsBackend::ObjectLayerPairFilterImpl::ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2)
    const {
    switch (inObject1) {
        case Layers::NON_MOVING: return inObject2 == Layers::MOVING; // Non moving only collides with moving
        case Layers::MOVING: return true; // Moving collides with everything
        default: JPH_ASSERT(false); return false;
    }
}


RlClone::PhysicsBackend::BPLayerInterfaceImpl::BPLayerInterfaceImpl() {
    // Create a mapping table from object to broad phase layer
    mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
    mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
}


uint RlClone::PhysicsBackend::BPLayerInterfaceImpl::GetNumBroadPhaseLayers() const {
    return BroadPhaseLayers::NUM_LAYERS;
}


BroadPhaseLayer RlClone::PhysicsBackend::BPLayerInterfaceImpl::GetBroadPhaseLayer(ObjectLayer inLayer) const {
    JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
    return mObjectToBroadPhase[inLayer];
}


#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
const char* RlClone::PhysicsBackend::BPLayerInterfaceImpl::GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const {
    switch ((BroadPhaseLayer::Type)inLayer) {
        case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING: return "NON_MOVING";
        case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING: return "MOVING";
        default: JPH_ASSERT(false); return "INVALID";
    }
}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED


bool RlClone::PhysicsBackend::ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(
    ObjectLayer inLayer1,
    BroadPhaseLayer inLayer2) const {
    switch (inLayer1) {
        case Layers::NON_MOVING: return inLayer2 == BroadPhaseLayers::MOVING;
        case Layers::MOVING: return true;
        default: JPH_ASSERT(false); return false;
    }
}


ValidateResult RlClone::PhysicsBackend::MyContactListener::OnContactValidate(
    const Body& inBody1,
    const Body& inBody2,
    RVec3Arg inBaseOffset,
    const CollideShapeResult& inCollisionResult) {
    cout << "Contact validate callback" << endl;

    // Allows you to ignore a contact before it is created (using layers to not
    // make objects collide is cheaper!)
    return ValidateResult::AcceptAllContactsForThisBodyPair;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactAdded(
    const Body& inBody1,
    const Body& inBody2,
    const ContactManifold& inManifold,
    ContactSettings& ioSettings) {
    cout << "A contact was added" << endl;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactPersisted(
    const Body& inBody1,
    const Body& inBody2,
    const ContactManifold& inManifold,
    ContactSettings& ioSettings) {
    cout << "A contact was persisted" << endl;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactRemoved(const SubShapeIDPair& inSubShapePair) {
    cout << "A contact was removed" << endl;
}


void RlClone::PhysicsBackend::MyBodyActivationListener::OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) {
    cout << "A body got activated" << endl;
}


void RlClone::PhysicsBackend::MyBodyActivationListener::OnBodyDeactivated(
    const BodyID& inBodyID,
    uint64 inBodyUserData) {
    cout << "A body went to sleep" << endl;
}


RlClone::PhysicsBackend::GamePhysicsBackend::GamePhysicsBackendContext::GamePhysicsBackendContext() {
    // Initialize the Factory
    std::cout << "LOG: Initializing GamePhysicsBackendContext" << std::endl;
    RegisterDefaultAllocator();
    Factory::sInstance = new Factory();
    RegisterTypes();

    Trace = TraceImpl;
    JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)
    std::cout << "LOG: Initialized GamePhysicsBackendContext successfully" << std::endl;
}


RlClone::PhysicsBackend::GamePhysicsBackend::GamePhysicsBackendContext::~GamePhysicsBackendContext() {
    std::cout << "LOG: Destroying GamePhysicsBackendContext" << std::endl;
    // Delete the factory
    UnregisterTypes();
    delete Factory::sInstance;
    std::cout << "LOG: Destroyed GamePhysicsBackendContext successfully" << std::endl;
}


RlClone::PhysicsBackend::GamePhysicsBackend::GamePhysicsBackend(
    const uint AllocatorMaxSize,
    const uint cMaxBodies,
    const uint cNumBodyMutexes,
    const uint cMaxBodyPairs,
    const uint cMaxContactConstraints)
    : physics_context()
    , temp_allocator(AllocatorMaxSize)
    , job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1) {
    std::cout << "LOG: Initializing Physicsbackend" << std::endl;
    this->physics_system.Init(
        cMaxBodies,
        cNumBodyMutexes,
        cMaxBodyPairs,
        cMaxContactConstraints,
        this->broad_phase_layer_interface,
        this->object_vs_broadphase_layer_filter,
        this->object_vs_object_layer_filter);
    std::cout << "LOG: Initialized PhysicsBackend successfully" << std::endl;
}


RlClone::PhysicsBackend::GamePhysicsBackend::~GamePhysicsBackend() {
    std::cout << "LOG: Destroying GamePhysicsBackend" << std::endl;
    std::cout << "LOG: Destroyed GamePhysicsBackend successfully" << std::endl;
}


PhysicsSystem& RlClone::PhysicsBackend::GamePhysicsBackend::GetPhysicsSystem() {
    return this->physics_system;
}


TempAllocatorImpl& RlClone::PhysicsBackend::GamePhysicsBackend::GetTempAllocator() {
    return this->temp_allocator;
}


JobSystemThreadPool& RlClone::PhysicsBackend::GamePhysicsBackend::GetJobSystemThreadPool() {
    return this->job_system;
}
