# Create a function to build each benchmark

function(add_bench name)
  add_executable(${name} "src/${name}.c")
  target_link_libraries(${name} PRIVATE matrix project_flags)
endfunction()

add_bench(bench_operations)
