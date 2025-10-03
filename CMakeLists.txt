cmake_minimum_required(VERSION 4.0)
project(ECS_TEST)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG -mfma -mavx2" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g" CACHE STRING "" FORCE)

add_executable(ECS_TEST main.cpp
        ECS.cpp
        ECS.h
        Component/Position.h
        Entity/Entity.h
        Utility/Utilities.h
        Component/IComponentArray.h
        Component/ComponentArray.h
        System/ISystem.h
        System/System.h
        System/SystemContext.h
        System/FixedTimeStepSystem.h
        System/IntervalSystem.h
        System/FrameSkipSystem.h
        System/PhysicsSystem.h
        System/AISystem.h
        System/RenderSystem.h
        System/ParticleSystem.h)
