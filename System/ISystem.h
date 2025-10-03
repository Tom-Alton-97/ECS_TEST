//
// Created by alton on 03/10/2025.
//

#ifndef ISYSTEM_H
#define ISYSTEM_H

namespace ECS_SYSTEM {
    struct SystemContext;  // forward declaration

    struct ISystem {
        virtual ~ISystem() = default;
        virtual void update(SystemContext& ctx) = 0;
    };
}

#endif //ISYSTEM_H
