#include <cstdio>
#include <iostream>
#include <fstream>
#include "reader.hpp"
#include "wall.hpp"

// void print_file(std::string file_tab) {

// }

void read(std::string filename, Maze * maze) {
    std::fstream file;
    file.open(filename, std::ios_base::in);
    std::string line;
    getline(file, line);
    // maze->setWidth((int)line[0]);
    // maze->setHeight((int)line[2]);
    while (!file.eof()) {
        getline(file, line);
        // WallType wall = line[4] == 'V' ? RIGHT : BOTTOM;
        // maze->setCell((int)line[0], (int)line[2], wall);
    }
    file.close();
}
