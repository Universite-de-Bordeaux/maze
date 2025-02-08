#include "writer.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>

void write(const Maze *maze, const char *filename) {
    std::cout << "Writing maze to file " << filename << std::endl;
    std::ofstream new_file;
    new_file.open(filename, std::ios_base::out);
    // récupération de largeur et hauteur
    const int height = maze->getHeight();
    const int width = maze->getWidth();
    // écriture de la première ligne
    new_file << width << ' ' << height << std::endl;
    // écriture des lignes suivantes
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            const Cell *cell = maze->getCell(x, y);
            if (cell->getWall(MAZE_CELL_RIGHT)) {
                new_file << x << ' ' << y << ' ' << 'V' << std::endl;
            }
            if (cell->getWall(MAZE_CELL_BOTTOM)) {
                new_file << x << ' ' << y << ' ' << 'H' << std::endl;
            }
        }
    }
    new_file.close();
}
