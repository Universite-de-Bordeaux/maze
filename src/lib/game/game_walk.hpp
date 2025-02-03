#ifndef GAME_WALK_HPP
#define GAME_WALK_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Résoud le labyrinthe sans connaitre son parcours précédent en se
 * baladant aléatoirement
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return int Le nombre de pas effectués pour résoudre le labyrinthe
 */
int game_walk(Maze*, Show*, bool);

#endif  // GAME_WALK_HPP
