include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.1
)

FetchContent_MakeAvailable(unity)

file(GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS
  ./*.c
)

add_executable(test_matrix ${TESTS_SOURCES})

target_link_libraries(test_matrix PRIVATE matrix unity)

add_test(NAME TestMathLib COMMAND test_matrix)
