#include "tom_thumb_hand.hpp"

#include "../show.hpp"
#include "../var.hpp"

int game_tom_thumb_hand(const Maze *maze, Show *show, const bool left) {
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    cell->setAlreadyVisited(true);
    refreshShow(show);
    int direction = 0;
    const int move = left ? 1 : 3;
    int steps = 0;
    int count = 0;
    int loop = 0;
    bool tmpChangeDirection = false;
    while (
        (cell->getX() != maze->getEndX() || cell->getY() != maze->getEndY()) &&
        steps <= pow(maze->getWidth() * maze->getHeight(), 3) && steps >= 0) {
        const int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell);
            return -1;
        }
        int nbNeighborsNotVisited =
            cell->getAbsoluteNumberOfNeighborsNotVisited();
        if (nbNeighborsNotVisited >= 1) {
            for (int i = 0;
                 i < 3 && (cell->getNeighbor(direction) == nullptr ||
                           cell->getNeighbor(direction)->isAlreadyVisited());
                 i++) {
                direction = (direction + move) % 4;
            }
        } else {
            for (int i = 0; i < 3 && cell->getNeighbor(direction) == nullptr;
                 i++) {
                direction = (direction + move) % 4;
            }
        }
        if (tmpChangeDirection) {
            int tmpDirection = (direction + 2) % 4;
            nbNeighborsNotVisited =
                cell->getAbsoluteNumberOfNeighborsNotVisited();
            if (nbNeighborsNotVisited >= 1) {
                for (int i = 0;
                     i < 3 &&
                     (cell->getNeighbor(tmpDirection) == nullptr ||
                      cell->getNeighbor(tmpDirection)->isAlreadyVisited());
                     i++) {
                    tmpDirection = (tmpDirection + move + 2) % 4;
                }
            } else {
                for (int i = 0;
                     i < 3 && cell->getNeighbor(tmpDirection) == nullptr; i++) {
                    tmpDirection = (tmpDirection + move + 2) % 4;
                }
            }
            if (tmpDirection != direction) {
                direction = tmpDirection;
                tmpChangeDirection = false;
            }
        }
        Cell *neighbor = cell->getNeighbor(direction);
        direction = (direction - move) % 4;
        if (direction < 0) direction += 4;
        if (neighbor != nullptr) {
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            cell->setStatus(MAZE_STATUS_VISITED);
            Cell *showCell[2] = {cell, neighbor};
            refreshShow(show, 2, showCell);
            cell = neighbor;
        }
        cell->setAlreadyVisited(true);
        steps++;
        count++;
        if (count >= maze->getWidth() * maze->getHeight() * 2 + loop) {
            tmpChangeDirection = true;
            count = 0;
            loop++;
        }
    }
    if (cell->getX() == maze->getEndX() && cell->getY() == maze->getEndY()) {
        cell->setStatus(MAZE_STATUS_WAY_OUT);
    } else {
        cell->setStatus(MAZE_STATUS_HOPELESS);
    }
    return steps > pow(maze->getWidth() * maze->getHeight(), 3) || steps < 0
               ? -1
               : steps;
}
