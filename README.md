# Matrix Lib

A C library for matrix operations, built with [CMake](https://cmake.org/), tested with [Unity](https://www.throwtheswitch.org/unity).

## Highlights

- Core matrix/vector operations plus linear algebra: determinant, inverse, and triangular superior via Gaussian elimination
- Error handling via result codes generated with an X-macro (`MATRIX_ERRORS(X)`), avoiding duplication between the enum and its error strings
- CMake setup with presets (`debug`, `release`, `test`), an `INTERFACE` target for shared compiler flags, and `BUILD_INTERFACE`/`INSTALL_INTERFACE` include dirs for consumption as an installed package
- Reproducible dev environment via Nix (`flake.nix`)
- Dev tooling script (`tools/run.sh`) wrapping build, run, gdb, and perf workflows

## Features

- **Core**: `Add`, `Subtract`, `Product` (matrix-matrix and scalar), `Load`, `NewFrom`
- **Linear algebra**: `Determinant` (closed-form up to 3x3, cofactor expansion; Gaussian elimination for n x n), `Inverse`, `TriangularSuperior`, `Identity`
- **Vectors**: `DotProduct`, `Norm`, `Normalize`
- All operations return a `MatrixResult` code (`MATRIX_OK`, `MATRIX_ERR_DIMENSIONS`, `MATRIX_ERR_NOT_INVERTIBLE`, ...), no exceptions, no `exit()` inside the library itself

## Project Structure

```
lib
├── CMakeLists.txt             # Build the matrix lib
├── include                    # Public headers
│   └── matrix
│       ├── core.h             # Matrix data structure
│       ├── errors.h           # Errors enums
│       ├── linalg.h           # Linear algebra
│       ├── print.h
│       └── vector.h
└── src
    ├── core/
    ├── linalg/
    ├── print/
    └── vector/
```

## Building

Requires CMake >= 3.15 and a C11 compiler.

```bash
cmake --preset debug
cmake --build build
```

Available presets: `debug`, `release`, `test`. Examples and tests are built by default; disable with `-DBUILD_EXAMPLES=OFF` / `-DBUILD_TESTS=OFF`.

## Testing

```bash
ctest --test-dir build
```

Unity is fetched automatically through CMake's `FetchContent`. Tests cover dimension mismatches, allocation limits, and correctness of determinant/inverse/triangular reduction against known matrices.

## Dev Tools

`tools/run.sh` wraps common workflows:

```bash
./tools/run.sh build     # build in debug mode
./tools/run.sh run       # build and run
./tools/run.sh debug     # build and attach gdb (gdbserver + tmux split if inside tmux)
./tools/run.sh profile   # build in profile mode, record with perf, open in hotspot
```
