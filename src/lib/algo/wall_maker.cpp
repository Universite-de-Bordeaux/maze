#include "wall_maker.hpp"

#include <iostream>

#include "../checker/depth_first.hpp"
#include "../queue.hpp"
#include "../show.hpp"
#include "../stack.hpp"

struct wall_maker {
    int x;
    int y;
    bool horizontal;
};

void processNeighbor(const Maze* maze, Queue& queue, Stack& stack, const int x,
                     const int y, const bool horizontal, int& count, int& j) {
    Wall* neighbor = maze->getWall(x, y, horizontal);
    if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
        neighbor->setAlreadyVisited(true);
        if ((horizontal && (x == 0 || x == maze->getWidth() - 1)) ||
            (!horizontal && (y == 0 || y == maze->getHeight() - 1))) {
            count++;
        }
        auto* wall = new wall_maker;
        wall->x = x;
        wall->y = y;
        wall->horizontal = horizontal;
        queue.push(wall);
        stack.push(wall);
        j++;
    }
}

static void resetAlreadyVisited(const Maze* maze) {
    for (int x = 0; x < maze->getWidth(); x++) {
        for (int y = 0; y < maze->getHeight(); y++) {
            for (int i = 0; i < 2; i++) {
                Wall* wall = maze->getWall(x, y, i);
                if (wall != nullptr) {
                    wall->setAlreadyVisited(false);
                }
            }
        }
    }
}

static int numberBorders(const Maze* maze, wall_maker* wall) {
    if (wall == nullptr ||
        maze->getWall(wall->x, wall->y, wall->horizontal) == nullptr) {
        return 0;
    }
    Wall* current = maze->getWall(wall->x, wall->y, wall->horizontal);
    Queue queue;
    Stack stack;
    queue.push(wall);
    stack.push(wall);
    current->setAlreadyVisited(true);
    int count = 0;
    if ((wall->horizontal &&
         (wall->x == 0 || wall->x == maze->getWidth() - 1)) ||
        (!wall->horizontal &&
         (wall->y == 0 || wall->y == maze->getHeight() - 1))) {
        count++;
    }
    while (!queue.empty()) {
        wall = static_cast<wall_maker*>(queue.front());
        queue.pop();
        int j = 0;
        if (wall->horizontal) {
            processNeighbor(maze, queue, stack, wall->x - 1, wall->y, true,
                            count, j);
            processNeighbor(maze, queue, stack, wall->x - 1, wall->y, false,
                            count, j);
            processNeighbor(maze, queue, stack, wall->x, wall->y, false, count,
                            j);
            processNeighbor(maze, queue, stack, wall->x + 1, wall->y, true,
                            count, j);
            processNeighbor(maze, queue, stack, wall->x - 1, wall->y + 1, false,
                            count, j);
            processNeighbor(maze, queue, stack, wall->x, wall->y + 1, false,
                            count, j);
        } else {
            processNeighbor(maze, queue, stack, wall->x, wall->y - 1, false,
                            count, j);
            processNeighbor(maze, queue, stack, wall->x, wall->y - 1, true,
                            count, j);
            processNeighbor(maze, queue, stack, wall->x, wall->y, true, count,
                            j);
            processNeighbor(maze, queue, stack, wall->x, wall->y + 1, false,
                            count, j);
            processNeighbor(maze, queue, stack, wall->x + 1, wall->y - 1, true,
                            count, j);
            processNeighbor(maze, queue, stack, wall->x + 1, wall->y, true,
                            count, j);
        }
    }
    while (!stack.empty()) {
        wall = static_cast<wall_maker*>(stack.top());
        stack.pop();
        Wall* current_tmp = maze->getWall(wall->x, wall->y, wall->horizontal);
        if (current_tmp != nullptr) {
            current_tmp->setAlreadyVisited(false);
        }
    }
    return count;
}

void algo_wall_maker(Maze* maze, const int width, const int height,
                     bool perfect, double probability, Show* show) {
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    refreshShow(show);
    Stack stack;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int i = 0; i < 2; i++) {
                if (i == 0 && x < width - 1) {
                    auto* wall = new wall_maker;
                    wall->x = x;
                    wall->y = y;
                    wall->horizontal = false;
                    stack.push(wall);
                } else if (i == 1 && y < height - 1) {
                    auto* wall = new wall_maker;
                    wall->x = x;
                    wall->y = y;
                    wall->horizontal = true;
                    stack.push(wall);
                }
            }
        }
    }

    while (!stack.empty()) {
        auto* wallsPossible =
            static_cast<wall_maker*>(stack.pop(maze->getRand()));
        const int x = wallsPossible->x;
        const int y = wallsPossible->y;
        const bool direction = wallsPossible->horizontal;
        maze->addWall(x, y, direction);
        const int count = numberBorders(maze, wallsPossible);
        bool isValid = false;
        checker_depth_first(maze, false, false, nullptr, &isValid, nullptr);
        if (count > 1) {
            maze->removeWall(x, y, direction);
        }
        maze->clearMaze();
        Cell* showCell[1] = {maze->getCell(x, y)};
        refreshShow(show, 1, showCell);
    }
}
