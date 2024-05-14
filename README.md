# Custom Memory Allocator

This project implements a custom memory allocator library in C. The library provides functions for memory allocation, deallocation, and management, similar to the standard `malloc`, `free`, `calloc`, and `realloc` functions.

## Files

The project consists of the following files:

- `MemoryAllocate.h`: Header file containing type definitions, external variable declarations, and function declarations for the memory allocator.
- `MemoryAllocate.c`: Source file containing the implementation of the memory allocator functions.

## Usage

To use the custom memory allocator library in your project, follow these steps:

1. Include the `MemoryAllocate.h` header file in your source files where you want to use the memory allocator functions.

2. Compile your source files along with the `MemoryAllocate.c` file to create an executable.

3. Link against the necessary libraries and include the appropriate compiler flags.

### Testing the Library

To test the library, you can use the provided Makefile. The Makefile allows you to compile and run a test file that uses the custom memory allocator functions.

To compile and run a test file, use the following command:

```bash
make <filename>
```

Replace `<filename>` with the name of your test file (without the `.c` extension).

For example, if you have a test file named `test.c`, you can compile and run it using:

```bash
make test
```

This will compile the `test.c` file along with the `MemoryAllocate.c` file and create an executable named `test`.

To clean up the generated object files and executables, use the following command:

```bash
make <filename> clean
```

Replace `<filename>` with the name of your test file (without the `.c` extension).

For example, to clean up the files generated for the `test.c` file, use:

```bash
make test clean
```

This will remove the generated object files and the `test` executable.

## Functions

The custom memory allocator library provides the following functions:

- `void *customMalloc(size_t size)`: Allocates a block of memory of the specified size and returns a pointer to the allocated memory.
- `void customFree(void *block)`: Frees a previously allocated block of memory.
- `void *customCalloc(size_t num, size_t size)`: Allocates a block of memory for an array of elements and initializes the memory to zero.
- `void *customRealloc(void *ptr, size_t newSize)`: Resizes a previously allocated block of memory to the specified new size.

These functions provide similar functionality to the standard `malloc`, `free`, `calloc`, and `realloc` functions, but with a custom implementation.

## Thread Safety

The custom memory allocator library is thread-safe. It uses a mutex lock (`lock_memory`) to ensure that multiple threads can safely access the memory allocation functions without conflicts.

## Dependencies

The library relies on the following headers and libraries:

- `<bits/pthreadtypes.h>`: Header file for POSIX thread types.
- `<stdio.h>`: Standard input/output library.
- `<string.h>`: String manipulation library.
- `<sys/mman.h>`: Memory management declarations.
- `<threads.h>`: C11 threads library.

Make sure you have these dependencies available on your system when compiling and linking the project.



Feel free to use, modify, and distribute the code as per the terms of the license.
