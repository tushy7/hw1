#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite

int main(int argc, char* argv[])
{
    ULListStr list;

    // Test: Adding elements with push_back
    list.push_back("apple");
    list.push_back("banana");
    list.push_back("cherry");
    list.push_back("date");

    // Test: Access elements with getValAtLoc
    std::cout << "Element at 0: " << *list.getValAtLoc(0) << std::endl; // Expected: apple
    std::cout << "Element at 1: " << *list.getValAtLoc(1) << std::endl; // Expected: banana
    std::cout << "Element at 2: " << *list.getValAtLoc(2) << std::endl; // Expected: cherry
    std::cout << "Element at 3: " << *list.getValAtLoc(3) << std::endl; // Expected: date

    


}
