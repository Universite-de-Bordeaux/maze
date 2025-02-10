#include "depth_first.hpp"

#include "../show.hpp"
#include "../stack.hpp"
#include "../var.hpp"

struct positionHistory {
    int x;
    int y;
    int direction;
    positionHistory *parent;
};

bool solver_depth_first(const Maze *maze, Show *show, const bool left) {
    Stack stack;
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }
    refreshShow(show);
    positionHistory startHistory = {maze->getStartX(), maze->getStartY(), 0,
                                    nullptr};
    stack.push(&startHistory);
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    maze->getStartCell()->setAlreadyVisited(true);

    while (!stack.empty()) {
        auto *current = static_cast<positionHistory *>(stack.top());
        stack.pop();
        const int x = current->x;
        const int y = current->y;
        Cell *cell = maze->getCell(x, y);
        refreshShow(show, 1, &cell, false);

        int count = 0;
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
                next->direction = (index + 2) % 4;
                next->parent = current;
                stack.push(next);
                neighbor->setStatus(MAZE_STATUS_VISITED);
                neighbor->setAlreadyVisited(true);
                if (neighbor->getX() == maze->getEndX() &&
                    neighbor->getY() == maze->getEndY()) {
                    neighbor->setStatus(MAZE_STATUS_WAY_OUT);
                    refreshShow(show, 1, &neighbor, true);

                    const auto *currentPath = next;
                    while (currentPath != nullptr) {
                        Cell *cellTop =
                            maze->getCell(currentPath->x, currentPath->y);
                        if (cellTop != nullptr) {
                            cellTop->setStatus(MAZE_STATUS_WAY_OUT);
                            refreshShow(show, 1, &cellTop, false);
                        }
                        currentPath = currentPath->parent;
                    }
                    refreshShow(show);
                    return true;
                }
            } else {
                count++;
            }
        }
        if (count == 4) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell, true);
        }
    }
    refreshShow(show);
    return false;
}