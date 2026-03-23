#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include <iostream>

using namespace JPH;

int main()
{
    // Init Jolt
    Factory::sInstance = new Factory();

    RegisterTypes();

    PhysicsSystem physics;

    physics.Init(
        1024, // max bodies
        0,
        1024,
        1024,
        BroadPhaseLayerInterface(),
        ObjectVsBroadPhaseLayerFilter(),
        ObjectLayerPairFilter()
    );

    std::cout << "Jolt initialized\n";

    delete Factory::sInstance;
}
