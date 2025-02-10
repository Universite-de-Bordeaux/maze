#include "breadth_first.hpp"

#include "../queue.hpp"
#include "../show.hpp"
#include "../stack.hpp"
#include "../var.hpp"

struct position {
    int x;
    int y;
};

struct positionHistory {
    int x;
    int y;
    int parent_x;
    int parent_y;
};

bool solver_breadth_first(const Maze *maze, Show *show) {
    Queue queue;
    Stack stack;
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }
    refreshShow(show);
    position start = {maze->getStartX(), maze->getStartY()};
    queue.push(&start);
    positionHistory startHistory = {maze->getStartX(), maze->getStartY(), -1,
                                    -1};
    stack.push(&startHistory);
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    maze->getStartCell()->setAlreadyVisited(true);
    while (!queue.empty()) {
        const auto *current = static_cast<position *>(queue.front());
        queue.pop();
        const int x = current->x;
        const int y = current->y;
        Cell *cell = maze->getCell(x, y);
        refreshShow(show, 1, &cell, false);
        int count = 0;
        for (int i = 0; i < 4; i++) {
            Cell *neighbor = cell->getNeighbor(i);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                auto *neighborPosition = new position;
                neighborPosition->x = neighbor->getX();
                neighborPosition->y = neighbor->getY();
                queue.push(neighborPosition);
                auto *neighborHistory = new positionHistory;
                neighborHistory->x = neighbor->getX();
                neighborHistory->y = neighbor->getY();
                neighborHistory->parent_x = x;
                neighborHistory->parent_y = y;
                stack.push(neighborHistory);
                neighbor->setStatus(MAZE_STATUS_VISITED);
                neighbor->setAlreadyVisited(true);
                if (neighbor->getX() == maze->getEndX() &&
                    neighbor->getY() == maze->getEndY()) {
                    neighbor->setStatus(MAZE_STATUS_WAY_OUT);
                    refreshShow(show, 1, &neighbor, true);
                    while (!stack.empty()) {
                        const auto *currentCell =
                            static_cast<positionHistory *>(stack.top());
                        const auto *cellTop =
                            static_cast<positionHistory *>(stack.top());
                        while (!stack.empty() &&
                               (cellTop->x != currentCell->parent_x ||
                                cellTop->y != currentCell->parent_y)) {
                            stack.pop();
                            cellTop =
                                static_cast<positionHistory *>(stack.top());
                        }
                        if (stack.empty()) {
                            break;
                        }
                        cell = maze->getCell(cellTop->x, cellTop->y);
                        if (cell != nullptr) {
                            cell->setStatus(MAZE_STATUS_WAY_OUT);
                            refreshShow(show, 1, &cell, false);
                        }
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
