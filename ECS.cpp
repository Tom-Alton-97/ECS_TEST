//
// Created by alton on 02/10/2025.
//

#include "ECS.h"

#include <iostream>
#include <ranges>

void ECS_SYSTEM::ECS::removeEntity(ENTITY::EntityID id) noexcept
{
    reusableEntityIDs[reusableEntitiesCount++] = id;
    entities[id].setInactive();
    hasReusableEntities = true;

    for (const auto& componentPtr : components | std::views::values)
    {
        componentPtr->remove(id);
    }
}

void ECS_SYSTEM::ECS::addEntity() noexcept
{
    try
    {
        internalGetNextEntityID();
        entities[nextEntityID].setActive();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Failed to add entity: " << e.what() << std::endl;
    }

}

void ECS_SYSTEM::ECS::internalGetNextEntityID() noexcept
{
    // Branchless method to get the nextEntityID or a reusable ID
    nextEntityID = hasReusableEntities * reusableEntityIDs[reusableEntitiesCount - (1 * (reusableEntitiesCount > 0))]
             + (!hasReusableEntities) * nextEntityID;

    // Decrement reusableEntitiesCount if we have any reusable entities
    reusableEntitiesCount -= hasReusableEntities;

    // hasReusableEntities is set by whether there is any available
    hasReusableEntities = reusableEntitiesCount > 0;

    // This is honestly witchcraft at this point enjoy future tom
    nextEntityID = std::min<ENTITY::EntityID>(
            static_cast<ENTITY::EntityID>(
                (hasReusableEntities * nextEntityID) + (!hasReusableEntities * entities.size())
            ),
            UTILITIES::MAX_ENTITY_ID_TYPE - 1
    );
}

ECS_SYSTEM::ECS::ECS(): entities()
{
    for (ENTITY::EntityID i = 0; i < UTILITIES::MAX_ENTITY_ID_TYPE; ++i)
    {
        entities.emplace_back(i); // actually constructs elements
    }

    reusableEntityIDs.resize(UTILITIES::MAX_ENTITY_ID_TYPE);

    //components.reserve(UTILITIES::MAX_COMPONENT_SIZE);
    systems.reserve(UTILITIES::MAX_SYSTEM_SIZE);
}