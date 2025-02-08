#ifndef WRITER_HPP
#define WRITER_HPP

#include "maze.hpp"

/**
 * @brief Sauvegarde un labyrinthe dans un fichier
 * @param maze le labyrinthe à sauvegarder
 * @param filename Le chemin relatif du fichier
 */
void write(const Maze *maze, const char *filename);

#endif  // WRITER_HPP