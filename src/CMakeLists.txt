file(GLOB_RECURSE MATRIX_SOURCES CONFIGURE_DEPENDS
  ./matrix/*.c
)

add_library(matrix ${MATRIX_SOURCES})

target_include_directories(matrix PUBLIC ./)

target_link_libraries(matrix PUBLIC project_flags)
