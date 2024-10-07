#include "algo_cours.hpp"
#include <iostream>

struct coordinate{
    int x;
    int y;
} ;

static Cell* nextNeighbor (Cell* current);

void algo_cours(Maze* maze, int width, int height, bool perfect) {
    maze->setWidthHeight(width, height);
    struct coordinate cellHistory[width * height];
    Cell *cellStart = maze->getCell(0, 0);
    nextNeighbor(cellStart);
}
