#include "depth_first.hpp"

#include <iostream>

#include "../cell.hpp"
#include "../maze.hpp"

/**
 * @brief Vérifie la validité du labyrinthe
 * @param maze Labyrinthe à vérifier
 * @param x Position x de la cellule
 * @param y Position y de la cellule
 * @param show Affichage du labyrinthe
 * @param direction Direction de la cellule
 * @param left Vérifie si le labyrinthe est parfait en partant à gauche
 */
static void checkCell(Maze *maze, int x, int y, Show *show,  // NOLINT
                      const int direction, const bool left) {
    Cell *cell = maze->getCell(x, y);
    if (cell == nullptr) {
        return;
    }
    cell->setAlreadyVisited(true);
    cell->setStatus(MAZE_STATUS_VISITED);
    const int numberOfNeighborsNotVisited =
        cell->getAbsoluteNumberOfNeighborsNotVisited();
    if (numberOfNeighborsNotVisited <= 0) {
        cell->setStatus(MAZE_STATUS_HOPELESS);
        refreshShow(show, 1, &cell);
        return;
    }
    refreshShow(show, 1, &cell);
    for (int i = 0; i < 4; i++) {
        int index;
        if (left) {
            index = (direction + i) % 4;
        } else {
            index = (direction - i) % 4;
        }
        if (index < 0) {
            index += 4;
        }
        if (cell->isNeighbor(index)) {
            const Cell *neighbor = cell->getNeighbor(index);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                checkCell(maze, neighbor->getX(), neighbor->getY(), show,
                          (index + 2) % 4, left);
            }
        }
    }
}

/**
 * @brief Vérifie la validité du labyrinthe parfait
 * @param maze Labyrinthe à vérifier
 * @param x Position x de la cellule
 * @param y Position y de la cellule
 * @param imperfect Labyrinthe parfait
 * @param show Affichage du labyrinthe
 * @param direction Direction de la cellule
 * @param left Vérifie si le labyrinthe est parfait en partant à gauche
 */
static void checkCellPerfect(Maze *maze, const int x, const int y,  // NOLINT
                             bool *imperfect,
                             Show *show, const int direction, const bool left) {
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    cell->setStatus(MAZE_STATUS_VISITED);
    if (cell->getAbsoluteNumberOfNeighbors() -
            cell->getAbsoluteNumberOfNeighborsNotVisited() >=
        2) {
        cell->setStatus(MAZE_STATUS_TOO_MANY_NEIGHBORS);
        *imperfect = true;
    }
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
        if (cell->getAbsoluteNumberOfNeighbors() -
                cell->getAbsoluteNumberOfNeighborsNotVisited() <
            2) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
        }
        refreshShow(show, 1, &cell);
        return;
    }
    refreshShow(show, 1, &cell);
    for (int i = 0; i < 4; i++) {
        int index;
        if (left) {
            index = (direction + i) % 4;
        } else {
            index = (direction - i) % 4;
        }
        if (index < 0) {
            index += 4;
        }
        if (cell->isNeighbor(index)) {
            const Cell *neighbor = cell->getNeighbor(index);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                checkCellPerfect(maze, neighbor->getX(), neighbor->getY(), imperfect, show,
                          (index + 2) % 4, left);
            }
        }
    }
}

void checker_depth_first(Maze *maze, const bool perfect, const bool left,
                         Show *show) {
    bool imperfect = false;
    if (perfect) {
        checkCellPerfect(maze, 0, 0, &imperfect, show, 0, left);
    } else {
        checkCell(maze, 0, 0, show, 0, left);
    }
    for (int i = 0; i < maze->getWidth(); i++) {
        for (int j = 0; j < maze->getHeight(); j++) {
            const Cell *cell = maze->getCell(i, j);
            if (!cell->isAlreadyVisited()) {
                std::cout << "Maze is not valid!" << std::endl;
                return;
            }
        }
    }
    std::cout << "Maze is valid!" << std::endl;
    if (perfect) {
        if (!imperfect) {
            std::cout << "Maze is perfect!" << std::endl;
        } else {
            std::cout << "Maze is not perfect!" << std::endl;
        }
    }
}
