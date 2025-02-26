#ifndef GAME_LIMITS_HPP
#define GAME_LIMITS_HPP

#include "../../maze.hpp"
#include "../../cell.hpp"

bool whileCondition(const Maze *maze, const Cell *cell, int steps);

int resultSteps(const Maze *maze, int steps);

#endif  // GAME_LIMITS_HPP
