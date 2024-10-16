#include "algo_cours.hpp"
#include "show.hpp"
#include <iostream>

struct coordinate{
    int x;
    int y;
};

int directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

static int numberRelativeNeighbors(Maze* maze, int width, int height, int currentX, int currentY, int directions[4][2], Cell* currentCell, Show* show) {
    int numberOfNeighbors = 0;
    for (int i = 0; i < 4; i++) {
        int x = currentX + directions[i][0];
        int y = currentY + directions[i][1];
        if (x >= 0 && x < width && y >= 0 && y < height && maze->getCell(x, y)->isAlreadyVisited() == false) {
            numberOfNeighbors++;
            currentCell->setStatus(MAZE_STATUS_VISITED);
            Cell* showCell[1] = {maze->getCell(x, y)};
            updateShowLive(show, maze, 1, showCell);
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
    current->getAbsoluteNeighborsNotVisited(listCell);  // Récupérer les voisins non visités
    int random = rand() % numberOfNeighbors;
    return listCell[random];  // Retourner un voisin non visité au hasard
}

// Fonction principale de l'algorithme (backtracking)
void algo_cours(Maze* maze, int width, int height, bool perfect, Show* show) {
    struct coordinate cellHistory[width * height];
    int historyIndex = 0;

    Cell* cellStart = maze->getCell(0, 0);
    cellStart->setAlreadyVisited(true);

    //cellule depart
    cellHistory[historyIndex].x = 0;
    cellHistory[historyIndex].y = 0;
    historyIndex++;

    while (historyIndex > 0) {
        if (show != nullptr) {
            show->eventHandler();
            show->display();
        }
        //cellule curent a patire de cellHistory
        int currentX = cellHistory[historyIndex - 1].x;
        int currentY = cellHistory[historyIndex - 1].y;
        Cell* currentCell = maze->getCell(currentX, currentY);
        currentCell->setStatus(MAZE_STATUS_CURRENT);
        Cell* showCell[1] = {currentCell};
        updateShowLive(show, maze, 1, showCell);

        Cell* neighbor = nextNeighbor(currentCell);

        if (neighbor != nullptr) {
            int numberOfNeighbors = currentCell->getAbsoluteNumberOfNeighborsNotVisited();
            Cell* listCell[numberOfNeighbors];
            currentCell->getAbsoluteNeighborsNotVisited(listCell);

            for (int i = 0; i < numberOfNeighbors; i++) {
                if (!(listCell[i]->getX() == neighbor->getX() && listCell[i]->getY() == neighbor->getY())) {
                    maze->addWall(currentCell, listCell[i]);
                }
            }

            neighbor->setAlreadyVisited(true);

            //ajout à histoorique
            coordinate newCoord;
            newCoord.x = neighbor->getX();
            newCoord.y = neighbor->getY();
            cellHistory[historyIndex] = newCoord;
            historyIndex++;
            currentCell->setStatus(MAZE_STATUS_VISITED);
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            // updateShowLive(show, maze, true);
            Cell* showCell[2] = {currentCell, neighbor};
            updateShowLive(show, maze, 2, showCell);
        } else {
            int numberOfNeighbors = numberRelativeNeighbors(maze, width, height, currentX, currentY, directions, currentCell, show);
            if (numberOfNeighbors <= 0) {
                currentCell->setStatus(MAZE_STATUS_HOPELESS);
                Cell* showCell[1] = {currentCell};
                updateShowLive(show, maze, 1, showCell);
                historyIndex--;
                // updateShowLive(show, maze, true);
            } else {
                coordinate neighbors[numberOfNeighbors];
                int index = 0;
                for (int i = 0; i < 4; i++) {
                    int x = currentX + directions[i][0];
                    int y = currentY + directions[i][1];
                    if (x >= 0 && x < width && y >= 0 && y < height && maze->getCell(x, y)->isAlreadyVisited() == false) {
                        neighbors[index].x = x;
                        neighbors[index].y = y;
                        index++;
                    }
                }
                maze->removeWall(currentCell, maze->getCell(neighbors[0].x, neighbors[0].y));
                cellHistory[historyIndex] = neighbors[0];
                historyIndex++;
                currentCell->setStatus(MAZE_STATUS_VISITED);
                maze->getCell(neighbors[0].x, neighbors[0].y)->setStatus(MAZE_STATUS_CURRENT);
                // updateShowLive(show, maze);
                Cell* showCell[2] = {currentCell, maze->getCell(neighbors[0].x, neighbors[0].y)};
                updateShowLive(show, maze, 2, showCell);
            }
        }
        updateShowLive(show, maze, 1, &currentCell);
    }
    maze -> clearMaze();
}
