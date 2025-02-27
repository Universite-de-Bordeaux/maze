#include "wall_maker.hpp"

#include "../checker/depth_first.hpp"
#include "../queue.hpp"
#include "../show.hpp"
#include "../solver/breadth_first.hpp"
#include "../stack.hpp"

// Structure représentant un mur avec ses coordonnées et son orientation
struct wall_maker {
    int x;
    int y;
    bool horizontal;
};

/**
 * @brief Compte le nombre de voisins d'un mur
 * @param maze Le labyrinthe
 * @param wall Le mur à analyser
 * @return Le nombre de voisins de le mur
 */
static int getNbNeighbors(const Maze* maze, const wall_maker* wall) {
    int nbNeighbors = 0;
    if (wall->horizontal) {
        // Parcours des voisins pour un mur horizontal
        if (maze->getWall(wall->x - 1, wall->y, true) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x - 1, wall->y, false) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x, wall->y, false) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x - 1, wall->y + 1, false) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr)
            nbNeighbors++;
    } else {
        // Parcours des voisins pour un mur vertical
        if (maze->getWall(wall->x, wall->y - 1, false) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x, wall->y - 1, true) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x, wall->y, true) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x + 1, wall->y - 1, true) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr) nbNeighbors++;
    }
    return nbNeighbors;
}

/**
 * @brief Compte le nombre de voisins non visités d'un mur
 * @param maze Le labyrinthe
 * @param wall Le mur à analyser
 * @return Le nombre de voisins non visités du mur
 */
static int getNbNeighborsNotVisited(const Maze* maze, const wall_maker* wall) {
    int nbNeighborsNotVisited = 0;
    if (wall->horizontal) {
        // Parcours des voisins non visités pour un mur horizontal
        if (maze->getWall(wall->x - 1, wall->y, true) != nullptr &&
            !maze->getWall(wall->x - 1, wall->y, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x - 1, wall->y, false) != nullptr &&
            !maze->getWall(wall->x - 1, wall->y, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y, false) != nullptr &&
            !maze->getWall(wall->x, wall->y, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr &&
            !maze->getWall(wall->x + 1, wall->y, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x - 1, wall->y + 1, false) != nullptr &&
            !maze->getWall(wall->x - 1, wall->y + 1, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr &&
            !maze->getWall(wall->x, wall->y + 1, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
    } else {
        // Parcours des voisins non visités pour un mur vertical
        if (maze->getWall(wall->x, wall->y - 1, false) != nullptr &&
            !maze->getWall(wall->x, wall->y - 1, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y - 1, true) != nullptr &&
            !maze->getWall(wall->x, wall->y - 1, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y, true) != nullptr &&
            !maze->getWall(wall->x, wall->y, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr &&
            !maze->getWall(wall->x, wall->y + 1, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x + 1, wall->y - 1, true) != nullptr &&
            !maze->getWall(wall->x + 1, wall->y - 1, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr &&
            !maze->getWall(wall->x + 1, wall->y, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
    }
    return nbNeighborsNotVisited;
}

/**
 * @brief Récupère les voisins d'un mur
 * @param maze Le labyrinthe
 * @param wall Le mur à analyser
 * @param neighbors Tableau pour stocker les voisins
 */
static void getNeighbors(const Maze* maze, const wall_maker* wall,
                         wall_maker* neighbors) {
    int count = 0;
    if (wall->horizontal) {
        // Récupère les voisins pour un mur horizontal
        if (maze->getWall(wall->x - 1, wall->y, true) != nullptr) {
            neighbors[count] = {wall->x - 1, wall->y, true};
            count++;
        }
        if (maze->getWall(wall->x - 1, wall->y, false) != nullptr) {
            neighbors[count] = {wall->x - 1, wall->y, false};
            count++;
        }
        if (maze->getWall(wall->x, wall->y, false) != nullptr) {
            neighbors[count] = {wall->x, wall->y, false};
            count++;
        }
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr) {
            neighbors[count] = {wall->x + 1, wall->y, true};
            count++;
        }
        if (maze->getWall(wall->x - 1, wall->y + 1, false) != nullptr) {
            neighbors[count] = {wall->x - 1, wall->y + 1, false};
            count++;
        }
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr) {
            neighbors[count] = {wall->x, wall->y + 1, false};
        }
    } else {
        // Récupère les voisins pour un mur vertical
        if (maze->getWall(wall->x, wall->y - 1, false) != nullptr) {
            neighbors[count] = {wall->x, wall->y - 1, false};
            count++;
        }
        if (maze->getWall(wall->x, wall->y - 1, true) != nullptr) {
            neighbors[count] = {wall->x, wall->y - 1, true};
            count++;
        }
        if (maze->getWall(wall->x, wall->y, true) != nullptr) {
            neighbors[count] = {wall->x, wall->y, true};
            count++;
        }
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr) {
            neighbors[count] = {wall->x, wall->y + 1, false};
            count++;
        }
        if (maze->getWall(wall->x + 1, wall->y - 1, true) != nullptr) {
            neighbors[count] = {wall->x + 1, wall->y - 1, true};
            count++;
        }
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr) {
            neighbors[count] = {wall->x + 1, wall->y, true};
        }
    }
}

/**
 * @brief Traite un voisin en le mettant dans la file d'attente et enregistre
 * son état
 * @param maze Le labyrinthe
 * @param queue La file d'attente
 * @param stack La pile
 * @param stackFree La pile de mémoire libre
 * @param x Coordonnée x du voisin
 * @param y Coordonnée y du voisin
 * @param horizontal Orientation du voisin
 * @param nbBorders Nombre de bords détectés
 * @param j Compteur de voisins
 */
void processNeighbor(const Maze* maze, Queue& queue, Stack& stack,
                     Stack& stackFree, const int x, const int y,
                     const bool horizontal, int& nbBorders, int& j) {
    Wall* neighbor = maze->getWall(x, y, horizontal);
    if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
        neighbor->setAlreadyVisited(true);
        // Vérifie si le voisin est sur le bord du labyrinthe
        if ((horizontal && (x == 0 || x == maze->getWidth() - 1)) ||
            (!horizontal && (y == 0 || y == maze->getHeight() - 1))) {
            nbBorders++;
        }
        // Crée un nouveau mur, l'ajoute à la file d'attente et aux piles
        auto* wall = new wall_maker;
        wall->x = x;
        wall->y = y;
        wall->horizontal = horizontal;
        queue.push(wall);
        stack.push(wall);
        stackFree.push(wall);
        j++;
    }
}

/**
 * @brief Vérifie si un mur est valide en essayant de détecter les bords et les
 * boucles
 * @param maze Le labyrinthe
 * @param wall Le mur à vérifier
 * @param nbBorders Nombre de bords détectés
 * @param nbLoops Nombre de boucles détectées
 */
static void validWall(const Maze* maze, wall_maker* wall, int& nbBorders,
                      int& nbLoops) {
    if (wall == nullptr ||
        maze->getWall(wall->x, wall->y, wall->horizontal) == nullptr) {
        nbBorders = 0;
        return;
    }
    Wall* current = maze->getWall(wall->x, wall->y, wall->horizontal);
    Queue queue;
    Stack stack;
    Stack stackFree;
    queue.push(wall);
    stack.push(wall);
    current->setAlreadyVisited(true);
    // Vérifie si le mur est sur le bord
    if ((wall->horizontal &&
         (wall->x == 0 || wall->x == maze->getWidth() - 1)) ||
        (!wall->horizontal &&
         (wall->y == 0 || wall->y == maze->getHeight() - 1))) {
        nbBorders++;
    }
    // Traite les voisins pour détecter les bords et les boucles
    while (!queue.empty() && nbBorders < 2 && nbLoops < 1) {
        wall = static_cast<wall_maker*>(queue.front());
        queue.pop();
        int j = 0;
        const int nbNeighbors = getNbNeighbors(maze, wall);
        wall_maker neighbors[nbNeighbors];
        getNeighbors(maze, wall, neighbors);
        const int nbNeighborsNotVisited = getNbNeighborsNotVisited(maze, wall);
        for (int i = 0; i < nbNeighbors; i++) {
            processNeighbor(maze, queue, stack, stackFree, neighbors[i].x,
                            neighbors[i].y, neighbors[i].horizontal, nbBorders,
                            j);
        }
        // Vérifie si le nombre de voisins indique une boucle
        if (nbNeighbors - nbNeighborsNotVisited >= 3 ||
            (nbNeighbors == 2 && nbNeighborsNotVisited == 0)) {
            nbLoops++;
        }
    }
    // Nettoie la file d'attente et les piles
    while (!queue.empty()) {
        queue.pop();
    }
    while (!stack.empty()) {
        wall = static_cast<wall_maker*>(stack.top());
        stack.pop();
        Wall* current_tmp = maze->getWall(wall->x, wall->y, wall->horizontal);
        if (current_tmp != nullptr) {
            current_tmp->setAlreadyVisited(false);
        }
    }
    while (!stackFree.empty()) {
        const auto* temp = static_cast<wall_maker*>(stackFree.top());
        delete temp;
        stackFree.pop();
    }
}

void algo_wall_maker(Maze* maze, const int width, const int height,
                     const bool perfect, const double probability, Show* show) {
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    refreshShow(show);
    Stack stack;
    auto stackFree = Stack();
    // Remplit la pile avec tous les murs possibles
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int i = 0; i < 2; i++) {
                if (i == 0 && x < width - 1) {
                    auto* wall = new wall_maker;
                    wall->x = x;
                    wall->y = y;
                    wall->horizontal = false;
                    stack.push(wall);
                    stackFree.push(wall);
                } else if (i == 1 && y < height - 1) {
                    auto* wall = new wall_maker;
                    wall->x = x;
                    wall->y = y;
                    wall->horizontal = true;
                    stack.push(wall);
                    stackFree.push(wall);
                }
            }
        }
    }

    // Traite chaque mur pour construire le labyrinthe
    while (!stack.empty()) {
        auto* wallsPossible =
            static_cast<wall_maker*>(stack.pop(maze->getRand()));
        const int x = wallsPossible->x;
        const int y = wallsPossible->y;
        const bool direction = wallsPossible->horizontal;
        maze->addWall(x, y, direction);
        int nbBorders = 0;
        int nbLoops = 0;
        validWall(maze, wallsPossible, nbBorders, nbLoops);
        Cell* showCell[1] = {maze->getCell(x, y)};
        if (nbBorders >= 2 || nbLoops >= 1) {
            maze->removeWall(x, y, direction);
            refreshShow(show, 1, showCell, true);
        } else {
            refreshShow(show, 1, showCell, false);
        }
    }
    refreshShow(show);
    bool isValid = false;
    bool isPerfect = false;
    checker_depth_first(maze, true, false, show, &isValid, &isPerfect);
    if (isValid && !isPerfect) {
        struct double_cell {
            Cell* cell1;
            Cell* cell2;
        };
        Stack stackDoubleCell;
        Stack stackFreeDoubleCell;
        // Recherche de paires de cellules pour briser le labyrinthe
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                for (int i = 0; i < 2; i++) {
                    Cell* cell1 = maze->getCell(x, y);
                    if (i == 0 && x < width - 1) {
                        Cell* cell2 = maze->getCell(x + 1, y);
                        if (cell1->getStatus() ==
                                MAZE_STATUS_TOO_MANY_NEIGHBORS &&
                            cell2->getStatus() ==
                                MAZE_STATUS_TOO_MANY_NEIGHBORS) {
                            auto* temp = new double_cell{cell1, cell2};
                            stackDoubleCell.push(temp);
                            stackFreeDoubleCell.push(temp);
                        }
                    } else if (i == 1 && y < height - 1) {
                        Cell* cell2 = maze->getCell(x, y + 1);
                        if (cell1->getStatus() ==
                                MAZE_STATUS_TOO_MANY_NEIGHBORS &&
                            cell2->getStatus() ==
                                MAZE_STATUS_TOO_MANY_NEIGHBORS) {
                            auto* temp = new double_cell{cell1, cell2};
                            stackDoubleCell.push(temp);
                            stackFreeDoubleCell.push(temp);
                        }
                    }
                }
            }
        }
        maze->clearMaze();
        // Tente d'ajouter des murs pour briser les boucles
        while (!stackDoubleCell.empty()) {
            const auto* doubleCell =
                static_cast<double_cell*>(stackDoubleCell.pop(maze->getRand()));
            maze->addWall(doubleCell->cell1, doubleCell->cell2);
            Cell* showCell[2] = {doubleCell->cell1, doubleCell->cell2};
            refreshShow(show, 2, showCell, false);
            maze->setStart(doubleCell->cell1->getX(),
                           doubleCell->cell1->getY());
            maze->setEnd(doubleCell->cell2->getX(), doubleCell->cell2->getY());
            if (!solver_breadth_first(maze, show)) {
                maze->removeWall(doubleCell->cell1, doubleCell->cell2);
            }
            maze->clearMaze();
        }
        // Nettoie la mémoire
        while (!stackFreeDoubleCell.empty()) {
            const auto* temp =
                static_cast<double_cell*>(stackFreeDoubleCell.top());
            delete temp;
            stackFreeDoubleCell.pop();
        }
    }
    // Supprime des murs aléatoirement si le labyrinthe n'est pas parfait
    if (!perfect) {
        refreshShow(show);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                for (int i = 0; i < 2; i++) {
                    if (maze->getRand()->get(probability)) {
                        if (i == 0 && x < width - 1) {
                            maze->removeWall(x, y, false);
                        } else if (i == 1 && y < height - 1) {
                            maze->removeWall(x, y, true);
                        }
                        Cell* showCell[1] = {maze->getCell(x, y)};
                        refreshShow(show, 1, showCell, true);
                    }
                }
            }
        }
    }
    // Nettoie la mémoire
    while (!stackFree.empty()) {
        const auto* temp = static_cast<wall_maker*>(stackFree.top());
        delete temp;
        stackFree.pop();
    }
}