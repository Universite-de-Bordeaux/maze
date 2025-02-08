#ifndef SOLVER_DEPTH_FIRST_HPP
#define SOLVER_DEPTH_FIRST_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Réalise la résolution du labyrinthe par la méthode de la main gauche
 * ou droite
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @param left True pour la méthode de la main gauche, false pour la méthode de
 * la main droite
 * @return True si le labyrinthe a été résolu, false sinon
 */
bool solver_depth_first(Maze* maze, Show* show, bool left);

#endif  // SOLVER_DEPTH_FIRST_HPP
