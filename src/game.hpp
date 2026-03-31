#ifndef GAME_HPP
#define GAME_HPP

// 1. MUST be included first. This defines all the JPH_ macros,
// basic types (uint32), and sets up the environment.
#include <Jolt/Jolt.h>

// 2. These are the standard Jolt headers you need for the setup
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

// 3. Other standard headers
#include <iostream>
#include <thread>

using namespace JPH;

namespace RlClone {

// Layer definitions
namespace Layers {
static constexpr ObjectLayer NON_MOVING = 0;
static constexpr ObjectLayer MOVING = 1;
static constexpr ObjectLayer NUM_LAYERS = 2;
}; // namespace Layers

// 1. Decides if two object layers (e.g. MOVING vs NON_MOVING) can collide
class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter {
public:
  virtual bool ShouldCollide(ObjectLayer inObject1,
                             ObjectLayer inObject2) const override {
    switch (inObject1) {
    case Layers::NON_MOVING:
      return inObject2 == Layers::MOVING; // Static only hits Dynamic
    case Layers::MOVING:
      return true; // Dynamic hits everything
    default:
      return false;
    }
  }
};

// 2. Groups Object Layers into "Broad Phase" layers (for performance)
namespace BroadPhaseLayers {
static constexpr BroadPhaseLayer NON_MOVING(0);
static constexpr BroadPhaseLayer MOVING(1);
static constexpr uint NUM_LAYERS = 2;
}; // namespace BroadPhaseLayers

class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface {
public:
  BPLayerInterfaceImpl() {
    mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
    mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
  }

  virtual uint GetNumBroadPhaseLayers() const override {
    return BroadPhaseLayers::NUM_LAYERS;
  }

  virtual BroadPhaseLayer
  GetBroadPhaseLayer(ObjectLayer inLayer) const override {
    return mObjectToBroadPhase[inLayer];
  }

private:
  BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};

// 3. Decides if an Object Layer should collide with a Broad Phase layer
class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter {
public:
  virtual bool ShouldCollide(ObjectLayer inLayer1,
                             BroadPhaseLayer inLayer2) const override {
    switch (inLayer1) {
    case Layers::NON_MOVING:
      return inLayer2 == BroadPhaseLayers::MOVING;
    case Layers::MOVING:
      return true;
    default:
      return false;
    }
  }
};

class Game {
private:
  TempAllocatorImpl temp_allocator(10 * 1024 * 1024); // 10MB buffer
  JobSystemThreadPool job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers,
                                 thread::hardware_concurrency() - 1);

  BPLayerInterfaceImpl broad_phase_layer_interface;
  ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
  ObjectLayerPairFilterImpl object_vs_object_layer_filter;

  PhysicsSystem physics_system;

  const uint cMaxBodies = 1024;
  const uint cNumBodyMutexes = 0;
  const uint cMaxBodyPairs = 1024;
  const uint cMaxContactConstraints = 1024;

public:
  Game(
       
  );
  ~Game();
  void update_bodies(float delta_time);
};

}; // namespace RlClone

#endif
