#include "wall_maker.hpp"

#include <iostream>

#include "../checker/depth_first.hpp"
#include "../queue.hpp"
#include "../show.hpp"

struct wall_maker {
    int x;
    int y;
    bool horizontal;
};

void processNeighbor(const Maze* maze, Queue& queue, const int x, const int y,
                     const bool horizontal, int& count, int& j) {
    Wall* neighbor = maze->getWall(x, y, horizontal);
    if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
        neighbor->setAlreadyVisited(true);
        if ((horizontal && (x == 0 || x == maze->getWidth() - 1)) ||
            (!horizontal && (y == 0 || y == maze->getHeight() - 1))) {
            count++;
        }
        queue.push(neighbor);
        j++;
    }
}

static int numberBorders(const Maze* maze, wall_maker* wall) {
    if (wall == nullptr ||
        maze->getWall(wall->x, wall->y, wall->horizontal) == nullptr) {
        return 0;
    }

    int count = 0;
    Queue queue;
    queue.push(wall);
    maze->getWall(wall->x, wall->y, wall->horizontal)->setAlreadyVisited(true);

    if (wall->horizontal && (wall->x == 0 || wall->x == maze->getWidth() - 1)) {
        count++;
    } else if (!wall->horizontal &&
               (wall->y == 0 || wall->y == maze->getHeight() - 1)) {
        count++;
    }

    while (!queue.empty()) {
        const wall_maker* current = static_cast<wall_maker*>(queue.front());
        queue.pop();
        int j = 0;
        if (current->horizontal) {
            processNeighbor(maze, queue, current->x - 1, current->y, true,
                            count, j);
            processNeighbor(maze, queue, current->x - 1, current->y, false,
                            count, j);
            processNeighbor(maze, queue, current->x, current->y, false, count,
                            j);
            processNeighbor(maze, queue, current->x + 1, current->y, true,
                            count, j);
            processNeighbor(maze, queue, current->x - 1, current->y + 1, false,
                            count, j);
            processNeighbor(maze, queue, current->x, current->y + 1, false,
                            count, j);
        } else {
            processNeighbor(maze, queue, current->x, current->y - 1, false,
                            count, j);
            processNeighbor(maze, queue, current->x, current->y - 1, true,
                            count, j);
            processNeighbor(maze, queue, current->x, current->y, true, count,
                            j);
            processNeighbor(maze, queue, current->x, current->y + 1, false,
                            count, j);
            processNeighbor(maze, queue, current->x + 1, current->y - 1, true,
                            count, j);
            processNeighbor(maze, queue, current->x + 1, current->y, true,
                            count, j);
        }
        std::cout << " neighbors=" << j << std::endl;
    }

    return count;
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

void algo_wall_maker(Maze* maze, const int width, const int height, bool,
                     double, Show* show) {
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    refreshShow(show);
    Queue queue;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int i = 0; i < 2; i++) {
                if (i == 0 && x < width - 1) {
                    auto* wall = new wall_maker;
                    wall->x = x;
                    wall->y = y;
                    wall->horizontal = false;
                    queue.push(wall);
                } else if (i == 1 && y < height - 1) {
                    auto* wall = new wall_maker;
                    wall->x = x;
                    wall->y = y;
                    wall->horizontal = true;
                    queue.push(wall);
                }
            }
        }
    }
    // std::cout << "wallsPossibleSize=" << wallsPossibleSize << std::endl;

    while (!queue.empty()) {
        const auto* wallsPossible =
            static_cast<wall_maker*>(queue.pop(maze->getRand()));
        const int x = wallsPossible->x;
        const int y = wallsPossible->y;
        const bool direction = wallsPossible->horizontal;
        maze->addWall(x, y, direction);
        // if (number > 1) {
        bool isValid = false;
        checker_depth_first(maze, false, false, nullptr, &isValid, nullptr);
        if (!isValid) {
            maze->removeWall(x, y, direction);
        }
        maze->clearMaze();
        // resetAlreadyVisited(maze);
        Cell* showCell[1] = {maze->getCell(x, y)};
        refreshShow(show, 1, showCell);
    }
}
