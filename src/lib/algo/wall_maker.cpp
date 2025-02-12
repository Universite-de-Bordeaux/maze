#include "wall_maker.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "../show.hpp"

static int numberBorders(const int width, const int height, Wall* wall) {
    if (wall == nullptr) {
        return 0;
    }
    if (wall->isAlreadyVisited()) {
        return 0;
    }

    int count = 0;
    Queue queue;
    queue.push(wall);
    wall->setAlreadyVisited(true);

    if (wall->isBorder()) {
        count++;
    }

    while (!queue.empty()) {
        const Wall* current = static_cast<Wall*>(queue.front());
        queue.pop();

        for (int i = 0; i < 6; i++) {
            Wall* neighbor = current->getNeighbor(i);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                neighbor->setAlreadyVisited(true);
                // std::cout << " test=" << neighbor->isBorder() << std::endl;
                if (neighbor->isBorder()) {
                    count++;
                    // std::cout << " numberBorders=" << count << std::endl;
                }
                queue.push(neighbor);
            }
        }
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
    int wallsPossible[width * height * 2][3];
    int wallsPossibleSize = 0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int i = 0; i < 2; i++) {
                if (i == 0 && x < width - 1) {
                    wallsPossible[wallsPossibleSize][0] = x;
                    wallsPossible[wallsPossibleSize][1] = y;
                    wallsPossible[wallsPossibleSize][2] = 0;
                    std::cout << "wallsPossible[" << wallsPossibleSize
                              << "][0]=" << wallsPossible[wallsPossibleSize][0]
                              << " wallsPossible[" << wallsPossibleSize
                              << "][1]=" << wallsPossible[wallsPossibleSize][1]
                              << " wallsPossible[" << wallsPossibleSize
                              << "][2]=" << wallsPossible[wallsPossibleSize][2]
                              << std::endl;
                    wallsPossibleSize++;
                } else if (i == 1 && y < height - 1) {
                    wallsPossible[wallsPossibleSize][0] = x;
                    wallsPossible[wallsPossibleSize][1] = y;
                    wallsPossible[wallsPossibleSize][2] = 1;
                    std::cout << "wallsPossible[" << wallsPossibleSize
                              << "][0]=" << wallsPossible[wallsPossibleSize][0]
                              << " wallsPossible[" << wallsPossibleSize
                              << "][1]=" << wallsPossible[wallsPossibleSize][1]
                              << " wallsPossible[" << wallsPossibleSize
                              << "][2]=" << wallsPossible[wallsPossibleSize][2]
                              << std::endl;
                    wallsPossibleSize++;
                }
            }
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < width * height * 2; i++) {
        std::cout << "wallsPossible[" << i << "][0]=" << wallsPossible[i][0]
                  << " wallsPossible[" << i << "][1]=" << wallsPossible[i][1]
                  << " wallsPossible[" << i << "][2]=" << wallsPossible[i][2]
                  << std::endl;
    }
    while (wallsPossibleSize > 0) {
        const int random = maze->getRand()->get(0, wallsPossibleSize - 1);
        const int x = wallsPossible[random][0];
        const int y = wallsPossible[random][1];
        const int direction = wallsPossible[random][2];
        wallsPossible[random][0] = wallsPossible[wallsPossibleSize - 1][0];
        wallsPossible[random][1] = wallsPossible[wallsPossibleSize - 1][1];
        wallsPossible[random][2] = wallsPossible[wallsPossibleSize - 1][2];
        wallsPossibleSize--;
        if (direction == 0) {
            maze->addWall(x, y, false, true);
        } else {
            maze->addWall(x, y, true, true);
        }
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
