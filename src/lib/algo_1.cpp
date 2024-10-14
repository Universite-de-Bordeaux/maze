#include "algo_1.hpp"
#include <cstdlib>
#include <ctime>

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
 * @param show L'objet pour afficher le labyrinthe
 */
static void create_exit(int *a, int *maxA, int* b, int*maxB, Maze *maze, bool isHorizontal, start *whereStart, Show *show) {
    if((isHorizontal ? !whereStart->top : !whereStart->left) <= *a &&
        *a < *maxA - (isHorizontal ? whereStart->top : whereStart->left)) {
        int startB = (isHorizontal ? (whereStart->left ? *b : 0) : (whereStart->top ? *b : 0));
        int endB = (isHorizontal ? (whereStart->left ? *maxB : *b) : (whereStart->top ? *maxB : *b));
        if (startB == endB) {
            (*a) += isHorizontal ? (whereStart->top ? 1 : -1) : (whereStart->left ? 1 : -1);
            return;
        }
        int rb = (int)(rand() % (endB - startB)) + startB;
        for (int bb = startB;
            bb <= endB;
            bb++) {
            if (bb != rb) {
                if (isHorizontal) {
                    maze->addWall(bb, *a - !whereStart->top, isHorizontal);
                } else {
                    maze->addWall(*a - !whereStart->left, bb, isHorizontal);
                }
            }
            if (maze -> getWidth() <= MAZE_REFRESH_SIZE && maze -> getHeight() <= MAZE_REFRESH_SIZE) {
                if (show != nullptr && show->isOpen()) {
                    show->update();
                }
            }
        }
        (*a) += isHorizontal ? (whereStart->top ? 1 : -1) : (whereStart->left ? 1 : -1);
        if (maze -> getWidth() > MAZE_REFRESH_SIZE || maze -> getHeight() > MAZE_REFRESH_SIZE) {
            if (show != nullptr && show->isOpen()) {
                show->update();
            }
        }
    }
}

void algo_1(Maze* maze, int width, int height, bool perfect, Show *show) {
    srand(time(0));
    start whereStart = {(bool)(rand() % 2), (bool)(rand() % 2)};
    int x = whereStart.left ? 0 : width - 1;
    int y = whereStart.top ? 0 : height - 1;
    while ((!whereStart.left <= x && x < width - whereStart.left) ||
        (!whereStart.top <= y && y < height - whereStart.top)) {
        if (rand() % 2 == 0) {
            create_exit(&x, &width, &y, &height, maze, false, &whereStart, show);
            create_exit(&y, &height, &x, &width, maze, true, &whereStart, show);
        } else {
            create_exit(&y, &height, &x, &width, maze, true, &whereStart, show);
            create_exit(&x, &width, &y, &height, maze, false, &whereStart, show);
        }
    }
}