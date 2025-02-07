#ifndef CHECKER_BREADTHFIRST_HPP
#define CHECKER_BREADTHFIRST_HPP

#include "../maze.hpp"
#include "../queue.hpp"
#include "../show.hpp"

/**
 * @brief checker - Vérifie si le labyrinthe est valide
 * @param maze - Labyrinthe à vérifier
 * @param perfect - Vérifie si le labyrinthe est parfait
 */
void checker_breadthfirst(Maze *, bool, Show *);

#endif  // CHECKER_BREADTHFIRST_HPP
