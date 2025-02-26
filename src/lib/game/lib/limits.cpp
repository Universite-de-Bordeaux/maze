#include "limits.hpp"

bool whileCondition(Maze *maze, Cell*cell, int steps) {
    return (cell->getX() != maze->getEndX() || cell->getY() != maze->getEndY()) &&
        steps <= pow(maze->getWidth() * maze->getHeight(), 2) && steps >= 0;
}

int resultSteps(Maze *maze, int steps) {
    return steps > pow(maze->getWidth() * maze->getHeight(), 2) || steps < 0
               ? -1
               : steps;
}