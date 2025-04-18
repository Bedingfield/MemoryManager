# Matrix Library with Custom Memory Manager

## Overview
This C++ project implements a matrix library integrated with a custom memory manager, showcasing my skills in systems programming, memory management, and modular design. The program includes:

- **Custom Memory Manager**: A first-fit memory allocator that manages a memory pool using a linked list of free blocks, with support for allocation, deallocation, and coalescing to reduce fragmentation.
- **Matrix Library**: A dynamic matrix implementation supporting operations like matrix creation, element access, display, and multiplication, all using the custom memory manager for allocation.
- **Test Harness**: A comprehensive test suite that exercises the memory manager and matrix library, verifying functionality and memory management correctness.

This project was developed as a college assignment in February 2020 to deepen my understanding of memory management and data structures in C++.

## Features
- **Memory Management**:
  - Allocates memory using a first-fit strategy with `mmap` for a Unix-based memory pool.
  - Supports deallocation with coalescing to merge adjacent free blocks, reducing fragmentation.
  - Provides a `traverse_free_list` function to inspect the free list for debugging.
- **Matrix Operations**:
  - Creates matrices of arbitrary size with dynamic memory allocation.
  - Supports element access (set/get), matrix multiplication, and display of matrix contents.
  - Uses a 1D array to efficiently store 2D matrix elements.
- **Testing**:
  - Tests various scenarios, including small and large matrices, multiple allocations, and matrix multiplication.
  - Prints the free list after each operation to verify memory management correctness.

## Technical Details
- **Language**: C++11
- **Files**:
  - `mm.cpp`: Implements the memory manager with allocation, deallocation, and coalescing.
  - `matrix.cpp`: Defines the matrix structure and operations.
  - `main.cpp`: Test harness to demonstrate functionality.
- **Key Components**:
  - `mmfree_t` and `mmalloc_t` structs for managing free and allocated blocks.
  - `matrix` struct with dynamic element storage.
  - First-fit allocation strategy with coalescing to optimize memory usage.
- **Platform**: Developed for Unix-based systems (uses `mmap` with `MAP_ANON`).

## How to Run
1. **Prerequisites**: A Unix-based system with a C++ compiler (e.g., `g++`).
2. **Compilation**:
   ```bash
   g++ -std=c++11 main.cpp matrix.cpp mm.cpp -o matrix_test

www.linkedin.com/in/jonathan-bedingfield
