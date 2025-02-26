#include "diagonal.hpp"

#include "../show.hpp"

struct start {
    bool left;
    bool top;
};

/**
 * @brief Crée une sortie dans le labyrinthe
 * @param a La position actuelle
 * @param maxA La position maximale
 * @param b La position actuelle
 * @param maxB La position maximale
 * @param maze Le labyrinthe
 * @param isHorizontal Si la sortie est horizontale
 * @param whereStart La position de départ
 * @param perfect
 * @param probability
 * @param show L'objet pour afficher le labyrinthe
 */
static void create_exit(int *a, const int *maxA, const int *b, const int *maxB,
                        Maze *maze, const bool isHorizontal,
                        const start *whereStart, const bool perfect,
                        const double probability, Show *show) {
    if ((isHorizontal ? !whereStart->top : !whereStart->left) <= *a &&
        *a < *maxA - (isHorizontal ? whereStart->top : whereStart->left)) {
        const int startB = isHorizontal      ? (whereStart->left ? *b : 0)
                           : whereStart->top ? *b
                                             : 0;
        const int endB = isHorizontal      ? (whereStart->left ? *maxB : *b)
                         : whereStart->top ? *maxB
                                           : *b;
        if (startB == endB) {
            *a += isHorizontal       ? (whereStart->top ? 1 : -1)
                  : whereStart->left ? 1
                                     : -1;
            return;
        }
        const int rb = maze->getRand()->get(startB, endB - 1);
        for (int bb = startB; bb <= endB; bb++) {
            if (bb != rb &&
                (perfect || maze->getRand()->get(1 - probability))) {
                if (isHorizontal) {
                    maze->addWall(bb, *a - !whereStart->top, isHorizontal);
                } else {
                    maze->addWall(*a - !whereStart->left, bb, isHorizontal);
                }
            }
            Cell *cell =
                maze->getCell(isHorizontal ? bb : *a, isHorizontal ? *a : bb);
            refreshShow(show, 1, &cell, false);
        }
        *a += isHorizontal       ? (whereStart->top ? 1 : -1)
              : whereStart->left ? 1
                                 : -1;
        Cell *cell =
            maze->getCell(isHorizontal ? rb : *a, isHorizontal ? *a : rb);
        refreshShow(show, 1, &cell, true);
    }
}

void algo_diagonal(Maze *maze, const int width, const int height,
                   const bool perfect, const double probability, Show *show) {
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    const start whereStart = {maze->getRand()->get(0, 1) == 0,
                              maze->getRand()->get(0, 1) == 0};
    int x = whereStart.left ? 0 : width - 1;
    int y = whereStart.top ? 0 : height - 1;
    while ((!whereStart.left <= x && x < width - whereStart.left) ||
           (!whereStart.top <= y && y < height - whereStart.top)) {
        if (maze->getRand()->get(0, 1)) {
            create_exit(&x, &width, &y, &height, maze, false, &whereStart,
                        perfect, probability, show);
            create_exit(&y, &height, &x, &width, maze, true, &whereStart,
                        perfect, probability, show);
        } else {
            create_exit(&y, &height, &x, &width, maze, true, &whereStart,
                        perfect, probability, show);
            create_exit(&x, &width, &y, &height, maze, false, &whereStart,
                        perfect, probability, show);
        }
    }
    refreshShow(show);
}
