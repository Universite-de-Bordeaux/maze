#ifndef GAME_SPLATOON_DEAD_END_HAND_HPP
#define GAME_SPLATOON_DEAD_END_HAND_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Réalise le jeu du labyrinthe avec la main gauche ou droite en se
 * souvenant du chemin
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @param left Si vrai, la main gauche est utilisée, sinon la main droite est
 * utilisée
 * @return Le nombre de pas pour sortir du labyrinthe
 */
int game_splatoon_dead_end_hand(Maze* maze, Show* show, bool left);

#endif  // GAME_SPLATOON_DEAD_END_HAND_HPP
