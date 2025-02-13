#include "back_tracking.hpp"

#include "../show.hpp"
#include "../stack.hpp"

static int numberRelativeNeighbors(const Maze* maze, const int currentX,
                                   const int currentY) {
    int numberOfNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != j && (i == 0 || j == 0)) {
                const int x = currentX + i;
                const int y = currentY + j;
                if (x >= 0 && x < maze->getWidth() && y >= 0 &&
                    y < maze->getHeight() &&
                    maze->getCell(x, y)->isAlreadyVisited() == false) {
                    numberOfNeighbors++;
                }
            }
        }
    }
    return numberOfNeighbors;
}

static Cell* nextNeighbor(const Cell* current, Rand* rand) {
    const int numberOfNeighbors =
        current->getAbsoluteNumberOfNeighborsNotVisited();
    if (numberOfNeighbors == 0) return nullptr;
    Cell* listCell[numberOfNeighbors];
    current->getAbsoluteNeighborsNotVisited(
        listCell);  // Récupérer les voisins non visités
    const int random = rand->get(0, numberOfNeighbors - 1);
    return listCell[random];  // Retourner un voisin non visité au hasard
}

// Fonction principale de l'algorithme (back_tracking)
void algo_back_tracking(Maze* maze, const int width, const int height,
                        const bool perfect, const double probability,
                        Show* show) {
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    auto stack = Stack();

    Cell* cellStart = maze->getCell(0, 0);
    cellStart->setAlreadyVisited(true);

    // cellule depart
    coordinate startCoord = {0, 0};
    stack.push(&startCoord);

    while (!stack.empty()) {
        // cellule curent a partir de cellHistory
        const auto* currentCoord = static_cast<coordinate*>(stack.top());
        const int currentX = currentCoord->x;
        const int currentY = currentCoord->y;
        Cell* currentCell = maze->getCell(currentX, currentY);
        currentCell->setStatus(MAZE_STATUS_CURRENT);

        Cell* neighbor = nextNeighbor(currentCell, maze->getRand());

        if (neighbor != nullptr) {
            const int numberOfNeighbors =
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
            coordinate newCoord{};
            newCoord.x = neighbor->getX();
            newCoord.y = neighbor->getY();
            auto* newCoordPtr = new coordinate;
            newCoordPtr->x = newCoord.x;
            newCoordPtr->y = newCoord.y;
            stack.push(newCoordPtr);
            currentCell->setStatus(MAZE_STATUS_VISITED);
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            Cell* showCells[2] = {currentCell, neighbor};
            refreshShow(show, 2, showCells, false);
        } else {
            const int numberOfNeighbors =
                numberRelativeNeighbors(maze, currentX, currentY);
            if (numberOfNeighbors <= 0) {
                currentCell->setStatus(MAZE_STATUS_HOPELESS);
                stack.pop();
                if (!perfect && maze->getRand()->get(probability)) {
                    const int randomIndex = maze->getRand()->get(0, 3);
                    for (int i = 0; i < 4; i++) {
                        const int index = (randomIndex + i) % 4;
                        const int x = currentX + DIRECTIONS[index][0];
                        const int y = currentY + DIRECTIONS[index][1];
                        if (x >= 0 && x < width && y >= 0 && y < height) {
                            const Cell* neighborCell = maze->getCell(x, y);
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
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (i != j && (i == 0 || j == 0)) {
                            const int x = currentX + i;
                            const int y = currentY + j;
                            if (x >= 0 && x < width && y >= 0 && y < height &&
                                maze->getCell(x, y)->isAlreadyVisited() ==
                                    false) {
                                neighbors[index].x = x;
                                neighbors[index].y = y;
                                index++;
                            }
                        }
                    }
                }
                maze->removeWall(currentCell,
                                 maze->getCell(neighbors[0].x, neighbors[0].y));
                auto* newCoordPtr = new coordinate;
                newCoordPtr->x = neighbors[0].x;
                newCoordPtr->y = neighbors[0].y;
                stack.push(newCoordPtr);
                currentCell->setStatus(MAZE_STATUS_VISITED);
                maze->getCell(neighbors[0].x, neighbors[0].y)
                    ->setStatus(MAZE_STATUS_CURRENT);
            }
            refreshShow(show, 1, &currentCell, true);
        }
    }
    refreshShow(show);
}
