file(GLOB_RECURSE CIPHER_SOURCES CONFIGURE_DEPENDS
  ./src/*.c
)

add_executable(cipher ${CIPHER_SOURCES})

target_link_libraries(cipher PRIVATE matrix)
