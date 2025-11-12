cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

include(AddCppKernelModule REQUIRED)

set(CPP_KERNEL_MODULE_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/module.c
        ${CMAKE_CURRENT_SOURCE_DIR}/kern_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/logger.c
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp_support.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp_module.cpp
)

add_cpp_kernel_module(cpp_kernel ${CMAKE_CURRENT_SOURCE_DIR}
        ${CPP_KERNEL_MODULE_SRC}
)
