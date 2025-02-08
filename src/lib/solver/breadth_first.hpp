#ifndef SOLVER_BREADTH_FIRST_HPP
#define SOLVER_BREADTH_FIRST_HPP

#include "../maze.hpp"
#include "../show.hpp"

struct position {
    int x;
    int y;
};

struct positionHistory {
    int x;
    int y;
    int parent_x;
    int parent_y;
};

/**
 * @brief Réalise la résolution du labyrinthe en largeur
 * @param maze Le labyrinthe à résoudre
 * @param show L'affichage du labyrinthe
 * @return True si le labyrinthe a été résolu, false sinon
 */
bool solver_breadth_first(const Maze* maze, Show* show);

#endif  // SOLVER_BREADTH_FIRST_HPP
