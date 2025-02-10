#include "fractal.hpp"

#include <cmath>
#include <iostream>

#include "../maze.hpp"
#include "../show.hpp"
#include "../var.hpp"

static bool add_wall_imperfect(Maze *maze, const int mid,
                               const double probability) {
    bool status = true;
    for (int i = 0; i < maze->getHeight(); i++) {
        status &= maze->addWall(mid - 1, i,
                                false) && maze->addWall(i, mid - 1, true);
    }
    int remove[4];
    remove[0] = maze->getRand()->get(0, mid - 1);
    status &= maze->removeWall(mid - 1, remove[0], false);
    remove[1] = maze->getRand()->get(0, mid - 1);
    status &= maze->removeWall(remove[1], mid - 1, true);
    remove[2] = maze->getRand()->get(0, mid - 1);
    status &= maze->removeWall(mid - 1, mid + remove[2], false);
    remove[3] = maze->getRand()->get(0, mid - 1);
    status &= maze->removeWall(mid + remove[3], mid - 1, true);
    if (!maze->getRand()->get(probability)) {
        const int r = maze->getRand()->get(0, 3);
        if (r == 0) {
            status &= maze->addWall(mid - 1, remove[0], false);
        } else if (r == 1) {
            status &= maze->addWall(remove[1], mid - 1, true);
        } else if (r == 2) {
            status &= maze->addWall(mid - 1, mid + remove[2], false);
        } else if (r == 3) {
            status &= maze->addWall(mid + remove[3], mid - 1, true);
        }
    }
    return status;
}

static bool add_wall_perfect(Maze *maze, const int mid) {
    bool status = true;
    for (int i = 0; i < mid; i++) {
        status &= maze->addWall(mid - 1, i, false);
        status &= maze->addWall(mid + i, mid - 1, true);
        status &= maze->addWall(mid - 1, mid + i, false);
        status &= maze->addWall(i, mid - 1, true);
    }
    int direction = maze->getRand()->get(0, 3);
    if (direction == NORTH) {
        int remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid + remove, mid - 1, true);
        remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid - 1, mid + remove, false);
        remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(remove, mid - 1, true);
    } else if (direction == EAST) {
        int remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid - 1, mid + remove, false);
        remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(remove, mid - 1, true);
        remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid - 1, remove, false);
    } else if (direction == SOUTH) {
        int remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(remove, mid - 1, true);
        remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid - 1, remove, false);
        remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid + remove, mid - 1, true);
    } else if (direction == WEST) {
        int remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid - 1, remove, false);
        remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid + remove, mid - 1, true);
        remove = maze->getRand()->get(0, mid - 1);
        status &= maze->removeWall(mid - 1, mid + remove, false);
    } else {
        return false;
    }
    return status;
}

static void quad_maze(Maze *maze) {
    const int old_width = maze->getWidth();
    const int old_height = maze->getHeight();
    auto new_maze = Maze();
    new_maze.setWidthHeight(old_width, old_height);
    bool status = true;
    // copie de maze dans new_maze
    for (int i = 0; i < old_width; i++) {
        for (int j = 0; j < old_height; j++) {
            for (int k = 0; k < 2; k++) {
                if (maze->getWall(i, j, k)) {
                    status &= new_maze.addWall(i, j, k);
                }
            }
        }
    }
    maze->setWidthHeight(2 * maze->getWidth(), 2 * maze->getHeight());
    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            for (int k = 0; k < 2; k++) {
                if (new_maze.getWall(i, j, k)) {
                    status &= maze->addWall(i, j, k);
                    status &= maze->addWall(i + old_width, j, k);
                    status &= maze->addWall(i + old_width, j + old_height, k);
                    status &= maze->addWall(i, j + old_height, k);
                }
            }
        }
    }
    new_maze.clearMaze();
}

void algo_fractal(Maze *maze, int n, const bool perfect,
                  const double probability, Show *show) {
    maze->setWidthHeight(1, 1);
    if (show && !show->getLowFreq()) {
        show->create();
    }
    if (show && !show->getLowFreq()) {
        show->destroy();
        show->create();
    }
    refreshShow(show);
    for (int i = 0; i < n; i++) {

        // duplication du labyrinthe
        quad_maze(maze);

        // ajout des murs
        if (!perfect && !add_wall_imperfect(maze, maze->getHeight() / 2, probability)) {
                std::cerr << "Error: add_wall" << std::endl;
                return;
            }
        }
        if (!add_wall_perfect(maze, maze->getHeight() / 2)) {
            std::cerr << "Error: add_wall" << std::endl;
            return;
        }

        // affichage
        if (show && !show->getLowFreq()) {
            show->destroy();
            show->create();
        }
        refreshShow(show);

        if (show && show->getLowFreq()) {
            show->destroy();
            show->create();
        }
    }