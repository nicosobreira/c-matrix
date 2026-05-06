file(GLOB_RECURSE EXAMPLES_SOURCES CONFIGURE_DEPENDS
  ./*.c
)

add_executable(examples ${EXAMPLES_SOURCES})

target_link_libraries(examples PRIVATE matrix)
