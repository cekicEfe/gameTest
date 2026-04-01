#ifndef GAME_HPP
#define GAME_HPP

#include <Jolt/Jolt.h>

#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

#include <iostream>
#include <thread>

using namespace JPH;

namespace RlClone {

namespace Layers {
static constexpr ObjectLayer NON_MOVING = 0;
static constexpr ObjectLayer MOVING = 1;
static constexpr ObjectLayer NUM_LAYERS = 2;
}; // namespace Layers

namespace BroadPhaseLayers {
static constexpr BroadPhaseLayer NON_MOVING(0);
static constexpr BroadPhaseLayer MOVING(1);
static constexpr uint NUM_LAYERS = 2;
}; // namespace BroadPhaseLayers

// Decides if two object layers (e.g. MOVING vs NON_MOVING) can collide
class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter {
public:
  virtual bool ShouldCollide(ObjectLayer inObject1,
                             ObjectLayer inObject2) const override {
    switch (inObject1) {
    case Layers::NON_MOVING:
      return inObject2 == Layers::MOVING;
    case Layers::MOVING:
      return true;
    default:
      return false;
    }
  }
};

// Maps Object Layer to Broad Phase Layer
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

// Decides if an Object Layer should collide with a Broad Phase layer
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

#define DEFAULT_BUFFER_SIZE 1024 * 1024 * 10

class Game {
private:
  TempAllocatorImpl temp_allocator; // 10MB buffer
  JobSystemThreadPool job_system;

  PhysicsSystem physics_system;

public:
  Game(const uint AllocatorMaxSize = DEFAULT_BUFFER_SIZE,
       const uint cMaxBodies = 1024, const uint cNumBodyMutexes = 0,
       const uint cMaxBodyPairs = 1024,
       const uint cMaxContactConstraints = 1024);
  ~Game();

  void update(float delta_time);
};

}; // namespace RlClone

#endif
