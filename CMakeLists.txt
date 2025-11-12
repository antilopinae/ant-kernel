cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ant-cmake")

include(CCache OPTIONAL)
include(NoInSourceBuilds OPTIONAL)

project(ant-kernel VERSION 1.0.0 LANGUAGES CXX C)

include(PlatformDetection REQUIRED)
include(CopyKernelHeaders REQUIRED)

add_subdirectory(c)
add_subdirectory(cpp)