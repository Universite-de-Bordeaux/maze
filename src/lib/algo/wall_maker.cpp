#include "wall_maker.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "../show.hpp"

static int numberBorders(int width, int height, Wall* wall) {
    if (wall == nullptr) {
        return 0;
    }
    if (wall->isAlreadyVisited()) {
        return 0;
    }
    wall->setAlreadyVisited(true);
    int number = 0;
    if (wall->isBorder()) {
        number++;
    }
    for (int i = 0; i < 6; i++) {
        Wall* neighbor = wall->getNeighbor(i);
        if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
            number += numberBorders(width, height, neighbor);
        }
    }
    return number;
}

static void resetAlreadyVisited(Maze* maze) {
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

void algo_wall_maker(Maze* maze, int width, int height, bool perfect,double probability,
                    Show* show) {
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    int wallsPossible[width * height * 2][3];
    int wallsPossibleSize = 0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int i = 0; i < 2; i++) {
                if (i == 0 && x < width - 1) {
                    wallsPossible[wallsPossibleSize][0] = x;
                    wallsPossible[wallsPossibleSize][1] = y;
                    wallsPossible[wallsPossibleSize][2] = 0;
                    wallsPossibleSize++;
                } else if (i == 1 && y < height - 1) {
                    wallsPossible[wallsPossibleSize][0] = x;
                    wallsPossible[wallsPossibleSize][1] = y;
                    wallsPossible[wallsPossibleSize][2] = 1;
                    wallsPossibleSize++;
                }
            }
        }
    }
    while (wallsPossibleSize > 0) {
        int random = rand() % wallsPossibleSize;
        int x = wallsPossible[random][0];
        int y = wallsPossible[random][1];
        int direction = wallsPossible[random][2];
        wallsPossible[random][0] = wallsPossible[wallsPossibleSize - 1][0];
        wallsPossible[random][1] = wallsPossible[wallsPossibleSize - 1][1];
        wallsPossible[random][2] = wallsPossible[wallsPossibleSize - 1][2];
        wallsPossibleSize--;
        if (direction == 0) {
            maze->addWall(x, y, false, true);
        } else {
            maze->addWall(x, y, true, true);
        }
        std::cout << "x=" << x << " y=" << y << " direction=" << direction
                  << " numberBorders="
                  << numberBorders(width, height,
                                   maze->getWall(x, y, direction))
                  << std::endl;
        resetAlreadyVisited(maze);
        if (numberBorders(width, height, maze->getWall(x, y, direction)) > 1) {
            maze->removeWall(x, y, direction, true);
        }
        resetAlreadyVisited(maze);
        Cell* showCell[1] = {maze->getCell(x, y)};
        refreshShow(show, 1, showCell);
        if (show && show->isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}
