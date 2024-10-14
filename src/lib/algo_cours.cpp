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
    int numberOfNeighbors = current->getAbsoluteNumberOfNeighborsNotVisited();
    if (numberOfNeighbors == 0) {
        return nullptr;  // Aucun voisin non visité
    }

    Cell* listCell[numberOfNeighbors];
    current->getAbsoluteNeighborsNotVisited(listCell);  // Récupérer les voisins non visités
    int random = rand() % numberOfNeighbors;
    return listCell[random];  // Retourner un voisin non visité au hasard
}

// Fonction principale de l'algorithme (backtracking)
void algo_cours(Maze* maze, int width, int height, bool perfect, Show* show) {
    maze->setWidthHeight(width, height);

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
        Cell* currentCell = maze->getCell(currentX, currentY);

        Cell* neighbor = nextNeighbor(currentCell);

        if (neighbor != nullptr) {
            int numberOfNeighbors = currentCell->getAbsoluteNumberOfNeighborsNotVisited();
            Cell* listCell[numberOfNeighbors];
            currentCell->getAbsoluteNeighborsNotVisited(listCell);

            for (int i = 0; i < numberOfNeighbors; i++) {
                if (!(listCell[i]->getX() == neighbor->getX() && listCell[i]->getY() == neighbor->getY())) {
                    // std::cout << "currentX : " << currentX << " currentY : " << currentY << std::endl;
                    // std::cout << "listCell[i]->getX() : " << listCell[i]->getX() << " listCell[i]->getY() : " << listCell[i]->getY() << std::endl;
                    if (listCell[i]->getX() == currentX && listCell[i]->getY() == currentY - 1) {
                        maze->addWall(currentX, listCell[i]->getY(), true);
                    } else if (listCell[i]->getX() == currentX && listCell[i]->getY() == currentY + 1) {
                        maze->addWall(currentX, currentY, true);
                    } else if (listCell[i]->getX() == currentX - 1 && listCell[i]->getY() == currentY) {
                        maze->addWall(listCell[i]->getX(), currentY, false);
                    } else if (listCell[i]->getX() == currentX + 1 && listCell[i]->getY() == currentY) {
                        maze->addWall(currentX, currentY, false);
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
            if (currentCell->getX() > 0 && maze->getCell(currentX - 1, currentY)->isAlreadyVisited() == false) {
                coordinate newCoord;
                newCoord.x = currentX - 1;
                newCoord.y = currentY;
                maze->removeWall(newCoord.x, newCoord.y, false);
                cellHistory[historyIndex] = newCoord;
                maze->getCell(newCoord.x, newCoord.y)->setAlreadyVisited(true);
                historyIndex++;
                updateShowLive(show, maze, false);
            } else if (currentCell->getY() > 0 && maze->getCell(currentX, currentY - 1)->isAlreadyVisited() == false) {
                coordinate newCoord;
                newCoord.x = currentX;
                newCoord.y = currentY - 1;
                maze->removeWall(newCoord.x, newCoord.y, true);
                cellHistory[historyIndex] = newCoord;
                maze->getCell(newCoord.x, newCoord.y)->setAlreadyVisited(true);
                historyIndex++;
                updateShowLive(show, maze, false);
            } else if (currentCell->getX() < width - 1 && maze->getCell(currentX + 1, currentY)->isAlreadyVisited() == false) {
                coordinate newCoord;
                newCoord.x = currentX + 1;
                newCoord.y = currentY;
                maze->removeWall(currentX, currentY, false);
                cellHistory[historyIndex] = newCoord;
                maze->getCell(newCoord.x, newCoord.y)->setAlreadyVisited(true);
                historyIndex++;
                updateShowLive(show, maze, false);
            } else if (currentCell->getY() < height - 1 && maze->getCell(currentX, currentY + 1)->isAlreadyVisited() == false) {
                coordinate newCoord;
                newCoord.x = currentX;
                newCoord.y = currentY + 1;
                maze->removeWall(currentX, currentY, true);
                cellHistory[historyIndex] = newCoord;
                maze->getCell(newCoord.x, newCoord.y)->setAlreadyVisited(true);
                historyIndex++;
                updateShowLive(show, maze, false);
            } else {
                historyIndex--;
            }
        }
        updateShowLive(show, maze, true);
    }
    maze -> clearMaze();
}
