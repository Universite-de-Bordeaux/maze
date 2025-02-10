#include "breadth_first.hpp"

#include "../queue.hpp"
#include "../show.hpp"
#include "../var.hpp"

struct positionHistory {
    int x;
    int y;
    positionHistory *parent;
};

bool solver_breadth_first(const Maze *maze, Show *show) {
    Queue queue;
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }
    refreshShow(show);
    positionHistory startHistory = {maze->getStartX(), maze->getStartY(),
                                    nullptr};
    queue.push(&startHistory);
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    maze->getStartCell()->setAlreadyVisited(true);
    while (!queue.empty()) {
        auto *current = static_cast<positionHistory *>(queue.front());
        queue.pop();
        const int x = current->x;
        const int y = current->y;
        Cell *cell = maze->getCell(x, y);
        refreshShow(show, 1, &cell, false);

        int count = 0;
        for (int i = 0; i < 4; i++) {
            Cell *neighbor = cell->getNeighbor(i);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                auto *next = new positionHistory;
                next->x = neighbor->getX();
                next->y = neighbor->getY();
                next->parent = current;
                queue.push(next);
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
