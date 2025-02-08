#ifndef GAME_FOG_HAND_HPP
#define GAME_FOG_HAND_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Réalise le jeu du labyrinthe avec sans visibilité avec la main gauche ou droite
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @param left Si vrai, la main gauche est utilisée, sinon la main droite est utilisée
 * @return Le nombre de pas pour sortir du labyrinthe
 */
int game_fog_hand(const Maze* maze, Show* show, bool left);

#endif  // GAME_FOG_HAND_HPP
