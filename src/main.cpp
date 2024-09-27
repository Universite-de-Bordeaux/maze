#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lib/reader.hpp"
#include "lib/maze.hpp"

void help() {
    std::cout << "Usage: ./main [-option] <instance_file>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-h : Show this help" << std::endl;
    std::cout << "-v : Show version" << std::endl;
    std::cout << "-r : Read the instance file" << std::endl;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        help();
        return 1;
    }
    int numberOfCommands = 0, numberOfNoCommands = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            numberOfCommands++;
        } else {
            numberOfNoCommands++;
        }
    }
    if (numberOfCommands < 1) {
        help();
        return 1;
    }
    char *commands[numberOfCommands];
    char *noCommands[numberOfNoCommands];
    for (int i = 1, j = 0, k = 0; i < argc; i++) {
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
            help();
        } else if (strcmp(commands[i], "-v") == 0) {
            std::cout << "Version 0.1" << std::endl;
        } else if (strcmp(commands[i], "-r") == 0) {
            if (numberOfNoCommands < 1) {
                help();
                return 1;
            }
            for (int i = 0; i < numberOfNoCommands; i++) {
                Maze a = Maze();
                Maze *maze = &a;
                read(noCommands[i], maze);
            }
        } else {
            std::cout << "Usage: ./main <instance_file> [-option]" << std::endl;
            return 1;
        }
    }
    return 0;
}
