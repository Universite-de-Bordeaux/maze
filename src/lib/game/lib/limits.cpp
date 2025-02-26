#include "limits.hpp"

bool whileCondition(const Maze *maze, const Cell *cell, const int steps) {
    return (cell->getX() != maze->getEndX() ||
            cell->getY() != maze->getEndY()) &&
           steps <= pow(maze->getWidth() * maze->getHeight(), 2) && steps >= 0;
}

int resultSteps(const Maze *maze, const int steps) {
    return steps > pow(maze->getWidth() * maze->getHeight(), 2) || steps < 0
               ? -1
               : steps;
}