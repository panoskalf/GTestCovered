# GTestCovered

*C++ Project Template with Testing and Coverage*

![C++](https://img.shields.io/badge/language-C%2B%2B14-blue.svg) ![CMake](https://img.shields.io/badge/build-CMake-informational) ![GitHub License](https://img.shields.io/github/license/panoskalf/GTestCovered) ![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey) ![Coverage](https://img.shields.io/badge/coverage-ready-green)

This project serves as a simple template for C++ applications, integrating CMake, Google Test, and code coverage tools. It includes pre-configured `.vscode/` settings for seamless integration with Visual Studio Code.

## Project Structure
```
.
├── .vscode                 # VS Code configuration
├── build                   # Build output (generated)
├── include                 # Header files
├── src                     # Source files
├── tests                   # Unit tests
└── CMakeLists.txt          # Main CMake configuration
```

## Prerequisites
- **Compiler**: GCC (for coverage support) or any C++14-compatible compiler.
- **CMake**: Version 3.20 or later.
- **gcovr**: For generating coverage reports (optional).
- **VS Code Extensions**:
  - CMake Tools
  - Coverage Gutters

## Build Targets
First step for any target:
- **Command**:
  ```bash
  cmake -S . -B build
  ```
### 1. **Main Application**
- **Command**:
  ```bash
  cmake --build build --target my_cpp_project
  ```
- **Output**: `build/bin/my_cpp_project`

### 2. **Unit Tests**
- **Command**:
  ```bash
  cmake --build build --target test_my_library
  ```
- **Output**: `build/bin/test_my_library`
- **Run Tests**:
  ```bash
  ./ctest
  ```
  or
  ```bash
  ./build/bin/test_my_library
  ```

### 3. **Coverage Reports**
Only available if gcovr is installed.
- **Command**:
  ```bash
  cmake --build build --target coverage_tests
  ```
- **Output**:
  - `build/coverage_tests/coverage_tests.html` (HTML report for tests)
  - `build/coverage_tests/lcov.info` (LCOV file for Coverage Gutters)
- **Command**
  ```bash
  cmake --build build --target coverage_main
  ```
- **Output**
  - `build/coverage_main/coverage_main.html` (HTML report for main)
  - `build/coverage_main/lcov.info` (LCOV file for Coverage Gutters)


## VS Code Configuration
The `.vscode/` folder is included for consistent development:
- **CMake Tools**: Automatically configures and builds the project.
- **Testing Integration**: Run and debug tests directly from the Testing tab.
- **Coverage Gutters**: Highlights covered and uncovered lines using `lcov.info`.

## Notes
- Coverage reports are optional and only generated if `gcovr` is installed.
- `lcov.info` files are optional and only generated if your version of gcovr supports --lcov argument
- The project is pre-configured to work seamlessly on both Windows (MinGW) and Linux (Ninja or Unix Makefiles).