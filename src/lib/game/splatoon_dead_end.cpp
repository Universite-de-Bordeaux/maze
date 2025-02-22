#include "splatoon_dead_end.hpp"

#include "../show.hpp"
#include "../var.hpp"
#include "lib/splatoon.hpp"

int game_splatoon_dead_end(Maze *maze, Show *show) {
    const auto counts = new int *[maze->getWidth()];
    for (int i = 0; i < maze->getWidth(); i++) {
        counts[i] = new int[maze->getHeight()];
    }
    for (int i = 0; i < maze->getWidth(); i++)
        for (int j = 0; j < maze->getHeight(); j++) counts[i][j] = 0;
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() <= 1) {
        cell->setStatus(MAZE_STATUS_HOPELESS);
        cell->setAlreadyVisited(true);
    }
    counts[cell->getX()][cell->getY()]++;
    refreshShow(show);
    int steps = 0;
    while (cell->getX() != maze->getEndX() ||
           cell->getY() != maze->getEndY() &&
               steps <= pow(maze->getWidth() * maze->getHeight(), 2) &&
               steps >= 0) {
        const int nbNeighborsNotVisited =
            cell->getAbsoluteNumberOfNeighborsNotVisited();
        if (nbNeighborsNotVisited == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell);
            return -1;
        }
        const int minCount = MinCountCell(cell, counts, true);
        const int nbMinCount = nbMinCountCell(cell, counts, minCount, true);
        const auto cellsMinCount = new Cell *[nbMinCount];
        cellsMinCountCell(cell, counts, minCount, cellsMinCount, true);
        const int direction = maze->getRand()->get(0, nbMinCount - 1);
        Cell *neighbor = cellsMinCount[direction];
        delete[] cellsMinCount;
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
        counts[cell->getX()][cell->getY()]++;
        steps++;
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    refreshShow(show, 1, &cell);
    return steps > pow(maze->getWidth() * maze->getHeight(), 2) || steps < 0
               ? -1
               : steps;
}
