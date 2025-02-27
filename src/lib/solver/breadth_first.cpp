#include "breadth_first.hpp"

#include "../queue.hpp"
#include "../show.hpp"
#include "../stack.hpp"
#include "../var.hpp"

// Structure pour stocker l'histoire des positions et les liens entre les nœuds
struct positionHistory {
    int x;
    int y;
    positionHistory *parent;  // Pointeur vers le nœud parent
};

bool solver_breadth_first(const Maze *maze, Show *show) {
    // Vérification si les cellules de départ ou d'arrivée sont nulles
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }

    refreshShow(show);

    positionHistory startHistory = {maze->getStartX(), maze->getStartY(),
                                    nullptr};

    Queue queue;
    Queue queueFree;  // File d'attente pour la libération de la mémoire
    Stack stack;
    Stack stackFree;  // Stack pour gérer la libération des éléments

    queue.push(&startHistory);
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    maze->getStartCell()->setAlreadyVisited(true);

    while (!queue.empty()) {
        auto *current = static_cast<positionHistory *>(queue.front());
        queue.pop();

        stack.push(current);
        stackFree.push(current);

        const int x = current->x;
        const int y = current->y;

        Cell *cell = maze->getCell(x, y);

        if (cell != nullptr) {
            refreshShow(show, 1, &cell, false);
        }

        // Compteur pour les cellules sans issue
        int count = 0;

        // Parcours des 4 voisins (nord, est, sud, ouest)
        for (int i = 0; i < 4; i++) {
            Cell *neighbor = cell->getNeighbor(i);

            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                auto *next = new positionHistory();
                next->x = neighbor->getX();
                next->y = neighbor->getY();
                next->parent = current;

                queue.push(next);
                queueFree.push(next);

                neighbor->setStatus(MAZE_STATUS_VISITED);
                neighbor->setAlreadyVisited(true);

                // Vérification si le voisin est la sortie
                if (neighbor->getX() == maze->getEndX() &&
                    neighbor->getY() == maze->getEndY()) {
                    neighbor->setStatus(MAZE_STATUS_WAY_OUT);

                    refreshShow(show, 1, &neighbor, true);

                    // Retour arrière pour retrouver le chemin
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
                    while (!queueFree.empty()) {
                        const auto *temp =
                            static_cast<positionHistory *>(queueFree.front());
                        if (temp != &startHistory) {
                            delete temp;
                        }
                        queueFree.pop();
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
    while (!queueFree.empty()) {
        const auto *temp = static_cast<positionHistory *>(queueFree.front());
        if (temp != &startHistory) {
            delete temp;
        }
        queueFree.pop();
    }

    return false;
}