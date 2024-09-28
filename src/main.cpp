#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lib/reader.hpp"
#include "lib/maze.hpp"

/**
 * Affiche l'aide
 */
void help() {
    std::cout << "Usage: ./main [-option] <instance_file>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-h : Show this help" << std::endl;
    std::cout << "-v : Show version" << std::endl;
    std::cout << "-r : Read the instance file" << std::endl;
}

/**
 * Affiche l'aide et retourne le code d'erreur
 * @param a Code d'erreur
 * @return Code d'erreur
 */
int help(int a) {
    help();
    return a;
}

/**
 * Commande -r
 * @param file Fichier
 */
void commandR(char *file) {
    Maze a = Maze();
    Maze *maze = &a;
    read(file, maze);
}

/**
 * Main
 * @param argc Nombre d'arguments
 * @param argv Arguments
 * @return Code d'erreur
 */
int main(int argc, char *argv[]) {
    if (argc < 2) return help(1);

    // Compte le nombre de commandes et de fichiers
    int numberOfCommands = 0, numberOfNoCommands = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            numberOfCommands++;
        } else {
            numberOfNoCommands++;
        }
    }

    if (numberOfCommands < 1) return help(1);

    // Stocke les commandes et les fichiers
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

    // Vérifie que les fichiers existent
    for (int i = 0; i < numberOfNoCommands; i++) {
        std::ifstream file(noCommands[i]);
        if (!file) {
            std::cout << "File not found : " << argv[1] << std::endl;
            return 1;
        }
    }

    // Exécute les commandes
    for (int i = 0; i < numberOfCommands; i++) {
        // Commandes
        // -h : Affiche l'aide
        if (strcmp(commands[i], "-h") == 0) help();
        // -v : Affiche la version
        else if (strcmp(commands[i], "-v") == 0) std::cout << "Version 0.1" << std::endl;
        // -r : Lit le fichier
        else if (strcmp(commands[i], "-r") == 0) {
            if (numberOfNoCommands < 1) {
                help();
                return 1;
            }
            for (int i = 0; i < numberOfNoCommands; i++) {
                commandR(noCommands[i]);
            }
        }
        // Commande inconnue
        else {
            std::cout << "Usage: ./main <instance_file> [-option]" << std::endl;
            return 1;
        }
    }
    return 0;
}
