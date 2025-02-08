#include "depth_first.hpp"

#include "../show.hpp"
#include "../var.hpp"

static bool solve(Maze *maze, Show *show, const int x, const int y,  // NOLINT
                  const int direction, const bool toLeft) {
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    cell->setStatus(MAZE_STATUS_CURRENT);
    if (x == maze->getEndX() && y == maze->getEndY()) {
        cell->setStatus(MAZE_STATUS_WAY_OUT);
        refreshShow(show, 1, &cell);
        return true;
    }
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
        cell->setStatus(MAZE_STATUS_HOPELESS);
        refreshShow(show, 1, &cell);
        return false;
    }
    refreshShow(show, 1, &cell);
    for (int i = 0; i < 4; i++) {
        int index;
        if (toLeft) {
            index = (direction + i) % 4;
        } else {
            index = (direction - i) % 4;
        }
        if (index < 0) {
            index += 4;
        }
        if (cell->isNeighbor(index)) {
            const Cell *neighbor = cell->getNeighbor(index);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                if (solve(maze, show, neighbor->getX(), neighbor->getY(),
                          (index + 2) % 4, toLeft)) {
                    cell->setStatus(MAZE_STATUS_WAY_OUT);
                    refreshShow(show, 1, &cell);
                    return true;
                }
            }
        }
    }
    cell->setStatus(MAZE_STATUS_VISITED);
    refreshShow(show, 1, &cell);
    return false;
}

bool solver_depth_first(Maze *maze, Show *show, const bool left) {
    refreshShow(show);
    return solve(maze, show, maze->getStartX(), maze->getStartY(), 0, left);
}
