//
// Created by alton on 03/10/2025.
//

#ifndef ICOMPONENTARRAY_H
#define ICOMPONENTARRAY_H

struct IComponentArray
{
    virtual ~IComponentArray() = default;
    virtual void remove(ECS_SYSTEM::UTILITIES::EntityIdType id) = 0;
};

#endif //ICOMPONENTARRAY_H
