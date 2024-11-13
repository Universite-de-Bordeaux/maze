#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "algo_fractal.hpp"
#include "../maze.hpp"
#include "../show.hpp"
#include "../var.hpp"

static bool add_wall(Maze *maze, int mid, int direction) {
    for (int i = 0; i < mid; i++) {
    	maze->addWall(mid-1, i, false);
    	maze->addWall(mid + i, mid-1, true);
    	maze->addWall(mid-1, mid + i, false);
    	maze->addWall(i, mid-1, true);
    }
    if (direction == NORTH) {
		int remove = rand() % mid;
        maze->removeWall(mid + remove, mid-1, true);
		remove = rand() % mid;
        maze->removeWall(mid-1, mid + remove, false);
        remove = rand() % mid;
        maze->removeWall(remove, mid-1, true);
    }
    else if (direction == EAST) {
      	int remove = rand() % mid;
        maze->removeWall(mid-1, mid + remove, false);
        remove = rand() % mid;
        maze->removeWall(remove, mid-1, true);
        remove = rand() % mid;
        maze->removeWall(mid-1, remove, false);
    }
    else if (direction == SOUTH) {
    	int remove = rand() % mid;
        maze->removeWall(remove, mid-1, true);
        remove = rand() % mid;
        maze->removeWall(mid-1, remove, false);
        remove = rand() % mid;
        maze->removeWall(mid + remove, mid-1, true);
    }
    else if (direction == WEST) {
        int remove = rand() % mid;
        maze->removeWall(mid-1, remove, false);
        remove = rand() % mid;
        maze->removeWall(mid + remove, mid-1, true);
		remove = rand() % mid;
        maze->removeWall(mid-1, mid + remove, false);
    }
    else {
        return false;
    }
    return true;
}

static void quad_maze(Maze * maze) {
    int old_width = maze->getWidth();
    int old_height = maze->getHeight();
    Maze new_maze = Maze();
    new_maze.setWidthHeight(old_width, old_height);
    // copie de maze dans new_maze
    for (int i = 0; i < old_width; i++) {
        for (int j = 0; j < old_height; j++) {
            for (int k = 0; k < 2; k++) {
                if (maze->getWall(i, j, k)) {
                    new_maze.addWall(i, j, k);
                }
            }
        }
    }
    maze->setWidthHeight(2*maze->getWidth(), 2*maze->getHeight());
    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            for (int k = 0; k < 2; k++) {
                if (new_maze.getWall(i, j, k)) {
                    maze->addWall(i, j, k);
                    maze->addWall(i+old_width, j, k);
                    maze->addWall(i+old_width, j+old_height, k);
                    maze->addWall(i, j+old_height, k);
                }
            }
        }
    }
    new_maze.clearMaze();
}

void algo_fractal(Maze* maze, int n, bool perfect, Show *show) {
    maze->setWidthHeight(1, 1);
    if (show) {
        show->create();
    }
    int nb_murs_supp = 3;
    if (show) {
        show->destroy();
        show->create();
    }
    refreshShow(show);
    while (n > 0) {
        // attend 10ms
        if (show && show->isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // duplication du labyrinthe
        quad_maze(maze);

        // ajout des murs
        int direction = rand() % 4;
        // if (!perfect) {
        //     *p_1 = 3 + direction % 2;
        // }
        if (!add_wall(maze, maze->getHeight() / 2, direction)) {
            std::cerr << "Error: add_wall" << std::endl;
            return;
        }

        // affichage
        if (show) {
            show->destroy();
            show->create();
        }
        refreshShow(show);

        n -= 1;
    }
    return;
}
