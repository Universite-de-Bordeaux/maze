#include "back_tracking.hpp"

#include "../show.hpp"
#include "../stack.hpp"

/**
 * @brief Calcule le nombre relatif de voisins non visités d'une cellule
 * @param maze Le labyrinthe
 * @param currentX La coordonnée X de la cellule courante
 * @param currentY La coordonnée Y de la cellule courante
 * @return Le nombre relatif de voisins non visités
 */
static int numberRelativeNeighbors(const Maze* maze, const int currentX,
                                   const int currentY) {
    int numberOfNeighbors = 0;
    // On vérifie tous les voisins (haut, bas, gauche, droit)
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // On exclut la diagonale
            if (i != j && (i == 0 || j == 0)) {
                const int x = currentX + i;
                const int y = currentY + j;
                // Si le voisin est dans les bornes et non visité
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

/**
 * @brief Retourne un voisin non visité au hasard
 * @param current La cellule courante
 * @param rand Le générateur de nombres aléatoires
 * @return Un pointeur vers la cellule voisine non visitée
 */
static Cell* nextNeighbor(const Cell* current, Rand* rand) {
    const int numberOfNeighbors =
        current->getAbsoluteNumberOfNeighborsNotVisited();
    if (numberOfNeighbors == 0) return nullptr;
    // On récupère la liste des voisins non visités
    Cell* listCell[numberOfNeighbors];
    current->getAbsoluteNeighborsNotVisited(listCell);
    // On choisit un voisin au hasard
    const int random = rand->get(0, numberOfNeighbors - 1);
    return listCell[random];
}

void algo_back_tracking(Maze* maze, const int width, const int height,
                        const bool perfect, const double probability,
                        Show* show) {
    // Initialisation du labyrinthe
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    // Structure de données pour stocker l'historique des cellules visitées
    auto stack = Stack();
    auto stackFree = Stack();

    // Cellule de départ
    Cell* cellStart = maze->getCell(0, 0);
    cellStart->setAlreadyVisited(true);
    coordinate startCoord = {0, 0};
    stack.push(&startCoord);

    while (!stack.empty()) {
        // Récupération de la cellule courante
        const auto* currentCoord = static_cast<coordinate*>(stack.top());
        const int currentX = currentCoord->x;
        const int currentY = currentCoord->y;
        Cell* currentCell = maze->getCell(currentX, currentY);
        currentCell->setStatus(MAZE_STATUS_CURRENT);

        // Recherche d'un voisin non visité
        Cell* neighbor = nextNeighbor(currentCell, maze->getRand());

        if (neighbor != nullptr) {
            // Si un voisin non visité est trouvé
            const int numberOfNeighbors =
                currentCell->getAbsoluteNumberOfNeighborsNotVisited();
            Cell* listCell[numberOfNeighbors];
            currentCell->getAbsoluteNeighborsNotVisited(listCell);

            // On bloque tous les autres voisins sauf le voisin choisi
            for (int i = 0; i < numberOfNeighbors; i++) {
                if (!(listCell[i]->getX() == neighbor->getX() &&
                      listCell[i]->getY() == neighbor->getY())) {
                    maze->addWall(currentCell, listCell[i]);
                }
            }

            // On marque le voisin comme visité et on l'ajoute à l'historique
            neighbor->setAlreadyVisited(true);
            coordinate newCoord{};
            newCoord.x = neighbor->getX();
            newCoord.y = neighbor->getY();
            auto* newCoordPtr = new coordinate(newCoord);
            stack.push(newCoordPtr);
            stackFree.push(newCoordPtr);
            currentCell->setStatus(MAZE_STATUS_VISITED);
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            // Mise à jour de l'affichage
            Cell* showCells[2] = {currentCell, neighbor};
            refreshShow(show, 2, showCells, false);
        } else {
            // Si aucun voisin non visité n'est trouvé
            const int numberOfNeighbors =
                numberRelativeNeighbors(maze, currentX, currentY);
            if (numberOfNeighbors <= 0) {
                // Cas où aucun chemin n'est possible : on met le statut
                // de la cellule à désespéré
                currentCell->setStatus(MAZE_STATUS_HOPELESS);
                stack.pop();
                // Pour les labyrinthes non parfaits, on a une probabilité de
                // créer un passage supplémentaire
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
                // Si des voisins non visités existent, on crée un passage
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
                // On crée un passage avec le premier voisin trouvé
                maze->removeWall(currentCell,
                                 maze->getCell(neighbors[0].x, neighbors[0].y));
                auto* newCoordPtr = new coordinate(neighbors[0]);
                stack.push(newCoordPtr);
                stackFree.push(newCoordPtr);
                currentCell->setStatus(MAZE_STATUS_VISITED);
                maze->getCell(neighbors[0].x, neighbors[0].y)
                    ->setStatus(MAZE_STATUS_CURRENT);
            }
            // Mise à jour de l'affichage
            refreshShow(show, 1, &currentCell, true);
        }
    }
    // Mise à jour finale de l'affichage
    refreshShow(show);
    // Nettoyage de la mémoire allouée dynamiquement
    while (!stackFree.empty()) {
        const auto* temp = static_cast<coordinate*>(stackFree.top());
        delete temp;
        stackFree.pop();
    }
    maze->clearMaze();
}
