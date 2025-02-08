#ifndef ALGO_DIAGONAL_HPP
#define ALGO_DIAGONAL_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * Crée un labyrinthe
 * @param maze Le labyrinthe
 * @param width La largeur du labyrinthe
 * @param height La hauteur du labyrinthe
 * @param perfect Si le labyrinthe doit être parfait
 * @param probability La probabilité de mur
 * @param show L'objet pour afficher le labyrinthe
 */
void algo_diagonal(Maze* maze, int width, int height, bool perfect, double probability, Show* show);

#endif  // ALGO_DIAGONAL_HPP
