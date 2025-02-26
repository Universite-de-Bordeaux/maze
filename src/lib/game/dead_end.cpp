#include "dead_end.hpp"

#include "../show.hpp"
#include "../var.hpp"
#include "lib/limits.hpp"

int game_dead_end(Maze *maze, Show *show) {
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() <= 1) {
        cell->setStatus(MAZE_STATUS_HOPELESS);
        cell->setAlreadyVisited(true);
    }
    refreshShow(show);
    int steps = 0;
    while (whileCondition(maze, cell, steps)) {
        const int nbNeighborsNotVisited =
            cell->getAbsoluteNumberOfNeighborsNotVisited();
        if (nbNeighborsNotVisited == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell);
            return -1;
        }
        const auto neighbors = new Cell *[nbNeighborsNotVisited];
        cell->getAbsoluteNeighborsNotVisited(neighbors);
        const int direction =
            maze->getRand()->get(0, nbNeighborsNotVisited - 1);
        Cell *neighbor = neighbors[direction];
        delete[] neighbors;
        if (neighbor != nullptr) {
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            if (cell->getStatus() != MAZE_STATUS_HOPELESS)
                cell->setStatus(MAZE_STATUS_VISITED);
            Cell *showCell[2] = {cell, neighbor};
            refreshShow(show, 2, showCell);
            cell = neighbor;
        }
        if (cell->getAbsoluteNumberOfNeighborsNotVisited() <= 1) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            cell->setAlreadyVisited(true);
            refreshShow(show, 1, &cell);
        }
        steps++;
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    refreshShow(show, 1, &cell);
    return resultSteps(maze, steps);
}
