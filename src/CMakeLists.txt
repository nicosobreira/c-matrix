file(GLOB_RECURSE MATRIX_SOURCES CONFIGURE_DEPENDS
  ./*.c
)

add_library(matrix ${MATRIX_SOURCES})

target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(matrix PRIVATE project_flags)
