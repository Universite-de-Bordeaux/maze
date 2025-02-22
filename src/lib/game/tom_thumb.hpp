#ifndef GAME_TOM_THUMB_HPP
#define GAME_TOM_THUMB_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Réalise le jeu du labyrinthe de manière aléatoire en se souvenant du chemin
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return Le nombre de pas pour sortir du labyrinthe
 */
int game_tom_thumb(Maze* maze, Show* show);

#endif  // GAME_TOM_THUMB_HPP
