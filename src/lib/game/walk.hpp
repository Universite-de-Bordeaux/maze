#ifndef GAME_WALK_HPP
#define GAME_WALK_HPP

#include "../maze.hpp"
#include "../show.hpp"

/**
 * @brief Réalise le jeu du labyrinthe en se déplaçant avec les flèches du
 * clavier
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @param ghost Si le mode fantôme est activé
 * @return Le nombre de pas pour sortir du labyrinthe
 */
int game_walk(const Maze* maze, Show* show, bool ghost);

#endif  // GAME_WALK_HPP
