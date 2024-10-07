#include "algo_cours.hpp"
#include <iostream>

struct coordinate{
    int x;
    int y;
} ;

static Cell* nextNeighbor (Cell* current) {
    int numberOfNeighbors = current->getNumberOfNeighborsNotVisited();
    if (numberOfNeighbors == 0) {
        return nullptr;
    }
    Cell* listCell[numberOfNeighbors];
    current->getAbsoluteNeighborsNotVisited(listCell);
    int random = rand() % numberOfNeighbors;
    std::cout << "number of neighbors : " << numberOfNeighbors << std::endl;
    std::cout << "random : " << random << std::endl;
    return listCell[random];
}

void algo_cours(Maze* maze, int width, int height, bool perfect) {
    maze->setWidthHeight(width, height);
    struct coordinate cellHistory[width * height];
    Cell *cellStart = maze->getCell(3, 2);
    nextNeighbor(cellStart);
    int numberOfNeighbors = cellStart->getNumberOfNeighbors();
    Cell* currentNeighbor[numberOfNeighbors];
    cellStart->getAbsoluteNeighbors(currentNeighbor);

}
