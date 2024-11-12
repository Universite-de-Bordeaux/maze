#ifndef ALGO_FRACTAL_HPP
#define ALGO_FRACTAL_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * Crée un labyrinthe
 * @param Maze* pointeur vers le labyrinthe à genérer
 * @param n la taille du tableau (doit être une puissance de 2)
 * @param bool vrai si le labyrinthe est parfait
*/
void algo_fractal(Maze*, int, bool, Show*);

#endif // ALGO_FRACTAL_HPP
