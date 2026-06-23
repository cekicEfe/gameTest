#ifndef DEMO_CHARACTER_CONTROLLER_SYSTEM_HPP
#define DEMO_CHARACTER_CONTROLLER_SYSTEM_HPP


#include <demo/systems/DemoCharacterCreatorSystem.hpp>


namespace RlClone::Demo {


class DemoCharacterControllerSystem {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    DemoCharacterControllerSystem(entt::registry& entity_registry_ref);
    ~DemoCharacterControllerSystem();
    void GetInput();
    void Update();
};


}; // namespace RlClone::Demo


#endif
