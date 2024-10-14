# include "algo_fractal.hpp"
#include "cell.hpp"
#include <cstdlib>
#include <ctime>

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
    Maze *new_maze = maze;
    int nb_murs_supp = 3;

    while (n) {
        int *p_1 = &nb_murs_supp;
        int width = maze->getWidth();
        int height = maze->getHeight();
        int line = height / 2;
        int column = width / 2;
        int r = rand() % 4;

        if (!perfect) {
            *p_1 = 3 + r % 2;
        }

        for (int i = 0; i < nb_murs_supp; i++) {
            if (r == 0) {
                int r_line = rand() % line;
                new_maze->addWall(column, r_line, false);
            }
            else if (r == 1) {
                int r_column = column + rand() % column;
                new_maze->addWall(r_column, line, true);
            }
            else if (r == 2) {
                int r_line = line + rand() % line;
                new_maze->addWall(column, r_line, false);
            }
            else {
                int r_column = rand() % column;
                new_maze->addWall(r_column, line, true);
            }
        }
        quad_maze(new_maze);
        n /= 2;
    }
    // delete new_maze;
    return;
}
