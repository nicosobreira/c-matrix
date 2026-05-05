cmake_minimum_required(VERSION 3.15)

project(hill
  LANGUAGES C
)

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)

add_library(project_flags INTERFACE)

target_compile_features(project_flags INTERFACE c_std_11)

target_compile_definitions(project_flags INTERFACE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
)

target_compile_options(project_flags INTERFACE
    $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:
        # Warnings
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wformat=2
        -Werror
        # Flags específicas por Build Type
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:RelWithDebInfo>:-O3;-g;-fno-omit-frame-pointer> # O ponto e vírgula separa os argumentos no CMake
    >

    $<$<C_COMPILER_ID:MSVC>:
        /W4
        /WX # Equivalente ao -Werror do GCC (Remova se não quiser falhar o build no Windows por causa de warnings)
    >
)
