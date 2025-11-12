cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

include(AddCKernelModule REQUIRED)

set(HELLO_1_MODULE_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/hello-1.c
)

add_c_kernel_module(ant-hello-1-module ${CMAKE_CURRENT_SOURCE_DIR}
        ${HELLO_1_MODULE_SRC}
)
