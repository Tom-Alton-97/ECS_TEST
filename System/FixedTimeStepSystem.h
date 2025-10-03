//
// Created by alton on 03/10/2025.
//

#ifndef FIXEDTIMESTEPSYSTEM_H
#define FIXEDTIMESTEPSYSTEM_H

#include "ISystem.h"
#include "SystemContext.h"

namespace ECS_SYSTEM {

    class FixedTimestepSystem : public ISystem {
    protected:
        float fixedDeltaTime;
        float accumulator{0.0f};

    public:
        explicit FixedTimestepSystem(float fixedDt = 1.0f / 60.0f)
            : fixedDeltaTime(fixedDt) {}

        void update(SystemContext& ctx) final {
            accumulator += ctx.deltaTime;

            while (accumulator >= fixedDeltaTime) {
                fixedUpdate(ctx);
                accumulator -= fixedDeltaTime;
            }
        }

        virtual void fixedUpdate(SystemContext& ctx) = 0;
    };

}

#endif //FIXEDTIMESTEPSYSTEM_H
