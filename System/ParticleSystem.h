//
// Created by alton on 03/10/2025.
//

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "FrameSkipSystem.h"

class ParticleSystem : public ECS_SYSTEM::FrameSkipSystem {
public:
    ParticleSystem() : FrameSkipSystem(2) {}  // Every other frame

    void frameUpdate(ECS_SYSTEM::SystemContext& ctx) override {
        auto& ecs = ctx.ecs;

        // Update particles (expensive, can skip frames)
        for (size_t i = 0; i < 1000; ++i) {
            // Update particle effects
        }
    }
};

#endif //PARTICLESYSTEM_H
