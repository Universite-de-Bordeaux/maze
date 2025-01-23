#include <fstream>
#include <iterator>
#include <ostream>

#include "maze.hpp"
#include "var.hpp"

/**
 * permet de sauvegarder les données du labyrinthe dans un fichier
 * @param maze le labyrinthe à sauvegarder
 * @param filename le chemin relatif du fichier
 */
void write(Maze *, char *);
