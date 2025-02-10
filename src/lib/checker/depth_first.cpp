#include "depth_first.hpp"

#include <iostream>

#include "../cell.hpp"
#include "../maze.hpp"
#include "../stack.hpp"

void check(const Maze *maze, const bool left, const bool perfect, Show *show,
           bool *imperfect) {
    struct IterativeCheckParams {
        int x;
        int y;
        int direction;
        Show *show;
        bool left;
        bool perfect;
        bool *imperfect;
    };

    Stack stack;
    IterativeCheckParams params = {0, 0, 0, show, left, perfect, imperfect};
    stack.push(&params);

    while (!stack.empty()) {
        const auto *current = static_cast<IterativeCheckParams *>(stack.top());
        stack.pop();

        Cell *cell = maze->getCell(current->x, current->y);
        if (cell == nullptr) continue;

        cell->setAlreadyVisited(true);
        cell->setStatus(MAZE_STATUS_VISITED);

        // Perfect maze checks
        if (perfect) {
            if (cell->getAbsoluteNumberOfNeighbors() -
                    cell->getAbsoluteNumberOfNeighborsNotVisited() >=
                2) {
                cell->setStatus(MAZE_STATUS_TOO_MANY_NEIGHBORS);
                *imperfect = true;
            }
            if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
                if (cell->getAbsoluteNumberOfNeighbors() -
                        cell->getAbsoluteNumberOfNeighborsNotVisited() <
                    2) {
                    cell->setStatus(MAZE_STATUS_HOPELESS);
                }
                refreshShow(current->show, 1, &cell, true);
                continue;
            }
        }

        const int numberOfNeighborsNotVisited =
            cell->getAbsoluteNumberOfNeighborsNotVisited();
        if (numberOfNeighborsNotVisited <= 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(current->show, 1, &cell, true);
            continue;
        }

        refreshShow(current->show, 1, &cell, false);

        // Determine the order of directions based on 'left'
        int directions[4];
        if (current->left) {
            for (int i = 0; i < 4; ++i) {
                directions[i] = (current->direction + i) % 4;
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                int index = (current->direction - i) % 4;
                if (index < 0) index += 4;
                directions[i] = index;
            }
        }

        // Push the directions in reverse order to maintain original processing
        for (int i = 3; i >= 0; --i) {
            int index = directions[i];
            if (cell->isNeighbor(index)) {
                const Cell *neighbor = cell->getNeighbor(index);
                if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                    const auto newParams = new IterativeCheckParams();
                    newParams->x = neighbor->getX();
                    newParams->y = neighbor->getY();
                    newParams->direction = (index + 2) % 4;
                    newParams->show = show;
                    newParams->left = current->left;
                    newParams->perfect = current->perfect;
                    newParams->imperfect = imperfect;

                    stack.push(newParams);
                }
            }
        }
    }
}

void checker_depth_first(const Maze *maze, const bool perfect, const bool left,
                         Show *show) {
    bool imperfect = false;
    check(maze, left, perfect, show, &imperfect);
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
