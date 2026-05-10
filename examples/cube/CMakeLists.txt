file(GLOB_RECURSE CUBE_SOURCES CONFIGURE_DEPENDS
  ./*.c
)

add_executable(cube ${CUBE_SOURCES})

target_link_libraries(cube PRIVATE matrix)
