#include "breadth_first.hpp"

#include "../queue.hpp"
#include "../show.hpp"
#include "../var.hpp"

struct positionHistory {
    int x;
    int y;
    positionHistory *parent;
};

void checker_breadth_first(const Maze *maze, const bool perfect, Show *show,
                           bool *isValid, bool *isPerfect) {
    Queue queue;
    bool imperfect = false;
    refreshShow(show);
    Cell *start = maze->getCell(0, 0);
    positionHistory startHistory = {0, 0, nullptr};
    queue.push(&startHistory);
    start->setStatus(MAZE_STATUS_VISITED);
    start->setAlreadyVisited(true);

    while (!queue.empty()) {
        auto *current = static_cast<positionHistory *>(queue.front());
        queue.pop();
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
            Cell *neighbor = cell->getNeighbor(i);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                auto *next = new positionHistory;
                next->x = neighbor->getX();
                next->y = neighbor->getY();
                next->parent = current;
                queue.push(next);
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
                if (isValid != nullptr) *isValid = false;
                return;
            }
        }
    }
    if (isValid != nullptr) *isValid = true;
    if (perfect) {
        if (!imperfect) {
            if (isPerfect != nullptr) *isPerfect = true;
        } else {
            if (isPerfect != nullptr) *isPerfect = false;
        }
    }
}
