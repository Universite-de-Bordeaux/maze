#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lib/reader.hpp"
#include "lib/maze.hpp"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "Usage: ./main <instance_file>" << std::endl;
        return 1;
    }
    int numberOfCommands = 0;
    int numberOfNoCommands = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            numberOfCommands++;
        } else {
            numberOfNoCommands++;
        }
    }
    if (numberOfCommands > 1) {
        std::cout << "Usage: ./main <instance_file> [-option]" << std::endl;
        return 1;
    }
    char *commands[numberOfCommands];
    char *noCommands[numberOfNoCommands];
    int j = 0;
    int k = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            commands[j] = argv[i];
            j++;
        } else {
            noCommands[k] = argv[i];
            k++;
        }
    }
    for (int i = 0; i < numberOfNoCommands; i++) {
        std::ifstream file(noCommands[i]);
        if (!file) {
            std::cout << "File not found : " << argv[1] << std::endl;
            return 1;
        }
    }
    for (int i = 0; i < numberOfCommands; i++) {
        if (strcmp(commands[i], "-h") == 0) {
            std::cout << "Usage: ./main <instance_file> [-option]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "-h : Show this help" << std::endl;
            std::cout << "-v : Show version" << std::endl;
            std::cout << "-r : Read the instance file" << std::endl;
            return 0;
        } else if (strcmp(commands[i], "-v") == 0) {
            std::cout << "Version 0.1" << std::endl;
            return 0;
        } else if (strcmp(commands[i], "-r") == 0) {
            for (int i = 0; i < numberOfNoCommands; i++) {
                Maze a = Maze();
                Maze *maze = &a;
                read(noCommands[i], maze);
            }
            return 0;
        } else {
            std::cout << "Usage: ./main <instance_file> [-option]" << std::endl;
            return 1;
        }
    }



    // Cell cell1 = Cell(1, 2);
    // std::cout << cell1.getX() << std::endl;
    // cell1.setX(10);
    // std::cout << cell1.getX() << std::endl;

    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
