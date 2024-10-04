#include "algo_cours.hpp"
#include <iostream>

struct coordinate{
    int x;
    int y;
} ;

void algo_cours(Maze* maze, int width, int height, bool perfect) {
    maze->setWidthHeight(width, height);
    struct coordinate cellHistory[width * height];
    Cell *cellStart = maze->getCell(0, 0);
    int count = 0;
    for (int i = 0; i< 4; i++) {
        Cell *neighbor = cellStart->getNeighbor(i);
        if(neighbor != nullptr ){
            count += 1 ;
            std::cout << "x : " << neighbor->getX() << " | y : " << neighbor->getY() << std::endl;
        }
    }
    std::cout << "n : "<<  count << std::endl;
}