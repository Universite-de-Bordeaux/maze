# include "maze.hpp"
#include <fstream>
#include <iterator>
#include <ostream>
# include "var.hpp"

void write(Maze * maze) {
    std::ofstream file;
    file.open("../instance/test.txt");
    for (int y = 0; y < maze->getHeight() - 1; y++) {
        for (int x = 0; x < maze->getWidth() - 1; x++) {
            Cell *cell = maze->getCell(x, y);
            if (cell->getWall(MAZE_CELL_RIGHT)) {
                file << x << ' ' << y << ' ' << 'V' << std::endl;
            } else if (cell->getWall(MAZE_CELL_BOTTOM)) {
                file << x << ' ' << y << ' ' << 'H' << std::endl;
            }
        }
    }
    file.close();
}
