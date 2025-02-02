#include "checker_depthfirst.hpp"

#include <iostream>

#include "../cell.hpp"
#include "../maze.hpp"

/**
 * @brief Vérifie la validité du labyrinthe
 * @param maze Labyrinthe à vérifier
 * @param show Affichage du labyrinthe
 */
static void checkCell(Maze *maze, int x, int y, Show *show) {
    refreshShow(show);
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    cell->setStatus(MAZE_STATUS_VISITED);
    Cell *showCell[1] = {cell};
    // updateShowLive(show, maze, true);
    if (cell == nullptr) {
        return;
    }
    int numberOfNeighborsNotVisited =
        cell->getAbsoluteNumberOfNeighborsNotVisited();
    if (numberOfNeighborsNotVisited <= 0) {
        cell->setStatus(MAZE_STATUS_HOPELESS);
        Cell *showCell[1] = {cell};
        updateShowLive(show, maze, 1, showCell);
        // updateShowLive(show, maze, false);
        return;
    }
    updateShowLive(show, maze, 1, showCell);
    Cell *neighbors[numberOfNeighborsNotVisited];
    cell->getAbsoluteNeighborsNotVisited(neighbors);
    for (int i = 0; i < numberOfNeighborsNotVisited; i++) {
        Cell *neighbor = neighbors[i];
        if (neighbor != nullptr) {
            checkCell(maze, neighbor->getX(), neighbor->getY(), show);
        }
    }
    return;
}

/**
 * @brief Vérifie la validité du labyrinthe parfait
 * @param maze Labyrinthe à vérifier
 * @param show Affichage du labyrinthe
 */
static void checkCellPerfect(Maze *maze, int x, int y, int pastX, int pastY,
                             bool *unperfect, Show *show) {
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    cell->setStatus(MAZE_STATUS_VISITED);
    Cell *showCell[1] = {cell};
    refreshShow(show);
    updateShowLive(show, maze, 1, showCell);
    // updateShowLive(show, maze, true);
    if (cell->getAbsoluteNumberOfNeighbors() -
            cell->getAbsoluteNumberOfNeighborsNotVisited() >=
        2) {
        cell->setStatus(MAZE_STATUS_TOO_MANY_NEIGHBORS);
        Cell *showCell[1] = {cell};
        updateShowLive(show, maze, 1, showCell);
        *unperfect = true;
    }
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
        if (!(cell->getAbsoluteNumberOfNeighbors() -
                  cell->getAbsoluteNumberOfNeighborsNotVisited() >=
              2)) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            Cell *showCell[1] = {cell};
            updateShowLive(show, maze, 1, showCell);
        }
        // updateShowLive(show, maze, false);
        return;
    }
    int numberOfNeighborsNotVisited =
        cell->getAbsoluteNumberOfNeighborsNotVisited();
    Cell *neighbors[numberOfNeighborsNotVisited];
    cell->getAbsoluteNeighborsNotVisited(neighbors);
    for (int i = 0; i < numberOfNeighborsNotVisited; i++) {
        Cell *neighbor = neighbors[i];
        checkCellPerfect(maze, neighbor->getX(), neighbor->getY(), x, y,
                         unperfect, show);
    }
    return;
}

void checker_depthfirst(Maze *maze, bool perfect, Show *show) {
    bool unperfect = false;
    updateShowLive(show, maze);
    if (perfect) {
        checkCellPerfect(maze, 0, 0, 0, 0, &unperfect, show);
    } else {
        checkCell(maze, 0, 0, show);
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
