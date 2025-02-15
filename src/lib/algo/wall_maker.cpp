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
                     const int y, const wall_maker& previous_wall,
                     const bool horizontal, int& nbBorders, int& j,
                     int& nbNeighbors, int& nbNeighborsNotVisited) {
    Wall* neighbor = maze->getWall(x, y, horizontal);
    if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
        neighbor->setAlreadyVisited(true);
        if ((horizontal && (x == 0 || x == maze->getWidth() - 1)) ||
            (!horizontal && (y == 0 || y == maze->getHeight() - 1))) {
            nbBorders++;
        }
        auto* wall = new wall_maker;
        wall->x = x;
        wall->y = y;
        wall->horizontal = horizontal;
        queue.push(wall);
        stack.push(wall);
        j++;
        nbNeighbors++;
        nbNeighborsNotVisited++;
    } else if (neighbor != nullptr && neighbor->isAlreadyVisited()) {
        nbNeighbors++;
    }
}

static void numberBorders(const Maze* maze, wall_maker* wall, int& nbBorders,
                          int& nbLoops) {
    if (wall == nullptr ||
        maze->getWall(wall->x, wall->y, wall->horizontal) == nullptr) {
        nbBorders = 0;
        return;
    }
    Wall* current = maze->getWall(wall->x, wall->y, wall->horizontal);
    Queue queue;
    Stack stack;
    queue.push(wall);
    stack.push(wall);
    current->setAlreadyVisited(true);
    if ((wall->horizontal &&
         (wall->x == 0 || wall->x == maze->getWidth() - 1)) ||
        (!wall->horizontal &&
         (wall->y == 0 || wall->y == maze->getHeight() - 1))) {
        nbBorders++;
    }
    while (!queue.empty() && nbBorders < 2 && nbLoops < 1) {
        wall_maker previous_wall = *wall;
        wall = static_cast<wall_maker*>(queue.front());
        queue.pop();
        int j = 0;
        int nbNeighbors = 0;
        int nbNeighborsNotVisited = 0;
        if (wall->horizontal) {
            processNeighbor(maze, queue, stack, wall->x - 1, wall->y,
                            previous_wall, true, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x - 1, wall->y,
                            previous_wall, false, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x, wall->y, previous_wall,
                            false, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x + 1, wall->y,
                            previous_wall, true, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x - 1, wall->y + 1,
                            previous_wall, false, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x, wall->y + 1,
                            previous_wall, false, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
        } else {
            processNeighbor(maze, queue, stack, wall->x, wall->y - 1,
                            previous_wall, false, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x, wall->y - 1,
                            previous_wall, true, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x, wall->y, previous_wall,
                            true, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x, wall->y + 1,
                            previous_wall, false, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x + 1, wall->y - 1,
                            previous_wall, true, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
            processNeighbor(maze, queue, stack, wall->x + 1, wall->y,
                            previous_wall, true, nbBorders, j, nbNeighbors,
                            nbNeighborsNotVisited);
        }
        if (nbNeighbors - nbNeighborsNotVisited >= 2) {
            nbLoops++;
        }
    }
    while (!queue.empty()) {
        queue.pop();
    }
    while (!stack.empty()) {
        wall = static_cast<wall_maker*>(stack.top());
        stack.pop();
        Wall* current_tmp = maze->getWall(wall->x, wall->y, wall->horizontal);
        if (current_tmp != nullptr) {
            current_tmp->setAlreadyVisited(false);
        }
    }
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
        int nbBorders = 0;
        int nbLoops = 0;
        numberBorders(maze, wallsPossible, nbBorders, nbLoops);
        if (nbBorders >= 2 || nbLoops >= 1) {
            if (nbLoops >= 1)
                std::cout << "x: " << x << " y: " << y
                          << " direction: " << direction
                          << " nbBorders: " << nbBorders
                          << " nbLoops: " << nbLoops << std::endl;
            maze->removeWall(x, y, direction);
        }
        Cell* showCell[1] = {maze->getCell(x, y)};
        refreshShow(show, 1, showCell);
    }
}
