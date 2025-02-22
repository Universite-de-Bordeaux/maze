#ifndef GAME_DEAD_END_HPP
#define GAME_DEAD_END_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Réalise le jeu du labyrinthe avec sans visibilité de manière aléatoire
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return Le nombre de pas pour sortir du labyrinthe
 */
int game_dead_end(Maze* maze, Show* show);

#endif  // GAME_DEAD_END_HPP
