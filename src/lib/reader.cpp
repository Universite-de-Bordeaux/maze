#include "reader.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "var.hpp"

void read(const std::string& filename, Maze* maze) {
    // ouverture du fichier
    std::fstream file;
    file.open(filename, std::ios_base::in);
    std::string line;

    // initialisation des variables
    getline(file, line);  // permet de lire une ligne
    int width, height;
    std::istringstream iss(line);

    if (iss >> width >>
        height) {  // iss permet de récupérer la largeur et la hauteur
        maze->setWidthHeight(width, height);
        getline(file, line);

        while (!file.eof() && !line.empty()) {
            int x, y;
            std::istringstream iss_tmp(line);
            char orientation;

            if (iss_tmp >> x >> y >> orientation) {
                // vérification d'erreur
                if (orientation != 'H' && orientation != 'V') {
                    exit(MAZE_FILE_ERROR);
                }

                maze->addWall(x, y, orientation == 'H');
            }
            getline(file, line);
        }
    }
    // gestion d'erreur
    else {
        exit(MAZE_FILE_ERROR);
    }
    file.close();
}
