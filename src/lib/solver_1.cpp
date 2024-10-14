#include "solver_1.hpp"
#include "var.hpp"
#include <iostream>

static bool solve(Maze *maze, Show *show, int x, int y, int direction, bool toLeft) {
    // std::cout << "x: " << x << " y: " << y << " direction: " << direction << " toLeft: " << toLeft << std::endl;
    if (maze -> getWidth() <= MAZE_REFRESH_SIZE && maze -> getHeight() <= MAZE_REFRESH_SIZE) {
        if (show != nullptr && show->isOpen()) {
            show->update();
        }
    }
    Cell *cell = maze->getCell(x, y);
    cell->setAlreadyVisited(true);
    cell->setStatus(MAZE_STATUS_CURRENT);
    if (x == maze->getEndX() && y == maze->getEndY()) {
        cell->setStatus(MAZE_STATUS_WAY_OUT);
        if (maze -> getWidth() > MAZE_REFRESH_SIZE || maze -> getHeight() > MAZE_REFRESH_SIZE) {
            if (show != nullptr && show->isOpen()) {
                show->update();
            }
        }
        return true;
    }
    if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
        cell->setStatus(MAZE_STATUS_HOPELESS);
        if (maze -> getWidth() > MAZE_REFRESH_SIZE || maze -> getHeight() > MAZE_REFRESH_SIZE) {
            if (show != nullptr && show->isOpen()) {
                show->update();
            }
        }
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
                bool result = solve(maze, show, neighbor->getX(), neighbor->getY(), (index + 2) % 4, toLeft);
                if (result) {
                    cell->setStatus(MAZE_STATUS_WAY_OUT);
                    return true;
                }
            }
        }
    }
    cell->setStatus(MAZE_STATUS_VISITED);
    return false;
}

bool solver_1(Maze *maze, Show *show, bool toLeft) {
    return solve(maze, show, maze->getStartX(), maze->getStartY(), 0, toLeft);
}
