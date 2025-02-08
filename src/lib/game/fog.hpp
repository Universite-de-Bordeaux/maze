#ifndef GAME_FOG_HPP
#define GAME_FOG_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Réalise le jeu du labyrinthe avec sans visibilité de manière aléatoire
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return Le nombre de pas pour sortir du labyrinthe
 */
int game_fog(Maze* maze, Show* show);

#endif  // GAME_FOG_HPP
