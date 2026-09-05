cmake_minimum_required(VERSION 3.20)                                                                                                                                                                                                                                      )

project(GraceInfra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type" FORCE)
endif()

add_executable(main src/main.cpp src/matrix.cpp src/tensor.cpp)
05