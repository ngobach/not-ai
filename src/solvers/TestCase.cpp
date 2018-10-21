#include "TestCase.h"
#include <iostream>

bool solver::TestCase::isValid() {
    return !this->origin.empty() && !this->basePath.empty();
}

void solver::TestCase::dump() {
    std::cout << "Test case data\n";
    std::cout << "> Base path: " << this->basePath << std::endl;
    std::cout << "> Origin file: " << this->origin << std::endl;
    for (const auto &part : this->parts) {
        std::cout << "> Part: " << part << std::endl;
    }
}