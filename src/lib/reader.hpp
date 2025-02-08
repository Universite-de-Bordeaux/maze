#ifndef READER_HPP
#define READER_HPP

#include <string>

#include "maze.hpp"

/**
 * Lit un fichier et remplit un objet Maze
 * @param filename Le nom du fichier à lire
 * @param maze l'objet Maze à remplir
 */
void read(const std::string& filename, Maze* maze);

#endif  // READER_HPP
