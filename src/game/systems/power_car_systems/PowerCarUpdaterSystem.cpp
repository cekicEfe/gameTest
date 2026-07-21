#include "PowerCarUpdaterSystem.hpp"


RlClone::PowerCarUpdaterSystem::PowerCarUpdaterSystem(entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::PowerCarUpdaterSystem::~PowerCarUpdaterSystem() {}


void RlClone::PowerCarUpdaterSystem::PrePhysicsUpdate() {
    auto view = this->entity_registry_ref.get()
                    .view<RlClone::PowerCarComponent, RlClone::BaseCarControllerComponent>();

    for (auto entity : view) {
        auto [power_car_component, car_controller_comp] =
            view.get<RlClone::PowerCarComponent, RlClone::BaseCarControllerComponent>(entity);

        JPH::WheeledVehicleController* controller = static_cast<JPH::WheeledVehicleController*>(
            power_car_component.vehicle_constraint->GetController());

        // Pass the input on to the constraint
        controller->SetDriverInput(
            car_controller_comp.forward,
            car_controller_comp.right,
            car_controller_comp.brake,
            car_controller_comp.hand_brake);
    }
}


void RlClone::PowerCarUpdaterSystem::Update() {}
