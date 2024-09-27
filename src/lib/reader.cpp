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
    // maze->setWidthHeight(line[0], line[2]);
    // for (int i = 0;i<maze->getHeight();i++) {
    //     for (int j = 0;j<maze->getWidth();j++) {
    //         std::cout << "test" << std::endl;
            // *(*(maze->getMat()+i)+j) = Cell(i, j);
    //     }
    // }
    std::cout << "test reader" << std::endl;
    while (!file.eof()) {
        getline(file, line);
        std::cout << line << std::endl;
        // WallType wall = line[4] == 'V' ? RIGHT : BOTTOM;
        // maze.setCell((int)line[0], (int)line[2], wall);
    }
    file.close();
}
