#include "show.hpp"
#include <iostream>

void show(Maze *maze) {
    std::cout << "Show" << std::endl;
    std::cout << maze->getWidth() << " x " << maze->getHeight() << std::endl;
    for (int y = 0; y < maze->getHeight(); y++) {
        for (int x = 0; x < maze->getWidth(); x++) {
            Cell* cell = maze->getCell(x, y);
            if (cell->getWall(cell->NeighborsEnum::RIGHT)) {
                std::cout << x << " " << y << " " << "V" << std::endl;
            }
            if (cell->getWall(cell->NeighborsEnum::BOTTOM)) {
                std::cout << x << " " << y << " " << "H" << std::endl;
            }
        }
    }
}
