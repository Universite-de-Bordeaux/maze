#include "algo_1.hpp"
#include <cstdlib>
#include <ctime>

struct start {
    bool left;
    bool top;
};

static void create_exit(int *a, int *maxA, int* b, int*maxB, Maze *maze, bool isHorizontal, start *whereStart) {
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
        }
        (*a) += isHorizontal ? (whereStart->top ? 1 : -1) : (whereStart->left ? 1 : -1);
    }
}

void algo_1(Maze* maze, int width, int height, bool perfect) {
    maze->setWidthHeight(width, height);
    srand(time(0));
    start whereStart = {(bool)(rand() % 2), (bool)(rand() % 2)};
    int x = whereStart.left ? 0 : width - 1;
    int y = whereStart.top ? 0 : height - 1;
    while ((!whereStart.left <= x && x < width - whereStart.left) ||
        (!whereStart.top <= y && y < height - whereStart.top)) {
        if (rand() % 2 == 0) {
            create_exit(&x, &width, &y, &height, maze, false, &whereStart);
            create_exit(&y, &height, &x, &width, maze, true, &whereStart);
        } else {
            create_exit(&y, &height, &x, &width, maze, true, &whereStart);
            create_exit(&x, &width, &y, &height, maze, false, &whereStart);
        }
    }
}
