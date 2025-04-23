# Add the test executable
add_executable(test_my_library test_my_library.cpp)

# Link the test executable with gtest and the library
target_link_libraries(test_my_library PRIVATE GTest::gtest_main my_library)

# Add coverage flags if using GCC or Clang
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(test_my_library PRIVATE --coverage)
  target_link_options(test_my_library PRIVATE --coverage)
endif()

# Add the include directory
target_include_directories(test_my_library PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Discover tests
include(GoogleTest)
gtest_discover_tests(test_my_library)

# Add a custom target for generating the coverage report for the tests
if(GCOVR_EXECUTABLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_custom_target(coverage_tests
    # Create the coverage directory
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage_tests
    # Reset coverage data
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --delete
    # Run the test executable
    COMMAND ${CMAKE_BINARY_DIR}/bin/test_my_library
    # Generate both HTML and LCOV reports in a single gcovr call
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --object-directory ${CMAKE_BINARY_DIR}
    --html --html-details -o ${CMAKE_BINARY_DIR}/coverage_tests/coverage_tests.html
    # if LCOV is supported, output file for coverage gutters extension
    $<$<BOOL:${GCOVR_SUPPORTS_LCOV}>:--lcov=${CMAKE_BINARY_DIR}/coverage_tests/lcov.info>
    --filter ${CMAKE_SOURCE_DIR}/src/my_library.cpp --filter ${CMAKE_SOURCE_DIR}/tests/.*\.cpp
    DEPENDS test_my_library
  )
endif()
