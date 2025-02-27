#include "fractal.hpp"

#include <cmath>
#include <iostream>

#include "../maze.hpp"
#include "../show.hpp"
#include "../var.hpp"

/**
 * @brief Ajoute des murs de manière imparfaite dans le labyrinthe
 * @param maze Le labyrinthe dans lequel ajouter des murs
 * @param mid La position médiane pour l'ajout de murs
 * @param probability La probabilité d'ajouter un mur
 */
static void add_wall_imperfect(Maze *maze, const int mid,
                               const double probability) {
    // Parcourt le labyrinthe pour ajouter des murs
    for (int i = 0; i < maze->getHeight(); i++) {
        // Ajout de murs sur le côté gauche et en haut
        maze->addWall(mid - 1, i, false);
        maze->addWall(i, mid - 1, true);
    }
    // Tableau pour stocker les positions où retirer des murs
    int remove[4];
    // Retrait d'un mur aléatoire à gauche
    remove[0] = maze->getRand()->get(0, mid - 1);
    maze->removeWall(mid - 1, remove[0], false);
    // Retrait d'un mur aléatoire en haut
    remove[1] = maze->getRand()->get(0, mid - 1);
    maze->removeWall(remove[1], mid - 1, true);
    // Retrait d'un mur aléatoire à droite
    remove[2] = maze->getRand()->get(0, mid - 1);
    maze->removeWall(mid - 1, mid + remove[2], false);
    // Retrait d'un mur aléatoire en bas
    remove[3] = maze->getRand()->get(0, mid - 1);
    maze->removeWall(mid + remove[3], mid - 1, true);
    // Rajout d'un mur aléatoire avec une probabilité donnée
    if (!maze->getRand()->get(probability)) {
        const int r = maze->getRand()->get(0, 3);
        if (r == 0) {
            maze->addWall(mid - 1, remove[0], false);
        } else if (r == 1) {
            maze->addWall(remove[1], mid - 1, true);
        } else if (r == 2) {
            maze->addWall(mid - 1, mid + remove[2], false);
        } else if (r == 3) {
            maze->addWall(mid + remove[3], mid - 1, true);
        }
    }
}

/**
 * @brief Ajoute des murs de manière parfaite dans le labyrinthe
 * @param maze Le labyrinthe dans lequel ajouter des murs
 * @param mid La position médiane pour l'ajout de murs
 * @return True si l'ajout de murs a réussi, false sinon
 */
static bool add_wall_perfect(Maze *maze, const int mid) {
    // Ajout de murs alentour
    for (int i = 0; i < mid; i++) {
        maze->addWall(mid - 1, i, false);
        maze->addWall(mid + i, mid - 1, true);
        maze->addWall(mid - 1, mid + i, false);
        maze->addWall(i, mid - 1, true);
    }
    // Direction aléatoire pour créer une sortie
    const int direction = maze->getRand()->get(0, 3);
    if (direction == NORTH) {
        int remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid + remove, mid - 1, true);
        remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid - 1, mid + remove, false);
        remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(remove, mid - 1, true);
    } else if (direction == EAST) {
        int remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid - 1, mid + remove, false);
        remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(remove, mid - 1, true);
        remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid - 1, remove, false);
    } else if (direction == SOUTH) {
        int remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(remove, mid - 1, true);
        remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid - 1, remove, false);
        remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid + remove, mid - 1, true);
    } else if (direction == WEST) {
        int remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid - 1, remove, false);
        remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid + remove, mid - 1, true);
        remove = maze->getRand()->get(0, mid - 1);
        maze->removeWall(mid - 1, mid + remove, false);
    } else {
        return false;
    }
    return true;
}

/**
 * @brief Crée un labyrinthe en quadrants
 * @param maze Le labyrinthe à créer
 */
static void quad_maze(Maze *maze) {
    // Récupération des dimensions actuelles du labyrinthe
    const int old_width = maze->getWidth();
    const int old_height = maze->getHeight();
    // Création d'un nouveau labyrinthe temporaire
    auto new_maze = Maze();
    new_maze.setWidthHeight(old_width, old_height);
    // Copie des murs du labyrinthe actuel vers le nouveau
    for (int i = 0; i < old_width; i++) {
        for (int j = 0; j < old_height; j++) {
            for (int k = 0; k < 2; k++) {
                if (maze->getWall(i, j, k)) {
                    new_maze.addWall(i, j, k);
                }
            }
        }
    }
    // Redimensionnement du labyrinthe actuel
    maze->setWidthHeight(2 * maze->getWidth(), 2 * maze->getHeight());
    // Réplication des murs dans les quatre quadrants
    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            for (int k = 0; k < 2; k++) {
                if (new_maze.getWall(i, j, k)) {
                    maze->addWall(i, j, k);
                    maze->addWall(i + old_width, j, k);
                    maze->addWall(i + old_width, j + old_height, k);
                    maze->addWall(i, j + old_height, k);
                }
            }
        }
    }
    // Nettoyage du labyrinthe temporaire
    new_maze.clearMaze();
}

void algo_fractal(Maze *maze, int n, const bool perfect,
                  const double probability, Show *show) {
    // Initialisation du labyrinthe à une cellule de base
    maze->setWidthHeight(1, 1);
    if (show && !show->getLowFreq()) {
        // Création de la fenêtre d'affichage
        show->create();
    }
    if (show && !show->getLowFreq()) {
        show->destroy();
        show->create();
    }
    // Rafraîchissement de l'affichage initial
    refreshShow(show);
    // Boucle principale de génération fractale
    while (n > 0) {
        // Duplication du labyrinthe en quadrants
        quad_maze(maze);
        // Ajout des murs en fonction des paramètres
        if (!perfect) {
            add_wall_imperfect(maze, maze->getHeight() / 2, probability);
        } else {
            if (!add_wall_perfect(maze, maze->getHeight() / 2)) {
                // Gestion d'erreur en cas d'echec
                std::cerr << "Error: add_wall" << std::endl;
                return;
            }
        }
        // Rafraîchissement de l'affichage après chaque itération
        if (show && !show->getLowFreq()) {
            show->destroy();
            show->create();
        }
        refreshShow(show);
        // Décrémentation de l'itération
        n -= 1;
    }
    // Finalisation de l'affichage
    if (show && show->getLowFreq()) {
        show->destroy();
        show->create();
    }
}