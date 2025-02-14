#ifndef CHECKER_DEPTH_FIRST_HPP
#define CHECKER_DEPTH_FIRST_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Vérifie si le labyrinthe est valide
 * @param maze Labyrinthe à vérifier
 * @param perfect Vérifie si le labyrinthe est parfait
 * @param left Vérifie si le labyrinthe est parfait en partant à gauche
 * @param show Affichage du labyrinthe
 * @param isValid Pointeur pour savoir si le labyrinthe est valide
 * @param isPerfect Pointeur pour savoir si le labyrinthe est parfait
 */
void checker_depth_first(const Maze* maze, bool perfect, bool left, Show* show,
                         bool* isValid, bool* isPerfect);

#endif  // CHECKER_DEPTH_FIRST_HPP
