#ifndef GAME_HPP
#define GAME_HPP


// The Jolt headers don't include Jolt.h. Always include Jolt.h before including
// any other Jolt header. You can use Jolt.h in your precompiled header to speed
// up compilation.
#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

// STL includes
#include <cstdarg>
#include <iostream>
#include <thread>

// For entity component system
#include <entt/entt.hpp>


namespace raylib {
#include <raylib.h>
};


// Disable common warnings triggered by Jolt, you can use
// JPH_SUPPRESS_WARNING_PUSH / JPH_SUPPRESS_WARNING_POP to store and restore the
// warning state
JPH_SUPPRESS_WARNINGS

// All Jolt symbols are in the JPH namespace
using namespace JPH;

// If you want your code to compile using single or double precision write 0.0_r
// to get a Real value that compiles to double or float depending if
// JPH_DOUBLE_PRECISION is set or not.
using namespace JPH::literals;

// We're also using STL classes in this example
using namespace std;

//
//
//
namespace RlClone {

extern void TraceImpl(const char* inFMT, ...);

#ifdef JPH_ENABLE_ASSERTS
// Callback for asserts, connect this to your own assert handler if you have one
extern bool AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, uint inLine);
#endif // JPH_ENABLE_ASSERTS


// Layer that objects can be in, determines which other objects it can collide
// with Typically you at least want to have 1 layer for moving bodies and 1
// layer for static bodies, but you can have more layers if you want. E.g. you
// could have a layer for high detail collision (which is not used by the
// physics simulation but only if you do collision testing).
namespace Layers {
static constexpr ObjectLayer NON_MOVING = 0;
static constexpr ObjectLayer MOVING = 1;
static constexpr ObjectLayer NUM_LAYERS = 2;
}; // namespace Layers


/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter {
public:
    virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override;
};


// Each broadphase layer results in a separate bounding volume tree in the broad
// phase. You at least want to have a layer for non-moving and moving objects to
// avoid having to update a tree full of static objects every frame. You can
// have a 1-on-1 mapping between object layers and broadphase layers (like in
// this case) but if you have many object layers you'll be creating many broad
// phase trees, which is not efficient. If you want to fine tune your broadphase
// layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on
// the TTY.
namespace BroadPhaseLayers {
static constexpr BroadPhaseLayer NON_MOVING(0);
static constexpr BroadPhaseLayer MOVING(1);
static constexpr uint NUM_LAYERS(2);
}; // namespace BroadPhaseLayers


// BroadPhaseLayerInterface implementation
// This defines a mapping between object and broadphase layers.
class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface {
public:
    BPLayerInterfaceImpl();

    virtual uint GetNumBroadPhaseLayers() const override;

    virtual BroadPhaseLayer GetBroadPhaseLayer(ObjectLayer inLayer) const override;

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override;
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED
private:
    BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};


/// Class that determines if an object layer can collide with a broadphase layer
class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter {
public:
    virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const override;
};


// An example contact listener
class MyContactListener : public ContactListener {
public:
    // See: ContactListener
    virtual ValidateResult OnContactValidate(
        const Body& inBody1,
        const Body& inBody2,
        RVec3Arg inBaseOffset,
        const CollideShapeResult& inCollisionResult) override;
    virtual void OnContactAdded(
        const Body& inBody1,
        const Body& inBody2,
        const ContactManifold& inManifold,
        ContactSettings& ioSettings) override;
    virtual void OnContactPersisted(
        const Body& inBody1,
        const Body& inBody2,
        const ContactManifold& inManifold,
        ContactSettings& ioSettings) override;
    virtual void OnContactRemoved(const SubShapeIDPair& inSubShapePair) override;
};


// An example activation listener
class MyBodyActivationListener : public BodyActivationListener {
public:
    virtual void OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) override;
    virtual void OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData) override;
};


class Game {
private:
    // We use GameContext to initialize the JoltPhysics before
    // we initalize the stack allocated job_system, temp_allocator and
    // physics_system
    class GameContext {
    public:
        GameContext();
        ~GameContext();
    };

    static constexpr float delta_time = 1 / 60;

    GameContext game_context;

    BPLayerInterfaceImpl broad_phase_layer_interface;
    ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
    ObjectLayerPairFilterImpl object_vs_object_layer_filter;

    TempAllocatorImpl temp_allocator; // 10MB buffer
    JobSystemThreadPool job_system;

    PhysicsSystem physics_system;
    
    entt::registry registry;
  
public:
    Game(
        const uint AllocatorMaxSize = (1024 * 1024 * 10),
        const uint cMaxBodies = 1024,
        const uint cNumBodyMutexes = 0,
        const uint cMaxBodyPairs = 1024,
        const uint cMaxContactConstraints = 1024);
    ~Game();

    void Init();
    void Cleanup();

    void MainLoop();
    bool ShouldGameStop();
    void Update();
    void Render();

    void InitDemo();
    void CleanupDemo();
};


} // namespace RlClone

#endif
