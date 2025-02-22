#ifndef GAME_LIB_SPLATOON_HPP
#define GAME_LIB_SPLATOON_HPP

#include "../../maze.hpp"

/**
 * @brief Cherche le nombre de passages de la cellule avec le moins de passages
 * @param cell La cellule à partir de laquelle chercher
 * @param counts Le tableau des compteurs de passages
 * @param checkVisited Vérifie si la cellule a déjà été visitée
 * @return Le nombre de passages de la cellule avec le moins de passages
 */
int MinCountCell(const Cell *cell, int **counts, bool checkVisited = false);

/**
 * @brief Cherche le nombre de cellules avec le même nombre de passages que la
 * cellule avec le moins de passages
 * @param cell La cellule à partir de laquelle chercher
 * @param counts Le tableau des compteurs de passages
 * @param minCount Le nombre de passages de la cellule avec le moins de passages
 * @param checkVisited Vérifie si la cellule a déjà été visitée
 * @return Le nombre de cellules avec le même nombre de passages que la cellule
 * avec le moins de passages
 */
int nbMinCountCell(const Cell *cell, int **counts, int minCount,
                   bool checkVisited = false);

/**
 * @brief Cherche les cellules avec le même nombre de passages que la cellule
 * avec le moins de passages
 * @param cell La cellule à partir de laquelle chercher
 * @param counts Le tableau des compteurs de passages
 * @param minCount Le nombre de passages de la cellule avec le moins de passages
 * @param cells Le tableau des cellules avec le même nombre de passages que la
 * cellule avec le moins de passages
 * @param checkVisited Vérifie si la cellule a déjà été visitée
 */
void cellsMinCountCell(const Cell *cell, int **counts, int minCount,
                       Cell **cells, bool checkVisited = false);

#endif  // GAME_LIB_SPLATOON_HPP
