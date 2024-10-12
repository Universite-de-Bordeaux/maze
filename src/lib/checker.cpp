#include "checker.hpp"
#include "maze.hpp"
#include <iostream>

static void checkCell(Maze *maze, int x, int y) {
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
        return;
    }
    int numberOfNeighborsNotVisited = cell->getAbsoluteNumberOfNeighborsNotVisited();
    Cell *neighbors[numberOfNeighborsNotVisited];
    cell->getAbsoluteNeighborsNotVisited(neighbors);
    for (int i = 0; i < numberOfNeighborsNotVisited; i++) {
        Cell *neighbor = neighbors[i];
        checkCell(maze, neighbor->getX(), neighbor->getY());
    }
    return;
}

void checker(Maze *maze) {
    std::cout << "Checking maze..." << std::endl;
    checkCell(maze, 0, 0);
    for (int i = 0; i < maze->getWidth(); i++) {
        for (int j = 0; j < maze->getHeight(); j++) {
            Cell *cell = maze->getCell(i, j);
            if (!cell->isAlreadyVisited()) {
                std::cout << "Maze is not valid!" << std::endl;
                return;
            }
        }
    }
}
