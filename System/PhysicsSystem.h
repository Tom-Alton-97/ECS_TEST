//
// Created by alton on 03/10/2025.
//

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H
#include "FixedTimeStepSystem.h"
//TODO remove
struct Transform {
    float x, y;
};

struct Velocity {
    float vx, vy;
};

class PhysicsSystem : public ECS_SYSTEM::FixedTimestepSystem {
public:
    PhysicsSystem() : FixedTimestepSystem(1.0f / 60.0f) {}

    void fixedUpdate(ECS_SYSTEM::SystemContext& ctx) override {
        auto& ecs = ctx.ecs;

        // Update all entities with velocity
        for (size_t i = 0; i < 1000; ++i) {
            auto* vel = ecs.tryGetComponent<Velocity>(i);
            auto* pos = ecs.tryGetComponent<Transform>(i);

            if (vel && pos) {
                pos->x += vel->vx * fixedDeltaTime;
                pos->y += vel->vy * fixedDeltaTime;
            }
        }
    }
};

#endif //PHYSICSSYSTEM_H
