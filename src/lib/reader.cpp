#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include "reader.hpp"
#include "var.hpp"

void read(std::string filename, Maze *maze) {
    std::fstream file;
    file.open(filename, std::ios_base::in);
    std::string line;
    getline(file, line);
    int width, height;
    std::istringstream iss(line);
    if (iss >> width >> height) {
        maze->setWidthHeight(width, height);
        getline(file, line);
        while (!file.eof() && line.size() > 0) {
            int x, y;
            std::istringstream iss(line);
            char orientation;
            if (iss >> x >> y >> orientation) {
                if (orientation != 'H' && orientation != 'V') {
                    exit(MAZE_FILE_ERROR);
                }
                if (!maze->addWall(x, y, orientation == 'H')) {
                    exit(MAZE_FILE_ERROR);
                }
                // std::cout << x << ' ' << y << ' ' << orientation << std::endl;
            }
            getline(file, line);
        }
    } else {
        exit(MAZE_FILE_ERROR);
    }
    file.close();
}
