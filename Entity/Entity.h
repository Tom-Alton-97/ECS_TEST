//
// Created by alton on 02/10/2025.
//
#pragma once

#include <cstdint>

#include "../Utility/Utilities.h"

#ifndef ENTITY_H
#define ENTITY_H


namespace ECS_SYSTEM::ENTITY
{
    using EntityID = UTILITIES::EntityIdType;

    class Entity
    {
    public:
        explicit Entity(const EntityID id) : id(id) {};
        ~Entity() = default;
        inline void setActive() noexcept { active = true; }
        inline void setInactive() noexcept { active = false; }
        [[nodiscard]] inline EntityID getID() const noexcept { return id; }
        [[nodiscard]] inline bool getIsActive() const noexcept { return active; }
        [[nodiscard]] inline bool operator==(const EntityID inId) const noexcept { return id == inId; }
    protected:
    private:


        const EntityID id{};
        bool active{false};
    };

}


#endif //ENTITY_H
