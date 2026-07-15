#include "PowerCarBuilder.hpp"


RlClone::PowerCarBuilder::PowerCarBuilder(PowerCarTemplate power_car_template) {}


RlClone::PowerCarBuilder::~PowerCarBuilder() {}


entt::entity RlClone::PowerCarBuilder::CreateCar(entt::registry& entity_registry) {}


RlClone::PowerCarDirector::PowerCarDirector(PowerCarBuilder&& power_car_builder) {}


RlClone::PowerCarDirector::~PowerCarDirector() {}


entt::entity RlClone::PowerCarDirector::Construct(entt::registry& entity_registry) {}
