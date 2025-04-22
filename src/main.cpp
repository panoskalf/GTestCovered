#include <iostream>
#include "my_library.h"

int main()
{
    myFunction();
    std::cout << "Hello, World!" << std::endl;
    // Example usage of a function from my_library
    int result = add(5, 3); // Assuming add is a function declared in my_library.h
    std::cout << "The result of adding 5 and 3 is: " << result << std::endl;
    return 0;
}