#include "game_fog.hpp"

#include "../show.hpp"
#include "../var.hpp"

bool game_fog(Maze *maze, Show *show) {
    updateShowLive(show, maze);
    refreshShow(show);
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    while (cell->getX() != maze->getEndX() || cell->getY() != maze->getEndY()){
        int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            updateShowLive(show, maze, 1, &cell);
            return false;
        }
        int direction = rand() % nbNeighbors;
        Cell **neighbors = new Cell *[nbNeighbors];
        cell->getAbsoluteNeighbors(neighbors);
        Cell *neighbor = neighbors[direction];
        delete[] neighbors;
        if (neighbor != nullptr) {
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            updateShowLive(show, maze, 1, &neighbor);
            cell->setStatus(MAZE_STATUS_VISITED);
            updateShowLive(show, maze, 1, &cell);
            cell = neighbor;
        }
        refreshShow(show);
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    return true;
}
