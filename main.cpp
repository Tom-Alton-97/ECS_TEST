#include <cassert>
#include <iostream>

#include "ECS.h"

struct Transform {
    float x{0}, y{0};
};

struct Velocity {
    float dx{0}, dy{0};
};

void testEntityLifecycle() {
    auto& ecs = ECS_SYSTEM::ECS::getInstance();

    // Add entities
    ecs.addEntity();
    ecs.addEntity();
    constexpr auto id1 = 0;
    auto id2 = 1;
    assert(ecs.tryGetComponent<Transform>(id1) == nullptr);

    // Remove entity
    ecs.removeEntity(id1);
    assert(!ecs.tryGetComponent<Transform>(id1));
    std::cout << "Entity lifecycle tests passed.\n";
}

void testComponentAddRemove() {
    auto& ecs = ECS_SYSTEM::ECS::getInstance();
    constexpr auto id = 2;

    Transform t{10, 20};
    Velocity v{1, 2};

    ecs.addComponent<Transform>(id, t);
    ecs.addComponent<Velocity>(id, v);

    auto* tPtr = ecs.tryGetComponent<Transform>(id);
    auto* vPtr = ecs.tryGetComponent<Velocity>(id);

    assert(tPtr && tPtr->x == 10 && tPtr->y == 20);
    assert(vPtr && vPtr->dx == 1 && vPtr->dy == 2);

    ecs.removeComponent<Transform>(id);
    assert(ecs.tryGetComponent<Transform>(id) == nullptr);
    assert(ecs.tryGetComponent<Velocity>(id) != nullptr);

    std::cout << "Component add/remove tests passed.\n";
}

void testSystemUpdate() {
    auto& ecs = ECS_SYSTEM::ECS::getInstance();
    constexpr auto id = 3;

    ecs.addComponent<Transform>(id, Transform{0, 0});
    ecs.addComponent<Velocity>(id, Velocity{1, 1});

    ecs.addSystem([](ECS_SYSTEM::SystemContext& ctx) {
        auto& ecs = ctx.ecs;
        float dt = ctx.deltaTime;
        for (ECS_SYSTEM::ENTITY::EntityID id = 0; id < 10; ++id) {
            auto* t = ecs.tryGetComponent<Transform>(id);
            auto* v = ecs.tryGetComponent<Velocity>(id);
            if (t && v) {
                t->x += v->dx * dt;
                t->y += v->dy * dt;
            }
        }
    });

    ecs.updateSystems(0.5f);

    auto* tPtr = ecs.tryGetComponent<Transform>(id);
    assert(tPtr && tPtr->x == 0.5f && tPtr->y == 0.5f);

    std::cout << "System update tests passed.\n";
}

int main() {
    testEntityLifecycle();
    testComponentAddRemove();
    testSystemUpdate();
    std::cout << "All ECS tests passed.\n";
    return 0;
}