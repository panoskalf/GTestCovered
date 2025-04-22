#include <gtest/gtest.h>
#include "my_library.h"

// Test case for a function in my_library
TEST(MyLibraryTest, FunctionNameTest)
{
    // Arrange
    int expected = 42;

    // Act
    int result = add(40, 2);
    // int result = 42;

    // Assert
    EXPECT_EQ(expected, result);
}

// Additional test cases can be added here
