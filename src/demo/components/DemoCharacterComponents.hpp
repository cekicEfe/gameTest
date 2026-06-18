#ifndef DEMO_CHARACTER_COMPONENTS_HPP
#define DEMO_CHARACTER_COMPONENTS_HPP

// For uint32_t
#include <cstdint>

#include <string>


namespace RlClone::Demo {


const std::string DEMO_FLOOR_MODEL("resources/test_models/hello_cube/HelloCube.obj");
const std::string DEMO_FLOOR_TEXTURE("resources/test_models/hello_cube/HelloCubeTexture.png");


const std::string DEMO_CHARACTER_MODEL("resources/test_models/test_ship/SpaceThingey.obj");
const std::string
    DEMO_CHARACTER_TEXTURE("resources/test_models/test_ship/SpaceThingeyBaseTexture.png");

const std::string DEMO_SPHERE_MODEL("resources/test_models/hello_sphere/HelloSphere.obj");
const std::string DEMO_SPHERE_TEXTURE("resources/test_models/hello_sphere/SphereUV.png");

const std::string DEMO_FRAGMENT_SHADER("resources/shaders/default_shader/DefaultShader.frag");
const std::string DEMO_VERTEX_SHADER("resources/shaders/default_shader/DefaultShader.vert");


struct DemoCharacterTag {};


struct DemoCharacterControlComponent {
    bool forward = false;
    bool backward = false;
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
};


}; // namespace RlClone::Demo

#endif
