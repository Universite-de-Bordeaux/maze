#include "depth_first.hpp"

#include <iostream>

#include "../cell.hpp"
#include "../maze.hpp"
#include "../stack.hpp"

struct positionHistory {
    int x;
    int y;
    int direction;
    positionHistory *parent;
};

void checker_depth_first(const Maze *maze, const bool perfect, const bool left,
                         Show *show) {
    Stack stack;
    bool imperfect = false;
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return;
    }
    refreshShow(show);
    positionHistory startHistory = {0, 0, 0, nullptr};
    stack.push(&startHistory);
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    maze->getStartCell()->setAlreadyVisited(true);

    while (!stack.empty()) {
        auto *current = static_cast<positionHistory *>(stack.top());
        stack.pop();
        const int x = current->x;
        const int y = current->y;
        Cell *cell = maze->getCell(x, y);
        if (perfect && cell->getAbsoluteNumberOfNeighbors() -
                               cell->getAbsoluteNumberOfNeighborsNotVisited() >=
                           2) {
            cell->setStatus(MAZE_STATUS_TOO_MANY_NEIGHBORS);
            imperfect = true;
        }
        if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
            if (cell->getAbsoluteNumberOfNeighbors() -
                    cell->getAbsoluteNumberOfNeighborsNotVisited() <
                2) {
                cell->setStatus(MAZE_STATUS_HOPELESS);
            }
            refreshShow(show, 1, &cell, true);
        } else {
            refreshShow(show, 1, &cell, false);
        }
        for (int i = 0; i < 4; i++) {
            int index;
            if (left) {
                index = (current->direction - i) % 4;
            } else {
                index = (current->direction + i) % 4;
            }
            if (index < 0) {
                index += 4;
            }
            Cell *neighbor = cell->getNeighbor(index);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                auto *next = new positionHistory;
                next->x = neighbor->getX();
                next->y = neighbor->getY();
                next->parent = current;
                stack.push(next);
                neighbor->setStatus(MAZE_STATUS_VISITED);
                neighbor->setAlreadyVisited(true);
            }
        }
    }
    refreshShow(show);
    for (int i = 0; i < maze->getWidth(); i++) {
        for (int j = 0; j < maze->getHeight(); j++) {
            const Cell *cell = maze->getCell(i, j);
            if (!cell->isAlreadyVisited()) {
                std::cout << "Maze is not valid!" << std::endl;
                return;
            }
        }
    }
    std::cout << "Maze is valid!" << std::endl;
    if (perfect) {
        if (!imperfect) {
            std::cout << "Maze is perfect!" << std::endl;
        } else {
            std::cout << "Maze is not perfect!" << std::endl;
        }
    }
}
