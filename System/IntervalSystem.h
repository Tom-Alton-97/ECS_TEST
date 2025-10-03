//
// Created by alton on 03/10/2025.
//

#ifndef INTERVALSYSTEM_H
#define INTERVALSYSTEM_H

#include "ISystem.h"
#include "SystemContext.h"

namespace ECS_SYSTEM {

    class IntervalSystem : public ISystem {
    protected:
        float updateInterval;
        float timeSinceUpdate{0.0f};

    public:
        explicit IntervalSystem(float interval)
            : updateInterval(interval) {}

        void update(SystemContext& ctx) final {
            timeSinceUpdate += ctx.deltaTime;

            if (timeSinceUpdate >= updateInterval) {
                intervalUpdate(ctx, timeSinceUpdate);
                timeSinceUpdate = 0.0f;
            }
        }

        virtual void intervalUpdate(SystemContext& ctx, float elapsed) = 0;
    };

}

#endif //INTERVALSYSTEM_H
