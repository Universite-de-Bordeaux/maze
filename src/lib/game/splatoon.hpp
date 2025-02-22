#ifndef GAME_SPLATOON_HPP
#define GAME_SPLATOON_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Réalise le jeu du labyrinthe de manière aléatoire en se souvenant du
 * nombre fois où il est passé
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return Le nombre de pas pour sortir du labyrinthe
 */
int game_splatoon(Maze* maze, Show* show);

#endif  // GAME_SPLATOON_HPP
