#ifndef GAME_PHYSICS_BACKEND_HPP
#define GAME_PHYSICS_BACKEND_HPP

// The Jolt headers don't include Jolt.h. Always include Jolt.h before including
// any other Jolt header. You can use Jolt.h in your precompiled header to speed
// up compilation.
#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/Core/Factory.h> // For JPH::Factory::sInstance
#include <Jolt/Core/JobSystemThreadPool.h> // For JPH::JobSystemThreadPool
#include <Jolt/Core/TempAllocator.h> // For JPH::TempAllocatorImpl
#include <Jolt/Physics/PhysicsSettings.h> //
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem
#include <Jolt/RegisterTypes.h> // For JPH::RegisterDefaultAllocator();
          // JPH::RegisterTypes(); JPH::UnregisterTypes();

// For Layer implementation
#include <Game/Layers.hpp>

// For cout and endl
#include <cstdarg>
#include <iostream>

// We're also using STL classes in this example
using namespace std;

namespace RlClone::PhysicsBackend {

// To trace physics
extern void TraceImpl(const char* inFMT, ...);

#ifdef JPH_ENABLE_ASSERTS
// Callback for asserts, connect this to your own assert handler if you have one
extern bool
AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, uint inLine);
#endif // JPH_ENABLE_ASSERTS

// For the future configuring
struct GamePhysicsBackendConfig {};

class GamePhysicsBackend {
private:
    class GamePhysicsBackendContext {
    public:
        GamePhysicsBackendContext();
        ~GamePhysicsBackendContext();
    };

    GamePhysicsBackendContext physics_context;

    RlClone::PhysicsBackend::BPLayerInterfaceImpl broad_phase_layer_interface;
    RlClone::PhysicsBackend::ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
    RlClone::PhysicsBackend::ObjectLayerPairFilterImpl object_vs_object_layer_filter;

    JPH::PhysicsSystem physics_system;
    JPH::TempAllocatorImpl temp_allocator;
    JPH::JobSystemThreadPool job_system;
public:
    GamePhysicsBackend(
        const uint AllocatorMaxSize = (1024 * 1024 * 10),
        const uint cMaxBodies = 1024,
        const uint cNumBodyMutexes = 0,
        const uint cMaxBodyPairs = 1024,
        const uint cMaxContactConstraints = 1024);
    GamePhysicsBackend(GamePhysicsBackendConfig config);
    ~GamePhysicsBackend();

    static constexpr float delta_time = 1 / 60;

    JPH::PhysicsSystem& GetPhysicsSystem();
    JPH::TempAllocatorImpl& GetTempAllocator();
    JPH::JobSystemThreadPool& GetJobSystemThreadPool();
};

}; // namespace RlClone::PhysicsBackend

#endif
