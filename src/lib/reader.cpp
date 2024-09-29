#include <cstdio>
#include <cstdlib>
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
    getline(file, line);
    while (!file.eof() && line.size() > 0) {
        std::cout << line << std::endl;
        if (!maze->addWall((int)line[0], (int)line[2], (int)line[4] == 'H')) {
            exit(EXIT_FAILURE);
        }
        getline(file, line);
    }
    file.close();
}
