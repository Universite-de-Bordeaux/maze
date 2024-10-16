# include "algo_fractal.hpp"
#include "maze.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

void add_vertical(Maze *maze, int height, int column) {
    for (int i = 0; i < maze->getHeight(); i++) {
        maze->addWall(column, i, false);
    }
    return;
}

void add_horizontal(Maze *maze, int line, int width) {

    for (int i = 0; i < width; i++) {
        std::cout << i << ' ' << line << std::endl;
        std::cout << maze->addWall(i, line, true) << std::endl;
    }
    return;
}

// void remove(Maze * maze, int direction, );

void quad_maze(Maze * maze) {
    int old_width = maze->getWidth();
    int old_height = maze->getHeight();
    maze->setWidthHeight(2*maze->getWidth(), 2*maze->getHeight());

    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            maze->setCell(i, j+old_width, maze->getCell(i, j));
            maze->setCell(i+old_height, j, maze->getCell(i, j));
            maze->setCell(i+old_height, j+old_width, maze->getCell(i, j));
        }
    }
    return;
}

void algo_fractal(Maze* maze, int n, bool perfect, Show *show) {
    int nb_murs_supp = 3;
    n = std::pow(2, n);
    maze->setWidthHeight(2, 2);
    while (n) {
        quad_maze(maze);
        int *p_1 = &nb_murs_supp;
        int width = maze->getWidth();
        int height = maze->getHeight();
        std::cout << "taille : " << width << ' ' << height << std::endl;
        int r = rand() % 4;
        if (!perfect) {
            *p_1 = 3 + r % 2;
        }

        int line = height / 2;
        int column = width / 2;
        // std::cout << "test 1" << std::endl;
        add_horizontal(maze, line, width);
        // std::cout << "test 2" << std::endl;
        add_vertical(maze, height, column);

        n /= 2;
    }
    return;
}
