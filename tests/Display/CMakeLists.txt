cmake_minimum_required(VERSION 3.10)

set(TARGET testsConsoleDisplay)

project(${TARGET})

find_package(GTest REQUIRED)

file(GLOB TARGET_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${TARGET} ${TARGET_SRC}) 
target_include_directories(${TARGET}
PRIVATE
    ${CMAKE_SOURCE_DIR}/include    
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(${TARGET}
PRIVATE
    libGraphicElement
    ${GTEST_BOTH_LIBRARIES}
)

set_target_properties(${TARGET}
PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${TARGET} PRIVATE
        /W4
    )
else ()
    target_compile_options(${TARGET} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()