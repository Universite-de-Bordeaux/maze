#include "diagonal.hpp"

#include "../show.hpp"

// Structure définissant une position de départ pour les sorties
struct start {
    bool left;  // Spécifie si la sortie démarre à gauche
    bool top;   // Spécifie si la sortie démarre en haut
};

/**
 * @brief Crée une sortie dans le labyrinthe
 * @param a Position actuelle le long de l'axe principal
 * @param maxA Position maximale le long de l'axe principal
 * @param b Position actuelle le long de l'axe secondaire
 * @param maxB Position maximale le long de l'axe secondaire
 * @param maze Le labyrinthe dans lequel créer la sortie
 * @param isHorizontal Si la sortie est horizontale
 * @param whereStart Position de départ de la sortie
 * @param perfect Si le labyrinthe est parfait
 * @param probability Probabilité d'ajouter une paroie
 * @param show Objet pour afficher le labyrinthe
 */
static void create_exit(int *a, const int *maxA, const int *b, const int *maxB,
                        Maze *maze, const bool isHorizontal,
                        const start *whereStart, const bool perfect,
                        const double probability, Show *show) {
    // Vérifie si la position actuelle est valable pour créer une sortie
    if ((isHorizontal ? !whereStart->top : !whereStart->left) <= *a &&
        *a < *maxA - (isHorizontal ? whereStart->top : whereStart->left)) {
        // Détermine la position de début et de fin pour l'autre axe
        const int startB = isHorizontal      ? (whereStart->left ? *b : 0)
                           : whereStart->top ? *b
                                             : 0;
        const int endB = isHorizontal      ? (whereStart->left ? *maxB : *b)
                         : whereStart->top ? *maxB
                                           : *b;

        if (startB == endB) {
            // Si les positions de début et de fin sont les mêmes, déplace le
            // pointeur
            *a += isHorizontal       ? (whereStart->top ? 1 : -1)
                  : whereStart->left ? 1
                                     : -1;
            return;
        }

        // Génère une position aléatoire pour la sortie
        const int rb = maze->getRand()->get(startB, endB - 1);

        // Parcourt les positions pour créer les parois et la sortie
        for (int bb = startB; bb <= endB; bb++) {
            if (bb != rb && (perfect || !maze->getRand()->get(probability))) {
                if (isHorizontal) {
                    // Ajoute une paroi si ce n'est pas la position de la sortie
                    maze->addWall(bb, *a - !whereStart->top, isHorizontal);
                } else {
                    maze->addWall(*a - !whereStart->left, bb, isHorizontal);
                }
            }
            // Met à jour l'affichage de la cellule courante
            Cell *cell =
                maze->getCell(isHorizontal ? bb : *a, isHorizontal ? *a : bb);
            refreshShow(show, 1, &cell, false);
        }

        // Met à jour la position actuelle
        *a += isHorizontal       ? (whereStart->top ? 1 : -1)
              : whereStart->left ? 1
                                 : -1;

        // Met à jour l'affichage de la sortie
        Cell *cell =
            maze->getCell(isHorizontal ? rb : *a, isHorizontal ? *a : rb);
        refreshShow(show, 1, &cell, true);
    }
}

void algo_diagonal(Maze *maze, const int width, const int height,
                   const bool perfect, const double probability, Show *show) {
    // Initialise les dimensions du labyrinthe
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }

    // Détermine aléatoirement la position de départ des sorties
    const start whereStart = {maze->getRand()->get(0, 1) == 0,
                              maze->getRand()->get(0, 1) == 0};
    int x = whereStart.left ? 0 : width - 1;  // Position initiale sur l'axe X
    int y = whereStart.top ? 0 : height - 1;  // Position initiale sur l'axe Y

    while ((!whereStart.left <= x && x < width - whereStart.left) ||
           (!whereStart.top <= y && y < height - whereStart.top)) {
        // Décide aléatoirement de l'ordre de création des sorties
        if (maze->getRand()->get(0, 1)) {
            // Crée une sortie horizontale puis verticale
            create_exit(&x, &width, &y, &height, maze, false, &whereStart,
                        perfect, probability, show);
            create_exit(&y, &height, &x, &width, maze, true, &whereStart,
                        perfect, probability, show);
        } else {
            // Crée une sortie verticale puis horizontale
            create_exit(&y, &height, &x, &width, maze, true, &whereStart,
                        perfect, probability, show);
            create_exit(&x, &width, &y, &height, maze, false, &whereStart,
                        perfect, probability, show);
        }
    }

    // Rafraîchit l'affichage final
    refreshShow(show);
}
