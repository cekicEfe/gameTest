// 1. MUST be included first. This defines all the JPH_ macros,
// basic types (uint32), and sets up the environment.
#include <Jolt/Core/Core.h>
#include <Jolt/Jolt.h>

// 2. These are the standard Jolt headers you need for the setup
#include <Jolt/RegisterTypes.h>

#include <Jolt/Core/Factory.h>

#include <Jolt/Core/TempAllocator.h>

#include <Jolt/Core/JobSystemThreadPool.h>

#include <Jolt/Physics/PhysicsSystem.h>

#include <Jolt/Physics/Body/BodyCreationSettings.h>

#include <Jolt/Physics/Collision/Shape/SphereShape.h>

// 3. Other standard headers
#include <iostream>
#include <thread>

// SUPER BAD SOLUTION TO THIS YET IT WORKS
namespace raylib {
#include <raylib.h>
}

// Optional: Jolt uses its own namespace macros, but you can use
// the JPH namespace for convenience in a .cpp file.
// #ifdef JPH_PROFILE_ENABLED
// namespace JPH {
//     // These satisfy the linker for the internal Jolt profiler
//     thread_local ProfileThread *ProfileThread::sInstance = nullptr;
//     bool ProfileMeasurement::sOutOfSamplesReported = false;
// }
// #endif
using namespace JPH;

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

int main() {
  // 1. Initialize the Factory
  RegisterDefaultAllocator();
  Factory::sInstance = new Factory();
  RegisterTypes();

  // 2. Setup Memory and Threading
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

  // Fixed the variable name and passed the filter instances
  physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs,
                      cMaxContactConstraints, broad_phase_layer_interface,
                      object_vs_broadphase_layer_filter,
                      object_vs_object_layer_filter);

  std::cout << "GAME:Jolt Physics is now fully initialized!" << std::endl;

  // 1. Get a reference to the body interface (the way you interact with bodies)
  BodyInterface &body_interface = physics_system.GetBodyInterface();

  // 2. Create a Sphere Shape (radius 0.5m)
  SphereShapeSettings sphere_settings(0.5f);
  ShapeSettings::ShapeResult sphere_result = sphere_settings.Create();
  ShapeRefC sphere_shape = sphere_result.Get(); // Create the actual shape

  // 3. Create the Body Creation Settings
  // Positions: (0, 10, 0), Layer: MOVING, MotionType: Dynamic
  BodyCreationSettings sphere_creation_settings(
      sphere_shape, RVec3(0.0f, 10.0f, 0.0f), Quat::sIdentity(),
      EMotionType::Dynamic, Layers::MOVING);

  // 4. Create the Body and Add it to the world
  BodyID sphere_id = body_interface.CreateAndAddBody(sphere_creation_settings,
                                                     EActivation::Activate);

  // Start raylib here
  //--------------------------------------------------------------------------------------

  const int screenWidth = 800;
  const int screenHeight = 450;

  raylib::InitWindow(screenWidth, screenHeight,
                     "raylib [core] example - 3d camera free");

  // Define the camera to look into our 3d world
  raylib::Camera3D camera = {0};
  camera.position = (raylib::Vector3){10.0f, 10.0f, 10.0f}; // Camera position
  camera.target =
      (raylib::Vector3){0.0f, 0.0f, 0.0f}; // Camera looking at point
  camera.up = (raylib::Vector3){
      0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;   // Camera field-of-view Y
  camera.projection = raylib::CAMERA_PERSPECTIVE; // Camera projection type

  raylib::Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

  raylib::DisableCursor(); // Limit cursor to relative movement inside the
                           // window

  raylib::SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  const float delta_time = 1.0f / 60.0f;
  // Main game loop
  while (!raylib::WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    raylib::UpdateCamera(&camera, raylib::CAMERA_FREE);

    physics_system.Update(delta_time, 1, &temp_allocator, &job_system);

    // Get the sphere position
    RVec3 position = body_interface.GetPosition(sphere_id);
    std::cout << ": Sphere Height = " << position.GetY() << "m" << std::endl;

    if (raylib::IsKeyPressed(raylib::KEY_Z))
      camera.target = (raylib::Vector3){0.0f, 0.0f, 0.0f};
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    raylib::BeginDrawing();

    raylib::ClearBackground(raylib::RAYWHITE);

    raylib::BeginMode3D(camera);
    raylib::DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, raylib::RED);
    raylib::DrawSphere((raylib::Vector3){position.GetX(), position.GetY(), position.GetZ()},
                       5.0f, raylib::RED);
        raylib::DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, raylib::MAROON);
    raylib::DrawGrid(10, 1.0f);
    raylib::EndMode3D();

    raylib::DrawRectangle(10, 10, 320, 93, raylib::Fade(raylib::SKYBLUE, 0.5f));
    raylib::DrawRectangleLines(10, 10, 320, 93, raylib::BLUE);

    raylib::DrawText("Free camera default controls:", 20, 20, 10,
                     raylib::BLACK);
    raylib::DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10,
                     raylib::DARKGRAY);
    raylib::DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10,
                     raylib::DARKGRAY);
    raylib::DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, raylib::DARKGRAY);

    raylib::EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  raylib::CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
