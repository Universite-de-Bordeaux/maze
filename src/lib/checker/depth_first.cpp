#include "depth_first.hpp"

#include "../cell.hpp"
#include "../maze.hpp"
#include "../stack.hpp"

// Structure pour stocker l'historique des positions visitées, la direction et
// leur parent
struct positionHistory {
    int x;
    int y;
    int direction;
    positionHistory *parent;
};

// Fonction principale pour vérifier le labyrinthe en utilisant un parcours en
// profondeur (DFS)
void checker_depth_first(const Maze *maze, const bool perfect, const bool left,
                         Show *show, bool *isValid, bool *isPerfect) {
    Stack stack;      // Pile pour gérer le parcours DFS
    Stack stackFree;  // Pile pour gérer la libération de la mémoire
    bool imperfect =
        false;  // Drapeau pour vérifier si le labyrinthe est parfait

    // Vérification des cellules de départ et d'arrivée
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return;
    }

    refreshShow(show);  // Rafraîchissement initial de l'affichage

    // Initialisation du point de départ
    Cell *start = maze->getCell(0, 0);
    positionHistory startHistory = {0, 0, 0, nullptr};
    stack.push(&startHistory);  // Ajout de la position initiale à la pile
    start->setStatus(
        MAZE_STATUS_VISITED);  // Marquage de la cellule de départ comme visitée
    start->setAlreadyVisited(true);

    // Parcours en profondeur (DFS)
    while (!stack.empty()) {
        // Extraction de l'élément au sommet de la pile
        auto *current = static_cast<positionHistory *>(stack.top());
        stack.pop();
        const int x = current->x;
        const int y = current->y;
        Cell *cell = maze->getCell(x, y);

        // Vérification si le labyrinthe n'est pas parfait
        if (cell != nullptr && perfect &&
            cell->getAbsoluteNumberOfNeighbors() -
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
            refreshShow(show, 1, &cell,
                        true);  // Mise à jour de l'affichage pour cette cellule
        } else {
            refreshShow(show, 1, &cell,
                        false);  // Mise à jour normale de l'affichage
        }

        // Exploration des voisins
        for (int i = 0; i < 4; i++) {
            // Indice du voisin ajusté en fonction de la direction et du
            // paramètre 'left'
            const int index = (current->direction + (left ? i : i + 2)) % 4;
            Cell *neighbor = cell->getNeighbor(index);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                auto *next = new positionHistory{
                    // Création d'un nouvel élément d'historique
                    neighbor->getX(), neighbor->getY(), index, current};
                stack.push(next);      // Ajout à la pile principale
                stackFree.push(next);  // Ajout à la pile pour la libération
                neighbor->setStatus(
                    MAZE_STATUS_VISITED);  // Marquage comme visitée
                neighbor->setAlreadyVisited(true);
            }
        }
    }

    refreshShow(show);  // Rafraîchissement final de l'affichage

    // Vérification si toutes les cellules ont été visitées
    for (int i = 0; i < maze->getWidth(); i++) {
        for (int j = 0; j < maze->getHeight(); j++) {
            const Cell *cell = maze->getCell(i, j);
            if (!cell->isAlreadyVisited()) {
                if (isValid != nullptr) *isValid = false;
                // Libération de la mémoire allouée dynamiquement
                while (!stackFree.empty()) {
                    const auto *temp =
                        static_cast<positionHistory *>(stackFree.top());
                    if (temp != &startHistory) delete temp;
                    stackFree.pop();
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
    while (!stackFree.empty()) {
        const auto *temp = static_cast<positionHistory *>(stackFree.top());
        if (temp != &startHistory) delete temp;
        stackFree.pop();
    }
}