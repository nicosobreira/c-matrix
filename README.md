# Matrix Lib

A C library for matrix operations, built with [CMake](https://cmake.org/), tested with [Unity](https://www.throwtheswitch.org/unity), and demonstrated through two applications: an ASCII 3D cube renderer and a Hill Cipher encoder/decoder.

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
lib/               core library
  include/matrix/  public headers (core, linalg, vector, print, errors)
  src/             implementation, split by domain (core, linalg, print, vector)
tests/             unit tests (Unity)
examples/
  cube/            ASCII wireframe cube, fixed-timestep render loop
  cipher/          Hill Cipher encoder/decoder
tools/
  run.sh           build / run / debug / profile helper
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

## Examples

### Cube

Renders a point rotating in 2D on an ASCII terminal buffer, driven by a fixed-timestep loop (`MS_PER_UPDATE` with lag accumulation). See [`examples/cube/README.md`](examples/cube/README.md) for the rotation matrices behind it.

```bash
./build/examples/cube/cube
```

### Cipher

Encrypts and decrypts 2-letter blocks with the Hill Cipher: encoding is a matrix product with a key matrix, decoding is a matrix product with its modular inverse. See [`examples/cipher/README.md`](examples/cipher/README.md).

```bash
./build/examples/cipher/cipher
```

## Dev Tools

`tools/run.sh` wraps common workflows:

```bash
./tools/run.sh build     # build in debug mode
./tools/run.sh run       # build and run
./tools/run.sh debug     # build and attach gdb (gdbserver + tmux split if inside tmux)
./tools/run.sh profile   # build in profile mode, record with perf, open in hotspot
```

## License

No license file yet — add one before treating this as reusable by others.
