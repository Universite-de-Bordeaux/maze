#include <iostream>
#include <fstream>
// #include "lib/reader.hpp"
#include "lib/maze.hpp"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "Usage: ./main <instance_file>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file) {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    Maze a = Maze();
    // Maze *maze = &a;
    // read(argv[1], maze);
    // Cell cell1 = Cell(1, 2);
    // std::cout << cell1.getX() << std::endl;
    // cell1.setX(10);
    // std::cout << cell1.getX() << std::endl;

    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
