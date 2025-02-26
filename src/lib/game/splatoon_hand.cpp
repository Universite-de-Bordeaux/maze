#include "splatoon_hand.hpp"

#include "../checker/breadth_first.hpp"
#include "../show.hpp"
#include "../var.hpp"
#include "lib/limits.hpp"
#include "lib/splatoon.hpp"

int game_splatoon_hand(Maze *maze, Show *show, const bool left) {
    const auto counts = new int *[maze->getWidth()];
    for (int i = 0; i < maze->getWidth(); i++) {
        counts[i] = new int[maze->getHeight()];
    }
    for (int i = 0; i < maze->getWidth(); i++)
        for (int j = 0; j < maze->getHeight(); j++) counts[i][j] = 0;
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    counts[cell->getX()][cell->getY()]++;
    refreshShow(show);
    int direction = 0;
    const int move = left ? 1 : 3;
    int steps = 0;
    int count = 0;
    int loop = 0;
    bool tmpChangeDirection = false;
    while (whileCondition(maze, cell, steps)) {
        const int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell);
            for (int i = 0; i < maze->getWidth(); i++) {
                delete[] counts[i];
            }
            delete[] counts;
            return -1;
        }
        int minCount = MinCountCell(cell, counts);
        for (int i = 0;
             i < 3 && cell->getNeighbor(direction) == nullptr ||
             counts[cell->getNeighbor(direction)->getX()]
                   [cell->getNeighbor(direction)->getY()] != minCount;
             i++) {
            direction = (direction + move) % 4;
        }
        if (tmpChangeDirection) {
            int tmpDirection = (direction + 2) % 4;
            minCount = MinCountCell(cell, counts);
            for (int i = 0;
                 i < 3 && cell->getNeighbor(tmpDirection) == nullptr ||
                 counts[cell->getNeighbor(tmpDirection)->getX()]
                       [cell->getNeighbor(tmpDirection)->getY()] != minCount;
                 i++) {
                tmpDirection = (tmpDirection + move + 2) % 4;
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
        counts[cell->getX()][cell->getY()]++;
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
    for (int i = 0; i < maze->getWidth(); i++) {
        delete[] counts[i];
    }
    delete[] counts;
    return resultSteps(maze, steps);
}
