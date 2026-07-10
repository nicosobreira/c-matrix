include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.1
)

FetchContent_MakeAvailable(unity)

function(add_unit_test name)
  add_executable(${name} "src/${name}.c")
  target_link_libraries(${name} PRIVATE matrix unity project_flags)
  add_test(NAME ${name} COMMAND ${name})
endfunction()

add_unit_test(test_operations)
add_unit_test(test_identity)

add_unit_test(test_triangular)
add_unit_test(test_inverse)
add_unit_test(test_determinant)
