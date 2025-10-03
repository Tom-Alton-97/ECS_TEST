//
// Created by alton on 03/10/2025.
//

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ISystem.h"

class RenderSystem : public ECS_SYSTEM::ISystem {
public:
    void update(ECS_SYSTEM::SystemContext& ctx) override {
        auto& ecs = ctx.ecs;

        // Render every frame
        for (size_t i = 0; i < 1000; ++i) {
            auto* pos = ecs.tryGetComponent<Transform>(i);
            if (pos) {
                // Draw sprite at pos->x, pos->y
            }
        }
    }
};

#endif //RENDERSYSTEM_H
