# Radar Simulations

Technology Playground: C++
1. Templated Ring Buffer Implementation
2. Pulse Train Generator Implementation

## Features
1. Templated Ring Buffer: Templated for any type T. Real-Time push, pop, capacity, size and empty/full checks.
2. Pulse Train Generator: Creates samples for radar pulse trains with configurable pulse width (PW), pulse repetition interval (PRI), and amplitude.

## High-Level Design

1. Install prerequisites.
2. Clone the repository.
3. Run automated tests.

## Prerequisites

Required:
- `gcc` (validated with gcc `15.2.0`)
- `C++` (validated with C++ `23`)
- `googletest` (validated with googletest `1.17.0`)
- `cmake` (validated with cmake `4.3.2`)

Recommended:
- `git` latest stable

## Clone Repository

```bash
git clone https://github.com/vchandnani/radar-simulations.git
cd radar-simulations
mkdir build && cd build
cmake ..
make
./run_tests
```

## Project Structure (2 Levels)
```text
.
├── build
│   ├── _deps
│   ├── bin
│   ├── cmake_install.cmake
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── CTestTestfile.cmake
│   ├── lib
│   ├── Makefile
│   └── run_tests
├── CMakeLists.txt
├── helloworld
├── helloworld.cpp
├── helloworld.dSYM
│   └── Contents
├── main
├── main.cpp
├── pulse_train_generator_test.cpp
├── pulse_train_generator.cpp
├── pulse_train_generator.h
├── README.md
├── ring_buffer_test.cpp
├── ring_buffer.cpp
└── ring_buffer.h
```

## Debug Hard

1. Template Class Implementation

For template classes, the implementation must be in the header file, or explicitly instantiated in the .cpp file. Move the implementation into the header file or add ```#include "CLASS-NAME.cpp"``` at the end of the header file.

2. Broken Download Links or Archive Format Inconsistencies

```bash
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    # Use a specific branch, tag, or commit hash for reliability
    GIT_TAG        v1.17.0
)
```