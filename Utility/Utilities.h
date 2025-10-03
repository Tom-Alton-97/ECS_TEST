//
// Created by alton on 02/10/2025.
//

#ifndef UTILITIES_H
#define UTILITIES_H
#include <cstdint>

namespace ECS_SYSTEM::UTILITIES
{
    using EntityIdType = std::uint_fast32_t;
    using ComponentSize = std::uint_fast8_t;
    using SystemSize = std::uint_fast8_t;
    constexpr EntityIdType MAX_ENTITY_ID_TYPE = 100000;
    constexpr ComponentSize MAX_COMPONENT_SIZE = UINT_FAST8_MAX;
    constexpr SystemSize MAX_SYSTEM_SIZE = UINT_FAST8_MAX;
}

#endif //UTILITIES_H
