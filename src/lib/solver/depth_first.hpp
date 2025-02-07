#ifndef SOLVER_DEPTHFIRST_HPP
#define SOLVER_DEPTHFIRST_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Résoud le labyrinthe en utilisant la méthode de la main gauche (ou de
 * la main droite)
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @param left true pour la méthode de la main gauche, false pour la méthode de
 * la main droite
 * @return true si le labyrinthe a été résolu, false sinon
 */
bool solver_depth_first(Maze*, Show*, bool);

#endif  // SOLVER_DEPTHFIRST_HPP
