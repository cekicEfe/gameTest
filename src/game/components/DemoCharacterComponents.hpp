#ifndef DEMO_CHARACTER_COMPONENTS_HPP
#define DEMO_CHARACTER_COMPONENTS_HPP

// For uint32_t
#include <cstdint>

#include <string>


namespace RlClone {

  
inline const constexpr std::string cDemoCharacterModel =
    "resources/test_models/test_ship/ShapeAttacker.obj";

  
inline const constexpr std::string cDemoCharacterModelTexture =
    "resources/test_models/test_ship/SpaceShipHullUV.png";

  
struct DemoCharacterTag {};


struct DemoCharacterControlComponent {
    bool forward = false;
    bool backward = false;
    bool left = false;
    bool right = false;
    bool jump = false;
    std::uint32_t jump_cooldown = 0;
};


}; // namespace RlClone

#endif
