#include "writer.hpp"
#include <ios>
#include <ostream>

void write(Maze * maze, char *file) {
    std::ofstream new_file;
    new_file.open(file, std::ios_base::out);
    int height = maze->getHeight();
    int width = maze->getWidth();
    new_file << width << ' ' << height << std::endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Cell *cell = maze->getCell(x, y);
            if (cell->getWall(MAZE_CELL_RIGHT)) {
                new_file << x << ' ' << y << ' ' << 'V' << std::endl;
            } else if (cell->getWall(MAZE_CELL_BOTTOM)) {
                new_file << x << ' ' << y << ' ' << 'H' << std::endl;
            }
        }
    }
    new_file.close();
}
