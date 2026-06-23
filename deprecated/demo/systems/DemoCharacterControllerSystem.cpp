#include "DemoCharacterControllerSystem.hpp"


RlClone::Demo::DemoCharacterControllerSystem::DemoCharacterControllerSystem(
    entt::registry& entity_registry_ref)
    : entity_registry_ref(entity_registry_ref) {}


RlClone::Demo::DemoCharacterControllerSystem::~DemoCharacterControllerSystem() {}


void RlClone::Demo::DemoCharacterControllerSystem::GetInput() {
    auto view =
        this->entity_registry_ref.get().view<RlClone::Demo::DemoCharacterControlComponent>();

    bool left = IsKeyDown(KEY_H) || IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_L) || IsKeyDown(KEY_RIGHT);
    bool forward = IsKeyDown(KEY_J) || IsKeyDown(KEY_UP);
    bool backward = IsKeyDown(KEY_K) || IsKeyDown(KEY_DOWN);
    bool up = IsKeyDown(KEY_N);
    bool down = IsKeyDown(KEY_M);    

    for (auto entity : view) {
        auto& input = view.get<RlClone::Demo::DemoCharacterControlComponent>(entity);

        input.left = left;
        input.right = right;
        input.forward = forward;
        input.backward = backward;
        input.up = up;
        input.down = down;
    }
}


void RlClone::Demo::DemoCharacterControllerSystem::Update() {
    if (auto* physics_backend_ptr = this->entity_registry_ref.get()
                                        .ctx()
                                        .find<RlClone::PhysicsBackend::GamePhysicsBackend>()) {
        auto view = this->entity_registry_ref.get()
                        .view<
                            RlClone::TransformComponent,
                            RlClone::PhysicsComponent,
                            RlClone::Demo::DemoCharacterControlComponent,
                            RlClone::KinematicTag>();

        for (auto entity : view) {
            auto& physics_component = view.get<RlClone::PhysicsComponent>(entity);
            auto& body_interface = physics_backend_ptr->GetPhysicsSystem().GetBodyInterface();

            if (body_interface.IsAdded(physics_component.body_id)) {
                auto& transform_component = view.get<RlClone::TransformComponent>(entity);
                auto& control_component =
                    view.get<RlClone::Demo::DemoCharacterControlComponent>(entity);

                if (control_component.forward)
                    transform_component.position.SetZ(transform_component.position.GetZ() - 0.1f);

                if (control_component.backward)
                    transform_component.position.SetZ(transform_component.position.GetZ() + 0.1f);

                if (control_component.right)
                    transform_component.position.SetX(transform_component.position.GetX() + 0.1f);

                if (control_component.left)
                    transform_component.position.SetX(transform_component.position.GetX() - 0.1f);

                if (control_component.up)
                    transform_component.position.SetY(transform_component.position.GetY() + 0.1f);

                if (control_component.down)
                    transform_component.position.SetY(transform_component.position.GetY() - 0.1f);
            }
        }
    }
    else {
        std::runtime_error("[[[FATAL Could not get physics backend]]]");
    }
}
