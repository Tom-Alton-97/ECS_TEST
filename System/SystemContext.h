//
// Created by alton on 03/10/2025.
//

#ifndef SYSTEMCONTEXT_H
#define SYSTEMCONTEXT_H

#include <cstdint>

namespace ECS_SYSTEM {
    class ECS;  // forward declaration

    struct SystemContext {
        ECS& ecs;
        float deltaTime;
        float totalTime;
        uint64_t frameCount;

        // Constructor
        SystemContext(ECS& e, float dt, float total, uint64_t frame)
            : ecs(e), deltaTime(dt), totalTime(total), frameCount(frame) {}
    };
}

#endif //SYSTEMCONTEXT_H
