#include <cstdio>
#include <iostream>
#include <fstream>
#include "reader.hpp"

// void print_file(std::string file_tab) {

// }

void read(std::string filename, Maze *maze) {
    std::fstream file;
    file.open(filename, std::ios_base::in);
    std::string line;
    getline(file, line);
    maze->setWidthHeight(line[0], line[2]);
    while (!file.eof()) {
        getline(file, line);
        std::cout << line << std::endl;
        maze->addWall(line[0], line[2], line[4] == 'H');
    }
    file.close();
}
