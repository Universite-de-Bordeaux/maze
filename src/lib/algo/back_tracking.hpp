#ifndef ALGO_BACKTRACKING_HPP
#define ALGO_BACKTRACKING_HPP

#include "../maze.hpp"
#include "../show.hpp"

struct coordinate {
    int x;
    int y;
};

constexpr int DIRECTIONS[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

/**
 * Crée un labyrinthe avec l'algorithme de backtracking
 * @param maze Pointeur vers le labyrinthe à créer
 * @param width Largeur du labyrinthe
 * @param height Hauteur du labyrinthe
 * @param perfect Si le labyrinthe doit être parfait
 * @param probability Probabilité de casser un mur
 * @param show Pointeur vers l'objet Show
 */
void algo_back_tracking(Maze* maze, int width, int height, bool perfect,
                        double probability, Show* show);

#endif  // ALGO_BACKTRACKING_HPP