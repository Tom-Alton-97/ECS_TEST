//
// Created by alton on 03/10/2025.
//

#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "IntervalSystem.h"

class AISystem : public ECS_SYSTEM::IntervalSystem {
public:
    AISystem() : IntervalSystem(0.1f) {}  // Update every 100ms

    void intervalUpdate(ECS_SYSTEM::SystemContext& ctx, float elapsed) override {
        auto& ecs = ctx.ecs;

        // AI logic here - runs at 10 FPS
        for (size_t i = 0; i < 1000; ++i) {
            // Make AI decisions
        }
    }
};

#endif //AISYSTEM_H
