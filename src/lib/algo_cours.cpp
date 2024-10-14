#include "algo_cours.hpp"
#include "var.hpp"
#include <iostream>

struct coordinate{
    int x;
    int y;
} ;

/*static Cell* nextNeighbor (Cell* current) {
    int numberOfNeighbors = current->getAbsoluteNumberOfNeighborsNotVisited();
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
    struct coordinate cellHistory[width * height];
    Cell *cellStart = maze->getCell(3, 2);
    nextNeighbor(cellStart);
    int numberOfNeighbors = cellStart->getAbsoluteNumberOfNeighbors();
    Cell* currentNeighbor[numberOfNeighbors];
    cellStart->getAbsoluteNeighbors(currentNeighbor);

    }*/


static Cell* nextNeighbor(Cell* current) {
    int numberOfNeighbors = current->getRelativeNumberOfNeighborsNotVisited();
    if (numberOfNeighbors == 0) {
        std::cout << "x : " << current->getX() << " y : " << current->getY() << " numberOfNeighbors : " << numberOfNeighbors << std::endl;
        return nullptr;  // Aucun voisin non visité
    }
    Cell* listCell[numberOfNeighbors];
    current->getRelativeNeighborsNotVisited(listCell);  // Récupérer les voisins non visités
    
    int random = rand() % numberOfNeighbors;
    std::cout << "x : " << current->getX() << " y : " << current->getY() << " numberOfNeighbors : " << numberOfNeighbors << " random : " << random << std::endl;
    return listCell[random];  // Retourner un voisin non visité au hasard
}

// Fonction principale de l'algorithme (backtracking)
void algo_cours(Maze* maze, int width, int height, bool perfect, Show* show) {
    srand(time(0));

    struct coordinate cellHistory[width * height];
    int historyIndex = 0;

    Cell* cellStart = maze->getCell(0, 0);
    cellStart->setAlreadyVisited(true);

    //cellule depart
    cellHistory[historyIndex].x = 0;
    cellHistory[historyIndex].y = 0;
    historyIndex++;

    while (historyIndex > 0) {
        //cellule curent a patire de cellHistory
        int currentX = cellHistory[historyIndex - 1].x;
        int currentY = cellHistory[historyIndex - 1].y;
        std::cout << "historyIndex : " << historyIndex << std::endl;
        for (int i = 0; i < historyIndex; i++) {
            std::cout << "x : " << cellHistory[i].x << " y : " << cellHistory[i].y << std::endl;
        }
        std::cout << "----------------A" << std::endl;
        Cell* currentCell = maze->getCell(currentX, currentY);
        std::cout << "----------------B" << std::endl;

        Cell* neighbor = nextNeighbor(currentCell);

        if (neighbor != nullptr) {
            int numberOfNeighbors = currentCell->getRelativeNumberOfNeighborsNotVisited();
            Cell* listCell[numberOfNeighbors];
            currentCell->getRelativeNeighborsNotVisited(listCell);
            for (int i = 0; i < numberOfNeighbors; i++) {
                if (!(listCell[i]->getX() == neighbor->getX() && listCell[i]->getY() == neighbor->getY())) {
                    std::cout << "currentX : " << currentX << " currentY : " << currentY << std::endl;
                    std::cout << "listCell[i]->getX() : " << listCell[i]->getX() << " listCell[i]->getY() : " << listCell[i]->getY() << std::endl;
                    if (listCell[i]->getX() == currentX && listCell[i]->getY() == currentY - 1) {
                        if (currentCell->isNeighbor(MAZE_CELL_TOP)) {
                            maze->addWall(currentX, listCell[i]->getY(), true);
                        } else {
                            maze->removeWall(currentX, listCell[i]->getY(), true);
                            std::cout << "wall removed x : " << currentX << " y : " << listCell[i]->getY() << std::endl;
                        }
                    } else if (listCell[i]->getX() == currentX && listCell[i]->getY() == currentY + 1) {
                        if (currentCell->isNeighbor(MAZE_CELL_BOTTOM)) {
                            maze->addWall(currentX, currentY, true);
                        } else {
                            maze->removeWall(currentX, currentY, true);
                            std::cout << "wall removed x : " << currentX << " y : " << currentY << std::endl;
                        }
                    } else if (listCell[i]->getX() == currentX - 1 && listCell[i]->getY() == currentY) {
                        if (currentCell->isNeighbor(MAZE_CELL_LEFT)) {
                            maze->addWall(listCell[i]->getX(), currentY, false);
                        } else {
                            maze->removeWall(listCell[i]->getX(), currentY, false);
                            std::cout << "wall removed x : " << listCell[i]->getX() << " y : " << currentY << std::endl;
                        }
                    } else if (listCell[i]->getX() == currentX + 1 && listCell[i]->getY() == currentY) {
                        if (currentCell->isNeighbor(MAZE_CELL_RIGHT)) {
                            maze->addWall(currentX, currentY, false);
                        } else {
                            maze->removeWall(currentX, currentY, false);
                            std::cout << "wall removed x : " << currentX << " y : " << currentY << std::endl;
                        }
                    }
                    // std::cout << "wall added" << std::endl;
                }
            }

            neighbor->setAlreadyVisited(true);

            //ajout à histoorique
            coordinate newCoord;
            newCoord.x = neighbor->getX();
            newCoord.y = neighbor->getY();
            cellHistory[historyIndex] = newCoord;
            historyIndex++;

        } else {
            historyIndex--;
        }
    }
}
