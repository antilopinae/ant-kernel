cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

include(AddCppKernelModule REQUIRED)

# add C++ Kernel Library
add_subdirectory(akl)

set(CPP_KERNEL_MODULE_SRC
        # C++ Kernel Library
        ${AKL_KERNEL_MODULE_SRC}

        # Sources of module
        ${CMAKE_CURRENT_SOURCE_DIR}/module.c
        ${CMAKE_CURRENT_SOURCE_DIR}/kern_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/logger.c
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp_support.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp_module.cpp
)

# Func to add target and then build C++ module
add_cpp_kernel_module(
        MODULE_NAME cpp_kernel
        MODULE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}
        MODULE_SRC ${CPP_KERNEL_MODULE_SRC}
        # Also copying directories
        MODULE_INCLUDE_DIRS
        include/
        akl/
)
