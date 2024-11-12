#include <iostream>

#include "algo_wallmaker.hpp"
#include "../show.hpp"

static int numberBorders(int width, int height, Wall* wall) {
    std::cout << "numberBorders" << std::endl;
    if (wall == nullptr) {
        return 0;
    }
    std::cout << "aaa" << std::endl;
    std::cout << "wall->isAlreadyVisited() = " << wall->isAlreadyVisited() << std::endl;
    std::cout << "bbb" << std::endl;
    wall->setAlreadyVisited(true);
    std::cout << "ccc" << std::endl;
    int number = 0;
    for (int i = 0; i < 6; i++) {
        std::cout << "ddd" << std::endl;
        Wall* neighbor = wall->getNeighbor(i);
        std::cout << "eee" << std::endl;
        if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
            number += numberBorders(width, height, neighbor);
        }
        std::cout << "fff" << std::endl;
    }
    std::cout << "ggg" << std::endl;
    if (wall->isBorder()) {
        number++;
    }
    wall->setAlreadyVisited(false);
    return number;
}

void algo_wallmaker(Maze* maze, int width, int height, bool perfect, Show* show) {
    maze->setWidthHeight(width, height);
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
    for (int i = 0; i < wallsPossibleSize; i++) {
        std::cout << "x=" << wallsPossible[i][0] << ", y=" << wallsPossible[i][1] << ", direction=" << wallsPossible[i][2] << std::endl;
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
        numberBorders(width, height, maze->getWall(x, y, direction));
        std::cout << "numberBorders(width, height, maze->getWall(0, 0, 0)) = " << numberBorders(width, height, maze->getWall(0, 0, 0)) << std::endl;
//        if (numberBorders(width, height, maze->getCell(0, 0)->getWall(0)) > 1) {
//            if (direction == 0) {
//                maze->removeWall(x, y, false, true);
//            } else {
//                maze->removeWall(x, y, true, true);
//            }
//        }
        std::cout << "x=" << x << ", y=" << y << ", direction=" << direction << std::endl;
    }
}