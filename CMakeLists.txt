cmake_minimum_required(VERSION 3.20)
project(GTestCovered)

# google test requires at least cpp 14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

include(FetchContent)
# the name of .zip file is the commit hash
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Set a global output directory for all executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find gcovr once and make it available to all subdirectories
find_program(GCOVR_EXECUTABLE gcovr)
if(GCOVR_EXECUTABLE)
  message(STATUS "gcovr found: ${GCOVR_EXECUTABLE}")
else()
  message(WARNING "gcovr not found. Coverage reports will not be generated.")
endif()

# Test if gcovr supports --lcov
if(GCOVR_EXECUTABLE)
  execute_process(
    COMMAND ${GCOVR_EXECUTABLE} --help
    OUTPUT_VARIABLE GCOVR_HELP_OUTPUT
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(GCOVR_HELP_OUTPUT MATCHES "--lcov")
    set(GCOVR_SUPPORTS_LCOV TRUE CACHE BOOL "Whether gcovr supports --lcov")
    message(STATUS "gcovr supports --lcov. LCOV output will be generated.")
  else()
    set(GCOVR_SUPPORTS_LCOV FALSE CACHE BOOL "Whether gcovr supports --lcov")
    message(WARNING "gcovr does not support --lcov. LCOV output will not be generated.")
  endif()
endif()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)