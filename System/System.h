//
// Created by alton on 03/10/2025.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "ISystem.h"

namespace ECS_SYSTEM {
    template<typename Func>
    struct System final : ISystem {
        Func func;

        explicit System(Func&& f) : func(std::forward<Func>(f)) {}

        void update(SystemContext& ctx) override {
            func(ctx);
        }
    };
}


#endif //SYSTEM_H
