#ifndef ALGO_COURS_HPP
#define ALGO_COURS_HPP

#include "maze.hpp"
#include "show.hpp"

/**
 * Crée un labyrinthe
 * @param Maze* pointeur vers le labyrinthe à genérer
 * @param int largeur du labyrinthe
 * @param int hauteur du labyrinthe
 * @param bool  vrai si le labyrinthe est parfait
*/
void algo_cours(Maze*, int, int, bool, Show*);

#endif // ALGO_COURS_HPP