#include "INIParser.h"
#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
    try {
        INIParser parser{ "INIFile.ini" };
        auto value = parser.get_value<int>("Section1", "var1");
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    return EXIT_SUCCESS;
}