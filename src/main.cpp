#include <iostream>
#include "lib/reader.hpp"
#include "lib/cell.hpp"

int main() {
    read("lib/instances/maze1.txt");

    Cell cell = Cell(1, 2);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
