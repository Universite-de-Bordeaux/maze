#ifndef SOLVER_BREADTHFIRST_HPP
#define SOLVER_BREADTHFIRST_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Résoud le labyrinthe en utilisant la méthode de la main gauche (ou de la main droite)
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return true si le labyrinthe a été résolu, false sinon
 */
bool solver_breadthfirst(Maze*, Show*);

#endif // SOLVER_BREADTHFIRST_HPP
