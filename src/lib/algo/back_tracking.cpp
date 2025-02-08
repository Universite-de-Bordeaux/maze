#include "back_tracking.hpp"

#include <iostream>

#include "../show.hpp"
#include "../stack.hpp"

static int numberRelativeNeighbors(Maze* maze, int width, int height,
                                   int currentX, int currentY,
                                   const int DIRECTIONS[4][2],
                                   Cell* currentCell, Show* show) {
    int numberOfNeighbors = 0;
    for (int i = 0; i < 4; i++) {
        int x = currentX + DIRECTIONS[i][0];
        int y = currentY + DIRECTIONS[i][1];
        Cell* cell = maze->getCell(x, y);
        if (x >= 0 && x < width && y >= 0 && y < height &&
            cell->isAlreadyVisited() == false) {
            numberOfNeighbors++;
            currentCell->setStatus(MAZE_STATUS_VISITED);
            cell->setStatus(MAZE_STATUS_TOO_MANY_NEIGHBORS);
            refreshShow(show, 1, &cell);
        }
    }
    return numberOfNeighbors;
}

static Cell* nextNeighbor(Cell* current) {
    int numberOfNeighbors = current->getAbsoluteNumberOfNeighborsNotVisited();
    if (numberOfNeighbors == 0) {
        return nullptr;  // Aucun voisin non visité
    }

    Cell* listCell[numberOfNeighbors];
    current->getAbsoluteNeighborsNotVisited(
        listCell);  // Récupérer les voisins non visités
    int random = rand() % numberOfNeighbors;
    return listCell[random];  // Retourner un voisin non visité au hasard
}

// Fonction principale de l'algorithme (back_tracking)
void algo_back_tracking(Maze* maze, int width, int height, bool perfect,
                        double probability, Show* show) {
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    Stack stack = Stack();

    Cell* cellStart = maze->getCell(0, 0);
    cellStart->setAlreadyVisited(true);

    // cellule depart
    coordinate startCoord = {0, 0};
    stack.push(&startCoord);

    while (!stack.empty()) {
        // cellule curent a patire de cellHistory
        coordinate* currentCoord = (coordinate*)stack.top();
        int currentX = currentCoord->x;
        int currentY = currentCoord->y;
        Cell* currentCell = maze->getCell(currentX, currentY);
        currentCell->setStatus(MAZE_STATUS_CURRENT);

        Cell* neighbor = nextNeighbor(currentCell);

        if (neighbor != nullptr) {
            int numberOfNeighbors =
                currentCell->getAbsoluteNumberOfNeighborsNotVisited();
            Cell* listCell[numberOfNeighbors];
            currentCell->getAbsoluteNeighborsNotVisited(listCell);

            for (int i = 0; i < numberOfNeighbors; i++) {
                if (!(listCell[i]->getX() == neighbor->getX() &&
                      listCell[i]->getY() == neighbor->getY())) {
                    maze->addWall(currentCell, listCell[i]);
                }
            }

            neighbor->setAlreadyVisited(true);

            // ajout à historique
            coordinate newCoord;
            newCoord.x = neighbor->getX();
            newCoord.y = neighbor->getY();
            coordinate* newCoordPtr = new coordinate;
            newCoordPtr->x = newCoord.x;
            newCoordPtr->y = newCoord.y;
            stack.push(newCoordPtr);
            currentCell->setStatus(MAZE_STATUS_VISITED);
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            refreshShow(show, 1, &neighbor);
        } else {
            int numberOfNeighbors =
                numberRelativeNeighbors(maze, width, height, currentX, currentY,
                                        DIRECTIONS, currentCell, show);
            if (numberOfNeighbors <= 0) {
                currentCell->setStatus(MAZE_STATUS_HOPELESS);
                stack.pop();
                if (!perfect &&
                    (double)(rand() % 10000) < probability * (double)10000) {
                    int randomIndex = rand() % 4;
                    for (int i = 0; i < 4; i++) {
                        int index = (randomIndex + i) % 4;
                        int x = currentX + DIRECTIONS[index][0];
                        int y = currentY + DIRECTIONS[index][1];
                        if (x >= 0 && x < width && y >= 0 && y < height) {
                            Cell* neighborCell = maze->getCell(x, y);
                            if (neighborCell->isAlreadyVisited()) {
                                maze->removeWall(currentCell, neighborCell);
                                break;
                            }
                        }
                    }
                }
            } else {
                coordinate neighbors[numberOfNeighbors];
                int index = 0;
                for (int i = 0; i < 4; i++) {
                    int x = currentX + DIRECTIONS[i][0];
                    int y = currentY + DIRECTIONS[i][1];
                    if (x >= 0 && x < width && y >= 0 && y < height &&
                        maze->getCell(x, y)->isAlreadyVisited() == false) {
                        neighbors[index].x = x;
                        neighbors[index].y = y;
                        index++;
                    }
                }
                maze->removeWall(currentCell,
                                 maze->getCell(neighbors[0].x, neighbors[0].y));
                coordinate* newCoordPtr = new coordinate;
                newCoordPtr->x = neighbors[0].x;
                newCoordPtr->y = neighbors[0].y;
                stack.push(newCoordPtr);
                currentCell->setStatus(MAZE_STATUS_VISITED);
                maze->getCell(neighbors[0].x, neighbors[0].y)
                    ->setStatus(MAZE_STATUS_CURRENT);
                Cell* showCell = maze->getCell(neighbors[0].x, neighbors[0].y);
                refreshShow(show, 1, &showCell);
            }
        }
        refreshShow(show, 1, &currentCell);
    }
    maze->clearMaze();
}
