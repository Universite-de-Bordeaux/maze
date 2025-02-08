#include "breadth_first.hpp"

#include <iostream>

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

void checker_breadth_first(const Maze *maze, const bool perfect, Show *show) {
    Queue queue;
    Stack stack;
    bool imperfect = false;
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return;
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
        if (cell->getAbsoluteNumberOfNeighbors() -
                cell->getAbsoluteNumberOfNeighborsNotVisited() >=
            2) {
            cell->setStatus(MAZE_STATUS_TOO_MANY_NEIGHBORS);
            imperfect = true;
        refreshShow(show, 1, &cell, true);
        } else {
            refreshShow(show, 1, &cell, false);
        }
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
