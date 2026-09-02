# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

Polaris is a teaching-oriented C++ deep-learning training and inference framework being built from scratch. The current chapter implements contiguous-memory matrix and tensor data structures, emphasizing C++ ownership, indexing, and performance concepts. The project is expected to grow toward CUDA-backed deep-learning functionality, but the current CMake target is CPU-only.

## Build and run

The project requires CMake 4.2 or newer and a C++ compiler.

```bash
cmake -S . -B build
cmake --build build
./build/main
```

CMake defaults `CMAKE_BUILD_TYPE` to `Release`; override it when needed:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

There is currently no test target, test framework, lint target, or formatter configuration. The executable in `src/main.cpp` is the only runnable validation program. To validate a focused change, update or temporarily extend that driver, rebuild, and run `./build/main`.

## Architecture

- `include/` contains public class declarations; `src/` contains their implementations. `CMakeLists.txt` builds one executable named `main` from `src/main.cpp`, `src/matrix.cpp`, and `src/tensor.cpp`.
- `Matrix` is the introductory two-dimensional data structure. It stores `rows_`, `cols_`, and row-major `std::vector<float>` data. Element access maps `(row, col)` to `row * cols_ + col`; addition and copy assignment require matching dimensions.
- `Tensor` generalizes the same idea to arbitrary dimensions. `shape_` stores dimension sizes, `strides_` stores the products of dimensions to the right, and `data_` points to one contiguous heap allocation of `float` values. Constructors compute the flattened length and strides; elementwise addition requires equal shapes.
- `Tensor` manually owns `data_` allocated with C allocation functions, so destructor, copy construction/assignment, move construction/assignment, and self-move/ownership behavior are central to changes in `tensor.cpp`. Keep allocation/deallocation conventions consistent.
- Tensor indexing currently exposes only a two-index `operator()`, intended as a bridge from `Matrix`; the general shape/stride representation is present for later multidimensional indexing. Matrix and tensor bounds/shape checks use `assert`.
- `src/main.cpp` is a simple performance comparison and smoke test: it creates large Matrix and Tensor instances, measures elementwise addition, and prints a sample matrix element. It is not a unit-test suite.

## Development notes

The README describes the repository as instructional material. Preserve the explanatory progression when changing the data structures: `Matrix` introduces row-major contiguous storage and operator overloads, while `Tensor` introduces arbitrary-rank shapes, strides, and explicit resource ownership. Read the relevant header and implementation together before changing an interface or ownership rule.
