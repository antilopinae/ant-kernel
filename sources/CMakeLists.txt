cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

include(AddCppKernelModule REQUIRED)

# add C++ Kernel Library
add_subdirectory(akl)

include_directories(akl)
include_directories(include)

set(CPP_KERNEL_MODULE_SRC
        # C++ Kernel Library
        ${AKL_KERNEL_MODULE_SRC}

        # sources of module
        ${CMAKE_CURRENT_SOURCE_DIR}/module.c
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp_module.cpp
)

# Func to add target and then build C++ module
add_cpp_kernel_module(
        # target 'cpp_kernel' to build kernel module
        MODULE_NAME cpp_kernel

        # dir where module src are
        MODULE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}

        # list with src of module (.c and .cpp)
        MODULE_SRC ${CPP_KERNEL_MODULE_SRC}

        # list with include directories of module
        MODULE_INCLUDE_DIRS
        include/
        ${AKL_INCLUDE_DIRS}
)

# target 'cpp_kernel_userspace' to build userspace kernel module
add_library(cpp_kernel_userspace STATIC
        cpp_module.cpp
)

# link with C++ Kernel Library
target_link_libraries(cpp_kernel_userspace
        PRIVATE akl
)
