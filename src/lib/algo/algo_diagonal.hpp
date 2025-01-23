#ifndef ALGO_DIAGONAL_HPP
#define ALGO_DIAGONAL_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * Crée un labyrinthe
 * @param Maze* pointeur vers le labyrinthe à genérer
 * @param int largeur du labyrinthe
 * @param int hauteur du labyrinthe
 * @param bool  vrai si le labyrinthe est parfait
 */
void algo_diagonal(Maze*, int, int, bool, Show*);

#endif  // ALGO_DIAGONAL_HPP
