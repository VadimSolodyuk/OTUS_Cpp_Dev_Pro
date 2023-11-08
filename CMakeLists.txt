cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

find_package(GTest REQUIRED)

add_subdirectory(lib)

add_executable(ip_filter ${CMAKE_CURRENT_SOURCE_DIR}/src/ip_filter.cpp)
target_include_directories(ip_filter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ip_filter PRIVATE lib_for_ip_filter)

add_executable(test_ip_filter ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp)
target_include_directories(test_ip_filter
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include    
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(test_ip_filter
    lib_for_ip_filter
    ${GTEST_BOTH_LIBRARIES}
)

set_target_properties(ip_filter test_ip_filter  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(test_ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
    

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_ip_filter test_ip_filter)
