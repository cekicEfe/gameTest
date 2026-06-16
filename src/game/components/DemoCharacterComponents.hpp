#ifndef DEMO_CHARACTER_COMPONENTS_HPP
#define DEMO_CHARACTER_COMPONENTS_HPP

// For uint32_t
#include <cstdint>

namespace RlClone {


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
