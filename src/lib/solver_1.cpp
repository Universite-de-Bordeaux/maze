#include "solver_1.hpp"
#include "show.hpp"
#include "var.hpp"

static bool solve(Maze *maze, Show *show, int x, int y, int direction, bool toLeft) {
    refreshShow(show, maze);
    // std::cout << "x: " << x << " y: " << y << " direction: " << direction << " toLeft: " << toLeft << std::endl;
    // updateShowLive(show, maze, true);
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    cell->setStatus(MAZE_STATUS_CURRENT);
    // updateShowLive(show, maze, 1, &cell);
    if (x == maze->getEndX() && y == maze->getEndY()) {
        cell->setStatus(MAZE_STATUS_WAY_OUT);
        updateShowLive(show, maze, 1, &cell);
        // updateShowLive(show, maze, false);
        return true;
    }
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
        cell->setStatus(MAZE_STATUS_HOPELESS);
        updateShowLive(show, maze, 1, &cell);
        // updateShowLive(show, maze, false);
        return false;
    }
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
        // std::cout << "index: " << index << " direction: " << direction << " i: " << i << std::endl;
        if (cell->isNeighbor(index)) {
            Cell *neighbor = cell->getNeighbor(index);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                updateShowLive(show, maze, 1, &cell);
                bool result = solve(maze, show, neighbor->getX(), neighbor->getY(), (index + 2) % 4, toLeft);
                updateShowLive(show, maze, 1, &neighbor);
                if (result) {
                    cell->setStatus(MAZE_STATUS_WAY_OUT);
                    // updateShowLive(show, maze, 1, &cell);
                    return true;
                }
            }
        }
    }
    cell->setStatus(MAZE_STATUS_VISITED);
    updateShowLive(show, maze, 1, &cell);
    return false;
}

bool solver_1(Maze *maze, Show *show, bool toLeft) {
    updateShowLive(show, maze);
    return solve(maze, show, maze->getStartX(), maze->getStartY(), 0, toLeft);
}
