#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include "reader.hpp"

void read(std::string filename, Maze *maze) {
    std::fstream file;
    file.open(filename, std::ios_base::in);
    std::string line;
    getline(file, line);
    maze->setWidthHeight((int)line[0], (int)line[2]);
    getline(file, line);
    while (!file.eof() && line.size() > 0) {
        int x, y;
        std::istringstream iss(line);
        char orientation;
        if (iss >> x >> y >> orientation) {
            if (orientation != 'H' && orientation != 'V') {
                exit(1);
            }
            if (!maze->addWall(x, y, orientation == 'H')) {
                exit(1);
            }
            std::cout << x << ' ' << y << ' ' << orientation << std::endl;
        }
        getline(file, line);
    }
    file.close();
}
