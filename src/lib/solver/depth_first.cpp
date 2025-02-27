#include "depth_first.hpp"

#include "../show.hpp"
#include "../stack.hpp"
#include "../var.hpp"

// Structure pour stocker l'histoire des positions, la direction et les liens
// entre les nœuds
struct positionHistory {
    int x;          // Coordonnée x
    int y;          // Coordonnée y
    int direction;  // Direction actuelle (0 = nord, 1 = est, 2 = sud, 3 =
                    // ouest)
    positionHistory *parent;  // Pointeur vers le nœud parent
};

bool solver_depth_first(const Maze *maze, Show *show, const bool left) {
    Stack stack;
    auto stackFree = Stack();  // Stack pour gérer la libération de la mémoire

    // Vérification si les cellules de départ ou d'arrivée sont nulles
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }

    refreshShow(show);

    positionHistory startHistory = {maze->getStartX(), maze->getStartY(), 0,
                                    nullptr};

    stack.push(&startHistory);

    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    maze->getStartCell()->setAlreadyVisited(true);

    while (!stack.empty()) {
        auto *current = static_cast<positionHistory *>(stack.top());
        stack.pop();

        const int x = current->x;
        const int y = current->y;

        Cell *cell = maze->getCell(x, y);

        if (cell != nullptr) {
            refreshShow(show, 1, &cell, false);
        }

        // Compteur pour les cellules sans issue
        int count = 0;

        // Parcours des 4 voisins dans un ordre déterminé par la direction et le
        // paramètre left
        for (int i = 0; i < 4; i++) {
            // Calcul de l'index du voisin en fonction de la direction actuelle
            // et du paramètre left
            const int index = (current->direction + (left ? i : i + 2)) % 4;

            Cell *neighbor = cell->getNeighbor(index);

            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                auto *next = new positionHistory();
                next->x = neighbor->getX();
                next->y = neighbor->getY();
                next->direction = (index + 2) % 4;
                next->parent = current;

                stack.push(next);
                stackFree.push(next);

                neighbor->setStatus(MAZE_STATUS_VISITED);
                neighbor->setAlreadyVisited(true);

                // Vérification si le voisin est la sortie
                if (neighbor->getX() == maze->getEndX() &&
                    neighbor->getY() == maze->getEndY()) {
                    neighbor->setStatus(MAZE_STATUS_WAY_OUT);

                    refreshShow(show, 1, &neighbor, true);

                    // Retour arrière pour tracer le chemin
                    const auto *currentPath = next;
                    while (currentPath != nullptr) {
                        Cell *cellTop =
                            maze->getCell(currentPath->x, currentPath->y);
                        if (cellTop != nullptr) {
                            cellTop->setStatus(MAZE_STATUS_WAY_OUT);
                            refreshShow(show, 1, &cellTop, false);
                        }
                        currentPath = currentPath->parent;
                    }

                    refreshShow(show);

                    // Libération de la mémoire
                    while (!stackFree.empty()) {
                        const auto *temp =
                            static_cast<positionHistory *>(stackFree.top());
                        if (temp != &startHistory) {
                            delete temp;
                        }
                        stackFree.pop();
                    }

                    return true;
                }
            } else {
                count++;
            }
        }

        // Si tous les voisins sont visités ou invalides
        if (count == 4) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell, true);
        }
    }

    refreshShow(show);

    // Libération de la mémoire
    while (!stackFree.empty()) {
        const auto *temp = static_cast<positionHistory *>(stackFree.top());
        if (temp != &startHistory) {
            delete temp;
        }
        stackFree.pop();
    }

    return false;
}