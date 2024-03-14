cmake_minimum_required(VERSION 3.25)
project(01_living_world_Jan_Kiezun)

set(CMAKE_CXX_STANDARD 17)

#set(Boost_DETAILED_FAILURE_MSG ON)
#set(Boost_THREADAPI win32)
set(BOOST_ROOT "C:/Program Files/boost/boost_1_81_0")
#set(Boost_COMPILER "-vc")
#set(Boost_USE_STATIC_RUNTIME ON)
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_DEBUG ON)
#
#find_package(Boost 1.60.0)
#find_package(Boost REQUIRED COMPONENTS serialization)
#
#include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIR})
#
#if (NOT Boost_FOUND)
#    message(FATAL_ERROR "Could not find boost!")
#endif ()
#message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
#message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
#message(STATUS "Boost_VERSION: ${Boost_VERSION}")


include_directories(LivingWorld)

add_executable(01_living_world_Jan_Kiezun
        LivingWorld/organisms/Animal.cpp
        LivingWorld/organisms/Animal.h
        LivingWorld/LivingWorld.cpp
        LivingWorld/organisms/Organism.cpp
        LivingWorld/organisms/Organism.h
        LivingWorld/organisms/Plant.cpp
        LivingWorld/organisms/Plant.h
        LivingWorld/Position.cpp
        LivingWorld/Position.h
        LivingWorld/World.cpp
        LivingWorld/World.h
        )

#target_link_libraries(01_living_world-Jan-Kiezun Boost::serialization)