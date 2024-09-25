#include <cstdlib>
#include "lib/reader.hpp"

int main() {
    Maze maze = Maze();
    read("lib/instances/maze1.txt", &maze);
    // Cell cell1 = Cell(1, 2);
    // std::cout << cell1.getX() << std::endl;
    // cell1.setX(10);
    // std::cout << cell1.getX() << std::endl;

    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
