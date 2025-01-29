#ifndef GAME_FOG_HAND_HPP
#define GAME_FOG_HAND_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Résoud le labyrinthe sans connaitre son parcours précédent en se
 * baladant aléatoirement
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return true si le labyrinthe a été résolu, false sinon
 */
bool game_fog_hand(Maze*, Show*, bool);

#endif  // GAME_FOG_HAND_HPP
