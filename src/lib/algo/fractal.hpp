#ifndef ALGO_FRACTAL_HPP
#define ALGO_FRACTAL_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * Crée un labyrinthe
 * @param maze le labyrinthe
 * @param n Le nombre d'itérations
 * @param perfect Si le labyrinthe est parfait
 * @param probability la probabilité de casse d'un mur
 * @param show l'affichage
 */
void algo_fractal(Maze* maze, int n, bool perfect, double probability,
                  Show* show);

#endif  // ALGO_FRACTAL_HPP
