cmake_minimum_required(VERSION 3.5)

project(my_allocator) 

add_executable(my_vector_with_my_allocator ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(my_vector_with_my_allocator
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(my_vector_with_my_allocator
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(my_vector_with_my_allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(my_vector_with_my_allocator PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
endif()