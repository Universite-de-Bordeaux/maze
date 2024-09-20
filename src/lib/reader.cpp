# include "maze.hpp"
# include <iostream>
#include <fstream>
#include <string>

void read(std::string filename) {
    std::fstream file;
    file.open(filename, std::ios_base::in);
    std::string line;
    while (!file.eof()) {
        std::getline(file, line);
        std::cout << line << std::endl;
    }
}
