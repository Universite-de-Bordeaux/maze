#ifndef ALGO_BACKTRACKING_HPP
#define ALGO_BACKTRACKING_HPP

#include "../maze.hpp"
#include "../show.hpp"

struct coordinate {
    int x;
    int y;
};

const int DIRECTIONS[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

/**
 * Crée un labyrinthe
 * @param Maze* pointeur vers le labyrinthe à genérer
 * @param int largeur du labyrinthe
 * @param int hauteur du labyrinthe
 * @param bool  vrai si le labyrinthe est parfait
 */
void algo_backtracking(Maze*, int, int, bool, double, Show*);

#endif  // ALGO_BACKTRACKING_HPP