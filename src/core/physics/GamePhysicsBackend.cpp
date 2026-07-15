#include "GamePhysicsBackend.hpp"


void RlClone::PhysicsBackend::TraceImpl(const char* inFMT, ...) {
    // Format the message
    va_list list;
    va_start(list, inFMT);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), inFMT, list);
    va_end(list);

    // Print to the TTY
    std::cout << buffer << std::endl;
}


#ifdef JPH_ENABLE_ASSERTS
// Callback for asserts, connect this to your own assert handler if you have one
bool RlClone::PhysicsBackend::AssertFailedImpl(
    const char* inExpression, const char* inMessage, const char* inFile, uint inLine) {
    // Print to the TTY
    std::cout << inFile << ":" << inLine << ": (" << inExpression << ") "
              << (inMessage != nullptr ? inMessage : "") << std::endl;

    // Breakpoint
    return true;
};
#endif // JPH_ENABLE_ASSERTS


RlClone::PhysicsBackend::GamePhysicsBackend::GamePhysicsBackendContext::
    GamePhysicsBackendContext() {

    std::cout << "LOG: Initializing GamePhysicsBackendContext" << std::endl;

    // Initialize the Factory
    JPH::RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    JPH::Trace = TraceImpl;
    JPH_IF_ENABLE_ASSERTS(JPH::AssertFailed = AssertFailedImpl;)
    std::cout << "LOG: Initialized GamePhysicsBackendContext successfully" << std::endl;
}


RlClone::PhysicsBackend::GamePhysicsBackend::GamePhysicsBackendContext::
    ~GamePhysicsBackendContext() {
    std::cout << "LOG: Destroying GamePhysicsBackendContext" << std::endl;
    // Delete the factory
    JPH::UnregisterTypes();
    delete JPH::Factory::sInstance;
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
    , job_system(
          JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, thread::hardware_concurrency() - 1) {
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


JPH::PhysicsSystem& RlClone::PhysicsBackend::GamePhysicsBackend::GetPhysicsSystem() {
    return this->physics_system;
}


JPH::TempAllocatorImpl& RlClone::PhysicsBackend::GamePhysicsBackend::GetTempAllocator() {
    return this->temp_allocator;
}


JPH::JobSystemThreadPool& RlClone::PhysicsBackend::GamePhysicsBackend::GetJobSystemThreadPool() {
    return this->job_system;
}
