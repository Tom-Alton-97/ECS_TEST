//
// Created by alton on 03/10/2025.
//

#ifndef FRAMESKIPSYSTEM_H
#define FRAMESKIPSYSTEM_H

#include "ISystem.h"
#include "SystemContext.h"

namespace ECS_SYSTEM {

    class FrameSkipSystem : public ISystem {
    protected:
        uint64_t skipFrames;

    public:
        explicit FrameSkipSystem(uint64_t skip)
            : skipFrames(skip) {}

        void update(SystemContext& ctx) final {
            if (ctx.frameCount % skipFrames == 0) {
                frameUpdate(ctx);
            }
        }

        virtual void frameUpdate(SystemContext& ctx) = 0;
    };

}

#endif //FRAMESKIPSYSTEM_H
