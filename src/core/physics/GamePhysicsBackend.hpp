#ifndef GAME_PHYSICS_BACKEND_HPP
#define GAME_PHYSICS_BACKEND_HPP


#include <Jolt/Jolt.h>
#include <Jolt/Core/Factory.h> // For JPH::Factory::sInstance
#include <Jolt/Core/JobSystemThreadPool.h> // For JPH::JobSystemThreadPool
#include <Jolt/Core/TempAllocator.h> // For JPH::TempAllocatorImpl
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h> // For JPH::PhysicsSystem
#include <Jolt/RegisterTypes.h> // For JPH::RegisterDefaultAllocator();
          // JPH::RegisterTypes(); JPH::UnregisterTypes();
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

// For layers
#include "Layers.hpp"

// For cout and endl
#include <cstdarg>
#include <iostream>


// We're also using STL classes in this example
using namespace std;


namespace RlClone::PhysicsBackend {

  
extern void TraceImpl(const char* inFMT, ...);

  
#ifdef JPH_ENABLE_ASSERTS
extern bool
AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, uint inLine);
#endif // JPH_ENABLE_ASSERTS

  
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
    ~GamePhysicsBackend();

    JPH::PhysicsSystem& GetPhysicsSystem();
    JPH::TempAllocatorImpl& GetTempAllocator();
    JPH::JobSystemThreadPool& GetJobSystemThreadPool();
};
  
  
}; // namespace RlClone::PhysicsBackend

#endif
