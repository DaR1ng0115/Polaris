cmake_minimum_required(VERSION 4.2.0)

project(Polaris)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type" FORCE)
endif()

add_executable(main src/main.cpp src/matrix.cpp src/tensor.cpp)
