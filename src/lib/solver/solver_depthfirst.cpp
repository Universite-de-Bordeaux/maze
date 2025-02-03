#include "solver_depthfirst.hpp"

#include "../show.hpp"
#include "../var.hpp"

static bool solve(Maze *maze, Show *show, int x, int y, int direction,
                  bool toLeft) {
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    cell->setStatus(MAZE_STATUS_CURRENT);
    if (x == maze->getEndX() && y == maze->getEndY()) {
        cell->setStatus(MAZE_STATUS_WAY_OUT);
        updateShowLive(show, maze, 1, &cell);
        return true;
    }
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
        cell->setStatus(MAZE_STATUS_HOPELESS);
        updateShowLive(show, maze, 1, &cell);
        return false;
    }
    updateShowLive(show, maze, 1, &cell);
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
            Cell *neighbor = cell->getNeighbor(index);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                if (solve(maze, show, neighbor->getX(),
                                    neighbor->getY(), (index + 2) % 4, toLeft)) {
                    cell->setStatus(MAZE_STATUS_WAY_OUT);
                    updateShowLive(show, maze, 1, &cell);
                    return true;
                }
            }
        }
    }
    cell->setStatus(MAZE_STATUS_VISITED);
    updateShowLive(show, maze, 1, &cell);
    return false;
}

bool solver_depthfirst(Maze *maze, Show *show, bool toLeft) {
    refreshShow(show);
    return solve(maze, show, maze->getStartX(), maze->getStartY(), 0, toLeft);
}
