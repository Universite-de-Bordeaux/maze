#ifndef CHECKER_BREADTH_FIRST_HPP
#define CHECKER_BREADTH_FIRST_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Vérifie si le labyrinthe est valide
 * @param maze Labyrinthe à vérifier
 * @param perfect Vérifie si le labyrinthe est parfait
 * @param show Affichage du labyrinthe
 */
void checker_breadth_first(const Maze *maze, bool perfect, Show *show);

#endif  // CHECKER_BREADTH_FIRST_HPP
