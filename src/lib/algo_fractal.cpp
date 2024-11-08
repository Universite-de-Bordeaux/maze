#include "algo_fractal.hpp"
#include "maze.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

static void add_column(Maze *maze, int column) {
    for (int i = 0; i < maze->getHeight(); i++) {
        std::cout << column << ' ' << i << " vertical" << std::endl;
        maze->addWall(column, i, false);
    }
    return;
}

static void add_line(Maze *maze, int line) {

    for (int i = 0; i < maze->getWidth(); i++) {
        std::cout << i << ' ' << line << " horizontal" << std::endl;
        maze->addWall(i, line, true);
    }
    return;
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
    std::cout << maze->getWall(0, 0, false) << std::endl;
    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            Cell *cell = new_maze.getCell(i, j);
            for (int k = 0; k < 2; k++) {
                if (maze->getWall(i, j, k)) {
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
    int nb_murs_supp = 3;
    n = std::pow(2, n);
    maze->setWidthHeight(1, 1);
    while (n > 1) {
        std::cout << "MAZE ACTUEL : " << maze->getWidth() << ' ' << maze->getHeight() << std::endl;
        quad_maze(maze);
        int width = maze->getWidth();
        int height = maze->getHeight();
        int r = rand() % 4;
        // if (!perfect) {
        //     *p_1 = 3 + r % 2;
        // }

        int line = height / 2 - 1;
        int column = width / 2 - 1;
        add_line(maze, line);
        add_column(maze, column);
        // FIXME
        n /= 2;
        std::cout << "n: " << n << std::endl;
    }
    return;
}
