#ifndef SOLVER_BREADTHFIRST_HPP
#define SOLVER_BREADTHFIRST_HPP

#include "../maze.hpp"
#include "../show.hpp"

struct Position {
    int x;
    int y;
};

struct PositionHistory {
    int x;
    int y;
    int parent_x;
    int parent_y;
};

/**
 * @brief Résoud le labyrinthe en utilisant la méthode de la main gauche (ou de
 * la main droite)
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return true si le labyrinthe a été résolu, false sinon
 */
bool solver_breadthfirst(Maze*, Show*);

#endif  // SOLVER_BREADTHFIRST_HPP
