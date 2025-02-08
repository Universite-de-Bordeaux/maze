#include "fog.hpp"

#include "../show.hpp"
#include "../var.hpp"

int game_fog(Maze *maze, Show *show) {
    refreshShow(show);
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    int steps = 0;
    while (cell->getX() != maze->getEndX() || cell->getY() != maze->getEndY()) {
        int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell);
            return -1;
        }
        int direction = rand() % nbNeighbors;
        Cell **neighbors = new Cell *[nbNeighbors];
        cell->getAbsoluteNeighbors(neighbors);
        Cell *neighbor = neighbors[direction];
        delete[] neighbors;
        if (neighbor != nullptr) {
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            cell->setStatus(MAZE_STATUS_VISITED);
            Cell *showCell[2] = {cell, neighbor};
            refreshShow(show, 2, showCell);
            cell = neighbor;
        }
        steps++;
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    return steps;
}
