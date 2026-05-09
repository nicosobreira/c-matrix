cmake_minimum_required(VERSION 3.15)

project(lib-matrix
  LANGUAGES C
)

option(BUILD_EXAMPLES "Compile the examples" ON)
option(BUILD_TESTS "Compile the tests" ON)

add_library(project_flags INTERFACE)

target_compile_features(project_flags INTERFACE c_std_11)

target_compile_definitions(project_flags INTERFACE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
)

target_compile_options(project_flags INTERFACE
    $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wformat=2
        -Werror
        $<$<CONFIG:RelWithDebInfo>:-O3;-g;-fno-omit-frame-pointer>
    >

    $<$<C_COMPILER_ID:MSVC>:
        /W4
        /WX
    >
)

# =============================================================================

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
