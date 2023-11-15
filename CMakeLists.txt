cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(my_vector_with_my_allocator VERSION ${PROJECT_VESRION}) 

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

install(TARGETS my_vector_with_my_allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
