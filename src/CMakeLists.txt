# Add the library
add_library(my_library my_library.cpp)

target_include_directories(my_library PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Add the executable
add_executable(my_cpp_project main.cpp my_library.cpp)

# Link the library to the executable
target_link_libraries(my_cpp_project PRIVATE my_library)

# Add coverage flags for my_cpp_project if using GCC
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(my_library PRIVATE --coverage)
  target_link_options(my_library PRIVATE --coverage)
  target_compile_options(my_cpp_project PRIVATE --coverage)
  target_link_options(my_cpp_project PRIVATE --coverage)
endif()

# Add a custom target for generating the coverage report for the main project
if(GCOVR_EXECUTABLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_custom_target(coverage_main
    # Create the coverage directory
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage_main
    # Reset coverage data
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --delete
    # Run the main project executable
    COMMAND ${CMAKE_BINARY_DIR}/bin/my_cpp_project
    # Generate both HTML and LCOV reports in the coverage_main directory
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --object-directory ${CMAKE_BINARY_DIR}/src
    --html --html-details -o ${CMAKE_BINARY_DIR}/coverage_main/coverage_main.html
    --lcov=${CMAKE_BINARY_DIR}/coverage_main/lcov.info # LCOV output file for coverage gutters extension
    --filter ${CMAKE_SOURCE_DIR}/src/.*\.cpp
    DEPENDS my_cpp_project
  )
endif()