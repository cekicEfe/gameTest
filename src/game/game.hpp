#ifndef GAME_HPP
#define GAME_HPP


// STL includes
#include <iostream>
#include <thread>


// The physics backend
#include <game/game_physics_backend.hpp>


// For entity component system
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace raylib {
#include <raylib.h>
};


// All Jolt symbols are in the JPH namespace
using namespace JPH;


// If you want your code to compile using single or double precision write 0.0_r
// to get a Real value that compiles to double or float depending if
// JPH_DOUBLE_PRECISION is set or not.
using namespace JPH::literals;


namespace RlClone {


class TestFloorFactory {
public:
    static void CreateTestFloor(entt::registry& registry, BodyInterface& body_interface) {
        // Next we can create a rigid body to serve as the floor, we make a large box
        // Create the settings for the collision volume (the shape).
        // Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
        BoxShapeSettings floor_shape_settings(Vec3(100.0f, 1.0f, 100.0f));
        floor_shape_settings
            .SetEmbedded(); // A ref counted object on the stack (base class RefTarget) should be marked as
                            // such to prevent it from being freed when its reference count goes to 0.


        // Create the shape
        ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
        ShapeRefC floor_shape =
            floor_shape_result
                .Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()


        // Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
        BodyCreationSettings floor_settings(
            floor_shape,
            RVec3(0.0_r, -1.0_r, 0.0_r),
            Quat::sIdentity(),
            EMotionType::Static,
            PhysicsBackend::Layers::NON_MOVING);


        // Create the actual rigid body
        Body* floor =
            body_interface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr


        // Add it to the world
        body_interface.AddBody(floor->GetID(), EActivation::DontActivate);

        
        auto floor_entity = registry.create();

        
        registry.emplace<BodyID>(floor_entity, floor->GetID());
        
        
    }
  
    static void DestroyTestFloor(entt::registry& registry, BodyInterface& body_interface, entt::entity entity) {


      BodyID floorID = registry.get<BodyID>(entity);

      
      body_interface.RemoveBody( floorID());
      body_interface.DestroyBody(floorID());

      
      registry.destroy(entity);

      
    }
  
    static void RenderTestFloor(entt::registry& registry, BodyInterface& body_interface, entt::entt entity) {

      
      BodyID floorID = registry.get<BodyID>(entity);
      RVec3 pos = body_interface.GetPosition (floorID);
      
      
    }
};

  
class Game {
private:
    entt::registry entity_registry;
    PhysicsBackend::GamePhysicsBackend game_physics_backend;

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
