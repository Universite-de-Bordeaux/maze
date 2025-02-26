#include "tom_thumb.hpp"

#include "../show.hpp"
#include "../var.hpp"
#include "lib/limits.hpp"

int game_tom_thumb(Maze *maze, Show *show) {
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    cell->setAlreadyVisited(true);
    refreshShow(show);
    int steps = 0;
    while (whileCondition(maze, cell, steps)) {
        const int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        const int nbNeighborsNotVisited =
            cell->getAbsoluteNumberOfNeighborsNotVisited();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell);
            return -1;
        }
        Cell *neighbor = nullptr;
        if (nbNeighborsNotVisited >= 1) {
            const auto neighbors = new Cell *[nbNeighborsNotVisited];
            cell->getAbsoluteNeighborsNotVisited(neighbors);
            const int direction =
                maze->getRand()->get(0, nbNeighborsNotVisited - 1);
            neighbor = neighbors[direction];
            delete[] neighbors;
        } else {
            const auto neighbors = new Cell *[nbNeighbors];
            cell->getAbsoluteNeighbors(neighbors);
            const int direction = maze->getRand()->get(0, nbNeighbors - 1);
            neighbor = neighbors[direction];
            delete[] neighbors;
        }
        if (neighbor != nullptr) {
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            cell->setStatus(MAZE_STATUS_VISITED);
            Cell *showCell[2] = {cell, neighbor};
            refreshShow(show, 2, showCell);
            cell = neighbor;
        }
        cell->setAlreadyVisited(true);
        steps++;
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    refreshShow(show, 1, &cell);
    return resultSteps(maze, steps);
}
