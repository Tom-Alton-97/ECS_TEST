//
// Created by alton on 03/10/2025.
//

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include <climits>
#include <vector>

#include "../Utility/Utilities.h"
#include "IComponentArray.h"

template<typename T>
struct ComponentArray final : IComponentArray {
    std::vector<T> packed;                    // dense array of components
    std::vector<ECS_SYSTEM::UTILITIES::EntityIdType> entities;   // entity IDs matching components
    std::vector<size_t> sparse;               // entity ID -> index in packed

    ComponentArray() : sparse(ECS_SYSTEM::UTILITIES::MAX_ENTITY_ID_TYPE, SIZE_MAX) {}

    void insert(ECS_SYSTEM::UTILITIES::EntityIdType id, T component) {
        size_t index = packed.size();
        packed.push_back(std::move(component));
        entities.push_back(id);
        sparse[id] = index;
    }

    T* get(ECS_SYSTEM::UTILITIES::EntityIdType id) {
        size_t index = sparse[id];
        if (index == SIZE_MAX) return nullptr;
        return &packed[index];
    }

    void remove(ECS_SYSTEM::UTILITIES::EntityIdType id) {
        size_t index = sparse[id];
        if (index == SIZE_MAX) return;

        // Swap with last element (constant time removal)
        size_t lastIndex = packed.size() - 1;
        if (index != lastIndex) {
            packed[index] = std::move(packed[lastIndex]);
            entities[index] = entities[lastIndex];
            sparse[entities[index]] = index;
        }

        packed.pop_back();
        entities.pop_back();
        sparse[id] = SIZE_MAX;
    }

    // Iterate over ALL components efficiently
    auto begin() { return packed.begin(); }
    auto end() { return packed.end(); }
};

#endif //COMPONENTARRAY_H
