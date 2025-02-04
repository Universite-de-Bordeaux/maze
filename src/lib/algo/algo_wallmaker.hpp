#ifndef ALGO_WALLMAKER_HPP
#define ALGO_WALLMAKER_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * Crée un labyrinthe
 * @param Maze* pointeur vers le labyrinthe à genérer
 * @param int largeur du labyrinthe
 * @param int hauteur du labyrinthe
 * @param bool  vrai si le labyrinthe est parfait
 */
void algo_wallmaker(Maze*, int, int, bool, double, Show*);

#endif  // ALGO_WALLMAKER_HPP