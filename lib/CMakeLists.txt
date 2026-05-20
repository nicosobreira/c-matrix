file(GLOB_RECURSE MATRIX_SOURCES CONFIGURE_DEPENDS
  ./src/*.c
)

add_library(matrix ${MATRIX_SOURCES})

target_include_directories(matrix
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(matrix PUBLIC project_flags)
