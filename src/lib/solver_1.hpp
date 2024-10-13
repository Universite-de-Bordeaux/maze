#ifndef SOLVER_1_HPP
#define SOLVER_1_HPP

#include "maze.hpp"
#include "show.hpp"

/**
 * @brief Résoud le labyrinthe en utilisant la méthode de la main gauche (ou de la main droite)
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @param left true pour la méthode de la main gauche, false pour la méthode de la main droite
 * @return true si le labyrinthe a été résolu, false sinon
 */
bool solver_1(Maze*, Show*, bool);

#endif // SOLVER_1_HPP
