#ifndef ALGO_FRACTAL_HPP
#define ALGO_FRACTAL_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * Crée un labyrinthe
 * @param Maze* pointeur vers le labyrinthe à genérer
 * @param n donne la taille du labyrinthe qui sera de 2^n
 * @param bool vrai si le labyrinthe est parfait
 */
void algo_fractal(Maze*, int, bool, double, Show*);

#endif  // ALGO_FRACTAL_HPP
