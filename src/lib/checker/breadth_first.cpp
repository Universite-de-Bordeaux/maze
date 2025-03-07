#include "breadth_first.hpp"

#include "../queue.hpp"
#include "../show.hpp"
#include "../var.hpp"

// Structure pour stocker l'historique des positions visitées et leur parent
struct positionHistory {
    int x;
    int y;
    positionHistory *parent;
};

void checker_breadth_first(const Maze *maze, const bool perfect, Show *show,
                           bool *isValid, bool *isPerfect) {
    // Initialisation des structures de données
    Queue queue;
    Queue queueFree;  // File d'attente pour gérer la libération de la mémoire
    bool imperfect = false;
    refreshShow(show);

    // Initialisation du point de départ
    Cell *start = maze->getCell(0, 0);
    positionHistory startHistory = {0, 0, nullptr};
    queue.push(&startHistory);
    start->setStatus(MAZE_STATUS_VISITED);
    start->setAlreadyVisited(true);

    while (!queue.empty()) {
        // Extraction de l'élément devant la file d'attente
        auto *current = static_cast<positionHistory *>(queue.front());
        queue.pop();
        const int x = current->x;
        const int y = current->y;
        Cell *cell = maze->getCell(x, y);

        // Vérification si le labyrinthe n'est pas parfait
        if (perfect && cell->getAbsoluteNumberOfNeighbors() -
                               cell->getAbsoluteNumberOfNeighborsNotVisited() >=
                           2) {
            cell->setStatus(MAZE_STATUS_TOO_MANY_NEIGHBORS);
            imperfect = true;
        }

        // Vérification des voisins non visités
        if (cell->getAbsoluteNumberOfNeighborsNotVisited() == 0) {
            if (cell->getAbsoluteNumberOfNeighbors() -
                    cell->getAbsoluteNumberOfNeighborsNotVisited() <
                2) {
                cell->setStatus(MAZE_STATUS_HOPELESS);
            }
            refreshShow(show, 1, &cell, true);
        } else {
            refreshShow(show, 1, &cell, false);
        }

        // Exploration des voisins
        for (int i = 0; i < 4; i++) {
            Cell *neighbor = cell->getNeighbor(i);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                auto *next = new positionHistory;  // Création d'un nouvel
                                                   // élément d'historique
                next->x = neighbor->getX();
                next->y = neighbor->getY();
                next->parent = current;
                queue.push(next);
                queueFree.push(next);
                neighbor->setStatus(MAZE_STATUS_VISITED);
                neighbor->setAlreadyVisited(true);
            }
        }
    }

    refreshShow(show);

    // Vérification si toutes les cellules ont été visitées
    for (int i = 0; i < maze->getWidth(); i++) {
        for (int j = 0; j < maze->getHeight(); j++) {
            const Cell *cell = maze->getCell(i, j);
            if (!cell->isAlreadyVisited()) {
                if (isValid != nullptr) *isValid = false;
                // Libération de la mémoire allouée dynamiquement
                while (!queueFree.empty()) {
                    const auto *temp =
                        static_cast<positionHistory *>(queueFree.front());
                    if (temp != &startHistory) delete temp;
                    queueFree.pop();
                }
                return;
            }
        }
    }

    if (isValid != nullptr) *isValid = true;  // Le labyrinthe est valide.

    // Vérification si le labyrinthe est parfait
    if (perfect) {
        if (!imperfect) {
            if (isPerfect != nullptr) *isPerfect = true;
        } else {
            if (isPerfect != nullptr) *isPerfect = false;
        }
    }

    // Libération de la mémoire allouée dynamiquement
    while (!queueFree.empty()) {
        const auto *temp = static_cast<positionHistory *>(queueFree.front());
        if (temp != &startHistory) delete temp;
        queueFree.pop();
    }
}