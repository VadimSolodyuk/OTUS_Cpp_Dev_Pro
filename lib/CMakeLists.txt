cmake_minimum_required(VERSION 3.5)

project(lib)

add_library(lib_for_ip_filter lib.cpp)

target_include_directories(lib_for_ip_filter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

set_target_properties(lib_for_ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
