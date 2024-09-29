#include "show.hpp"
#include <iostream>
#include "var.hpp"

void show(Maze *maze) {
    for (int x = 0; x < maze->getWidth() * 2 + 2; x++) {
        std::cout << "_";
    }
    std::cout << std::endl;
    for (int y = 0; y < maze->getHeight() - 1; y++) {
        std::cout << "|";
        for (int x = 0; x < maze->getWidth(); x++) {
            Cell* cell = maze->getCell(x, y);
            if (cell->getWall(cell->NeighborsEnum::BOTTOM)) {
                std::cout << "_";
            } else {
                std::cout << " ";
            }
            if (cell->getWall(cell->NeighborsEnum::RIGHT)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "|";
    for (int x = 0; x < maze->getWidth() * 2; x++) {
        std::cout << "_";
    }
    std::cout << "|" << std::endl;
}
