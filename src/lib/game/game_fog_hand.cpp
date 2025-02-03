#include "game_fog_hand.hpp"

#include "../show.hpp"
#include "../var.hpp"

int game_fog_hand(Maze *maze, Show *show, bool toLeft) {
    refreshShow(show);
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    int direction = 0;
    int move = toLeft ? 1 : 3;
    int steps = 0;
    while (cell->getX() != maze->getEndX() || cell->getY() != maze->getEndY()) {
        int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            updateShowLive(show, maze, 1, &cell);
            return -1;
        }
        for (int i = 0; i < 3 && cell->getNeighbor(direction) == nullptr; i++) {
            direction = (direction + move) % 4;
        }
        Cell *neighbor = cell->getNeighbor(direction);
        direction = (direction - move) % 4;
        if (direction < 0) direction += 4;
        if (neighbor != nullptr) {
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            cell->setStatus(MAZE_STATUS_VISITED);
            Cell *showCell[2] = {cell, neighbor};
            updateShowLive(show, maze, 2, showCell);
            cell = neighbor;
        }
        steps++;
        if (steps % (maze->getWidth() * maze->getHeight()) == 0) {
            toLeft = !toLeft;
            move = toLeft ? 1 : 3;
        }
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    return steps;
}
