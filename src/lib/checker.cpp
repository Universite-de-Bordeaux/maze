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

static void checkCellPerfect(Maze *maze, int x, int y, int pastX, int pastY, bool *unperfect) {
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    if (cell->getAbsoluteNumberOfNeighbors() - cell->getAbsoluteNumberOfNeighborsNotVisited() >= 2) {
        *unperfect = true;
    }
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
        return;
    }
    int numberOfNeighborsNotVisited = cell->getAbsoluteNumberOfNeighborsNotVisited();
    Cell *neighbors[numberOfNeighborsNotVisited];
    cell->getAbsoluteNeighborsNotVisited(neighbors);
    for (int i = 0; i < numberOfNeighborsNotVisited; i++) {
        Cell *neighbor = neighbors[i];
        checkCellPerfect(maze, neighbor->getX(), neighbor->getY(), x, y, unperfect);
    }
    return;
}

void checker(Maze *maze, bool perfect) {
    std::cout << "Checking maze..." << std::endl;
    bool unperfect = false;
    if (perfect) {
        checkCellPerfect(maze, 0, 0, 0, 0, &unperfect);
    } else {
        checkCell(maze, 0, 0);
    }
    for (int i = 0; i < maze->getWidth(); i++) {
        for (int j = 0; j < maze->getHeight(); j++) {
            Cell *cell = maze->getCell(i, j);
            if (!cell->isAlreadyVisited()) {
                std::cout << "Maze is not valid!" << std::endl;
                return;
            }
        }
    }
    std::cout << "Maze is valid!" << std::endl;
    if (perfect) {
        if (!unperfect) {
            std::cout << "Maze is perfect!" << std::endl;
        } else {
            std::cout << "Maze is not perfect!" << std::endl;
        }
    }
    return;
}
