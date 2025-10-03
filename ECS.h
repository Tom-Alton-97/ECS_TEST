//
// Created by alton on 02/10/2025.
//

#ifndef ECS_H
#define ECS_H

#include <cassert>
#include <functional>
#include <memory>
#include <optional>
#include <typeindex>
#include <unordered_set>
#include <vector>

#include "Entity/Entity.h"
#include "Utility/Utilities.h"
#include "Component/ComponentArray.h"
#include "System/ISystem.h"
#include "System/System.h"
#include "System/SystemContext.h"

namespace ECS_SYSTEM {
// TODO need to use PIMPL

    // template<typename T>
    // struct ComponentArray : IComponentArray {
    //     std::vector<std::optional<T>> components;
    //
    //     ComponentArray() : components(UTILITIES::MAX_COMPONENT_SIZE) {}
    // };


class ECS { //may need to use 64bit so we never have to check for overflow
    public:
        ~ECS() = default;

        inline static ECS& getInstance() noexcept
        {
            static ECS instance;
            return instance;
        }

        void removeEntity(ENTITY::EntityID id) noexcept;
        void addEntity() noexcept;

    template<typename T>
        void addComponent(ENTITY::EntityID id, T component) {
        const auto typeId = std::type_index(typeid(T));
        auto it = components.find(typeId);

        ComponentArray<T>* array = nullptr;
        if (it == components.end()) {
            auto arrayPtr = std::make_unique<ComponentArray<T>>();
            array = arrayPtr.get();
            components[typeId] = std::move(arrayPtr);
        } else {
            array = static_cast<ComponentArray<T>*>(it->second.get());
        }

        array->insert(id, std::move(component));
    }

    template<typename T>
    T* tryGetComponent(ENTITY::EntityID id) noexcept {
        const auto typeId = std::type_index(typeid(T));
        const auto it = components.find(typeId);
        if (it == components.end()) return nullptr;

        auto* array = static_cast<ComponentArray<T>*>(it->second.get());
        return array->get(id); // use ComponentArray::get
    }

    template<typename T>
    void removeComponent(ENTITY::EntityID id) noexcept {
        getOrCreateComponentArray<T>()->remove(id);
    }

    template<typename Func>
    void addSystem(Func&& systemFunc) {
        systems.push_back(std::make_unique<System<Func>>(std::forward<Func>(systemFunc)));
    }

    void addSystem(std::unique_ptr<ISystem> system) {
        systems.push_back(std::move(system));
    }

    template<typename SystemType, typename... Args>
    void addSystem(Args&&... args) {
        systems.push_back(std::make_unique<SystemType>(std::forward<Args>(args)...));
    }

    void updateSystems(float deltaTime = 1.0f) {
        totalTime += deltaTime;
        frameCount++;

        SystemContext ctx(*this, deltaTime, totalTime, frameCount);

        for (const auto& system : systems) {
            system->update(ctx);
        }
    }

    protected:
    private:

        explicit ECS();

        // We aren't returning for performance
        void internalGetNextEntityID() noexcept;

        // ECS Containers
        std::vector<ENTITY::Entity> entities;
        std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> components;
        std::vector<std::unique_ptr<ISystem>> systems;

        // Reusable Entities
        bool hasReusableEntities{false};
        ENTITY::EntityID nextEntityID{0};
        ENTITY::EntityID reusableEntitiesCount{0};
        std::vector<ENTITY::EntityID> reusableEntityIDs{0};

        float totalTime{0.0f};
        uint64_t frameCount{0};

    template<typename T>
    ComponentArray<T>* getOrCreateComponentArray() {
        const auto typeId = std::type_index(typeid(T));
        const auto it = components.find(typeId);

        if (it == components.end()) {
            auto arrayPtr = std::make_unique<ComponentArray<T>>();
            ComponentArray<T>* rawPtr = arrayPtr.get();
            components[typeId] = std::move(arrayPtr);
            return rawPtr;
        }

        return static_cast<ComponentArray<T>*>(it->second.get());
    }
    };
} // ECS

#endif //ECS_H