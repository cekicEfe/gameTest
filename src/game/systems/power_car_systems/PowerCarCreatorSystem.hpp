#ifndef POWER_CAR_CREATOR_SYSTEM_HPP
#define POWER_CAR_CREATOR_SYSTEM_HPP

#include "entity_builders/PowerCarBuilder.hpp"

#include <entt/entt.hpp>
#include <functional>

namespace RlClone {

class PowerCarCreatorSystem final {
private:
    std::reference_wrapper<entt::registry> entity_registry_ref;
public:
    PowerCarCreatorSystem(entt::registry& entity_registry_ref);

    ~PowerCarCreatorSystem();

    void Create();
};


}; // namespace RlClone


#endif
