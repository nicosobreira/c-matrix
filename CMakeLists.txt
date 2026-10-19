cmake_minimum_required(VERSION 3.15)

project(lib-matrix
  LANGUAGES C
)

option(BUILD_EXAMPLES "Compile the examples" ON)
option(BUILD_TESTING "Compile the tests" ON)
option(BUILD_BENCHMARKS "Compile the benchmarks" OFF)

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
    -Wsign-conversion
    -Wfloat-conversion
    -Wnull-dereference
    -Wimplicit-fallthrough
    -Wuninitialized
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:RelWithDebInfo>:-O3;-g;-fno-omit-frame-pointer>
  >

  $<$<C_COMPILER_ID:MSVC>:
    /W4
    /WX
  >
)

# =============================================================================

add_subdirectory(lib)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

if(BUILD_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()
