#include "writer.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>

void write(const Maze *maze, const char *filename) {
    // Affiche un message indiquant où le labyrinthe est écrit
    std::cout << "Writing maze to file " << filename << std::endl;
    std::ofstream new_file;
    new_file.open(filename,
                  std::ios_base::out);  // Ouvre le fichier en mode écriture

    // Récupération des dimensions du labyrinthe
    const int height = maze->getHeight();
    const int width = maze->getWidth();

    // Écriture de la première ligne contenant la largeur et la hauteur
    new_file << width << ' ' << height << std::endl;

    // Écriture des murs de chaque cellule
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            const Cell *cell = maze->getCell(x, y);
            // Vérification et écriture du mur de droite (vertical)
            if (cell->getWall(MAZE_CELL_RIGHT)) {
                new_file << x << ' ' << y << ' ' << 'V' << std::endl;
            }
            // Vérification et écriture du mur du bas (horizontal)
            if (cell->getWall(MAZE_CELL_BOTTOM)) {
                new_file << x << ' ' << y << ' ' << 'H' << std::endl;
            }
        }
    }

    new_file.close();  // Fermeture du fichier
}