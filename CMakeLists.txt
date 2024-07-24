cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(TARGET Editor)

project(${TARGET} VERSION ${PROJECT_VESRION}) 

add_subdirectory(source/lib)

add_executable(${TARGET} ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)
target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${TARGET}
PRIVATE
    libEditor
    libView
    libController
)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${TARGET} PRIVATE /W4)
else ()
    target_compile_options(${TARGET} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

include(CTest)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)

    add_test(testsGraphicPrimitive
        ${CMAKE_BINARY_DIR}/tests/GraphicElement/testsGraphicPrimitive
    ) 
    add_test(testsConsoleDisplay
        ${CMAKE_BINARY_DIR}/tests/Display/testsConsoleDisplay
    )
    add_test(testsEditor
        ${CMAKE_BINARY_DIR}/tests/Editor/testsEditor
    )
    add_test(testsDocument
        ${CMAKE_BINARY_DIR}/tests/Document/testsDocument
    ) 
    add_test(testsView
        ${CMAKE_BINARY_DIR}/tests/View/testsView
    ) 
    add_test(testsController
        ${CMAKE_BINARY_DIR}/tests/Controller/testsController
    )
    add_test(testsHandlersEditor
        ${CMAKE_BINARY_DIR}/tests/handlersEditor/testsHandlersEditor
    ) 
endif()

install(TARGETS ${TARGET} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)