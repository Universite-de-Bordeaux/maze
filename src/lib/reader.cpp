#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "reader.hpp"
#include "var.hpp"

void read(std::string filename, Maze *maze) {
    // ouverture du fichier ----------------------------------------------------------------------
    std::fstream file;
    file.open(filename, std::ios_base::in);
    std::string line;
    // -------------------------------------------------------------------------------------------

    // initialisation des variable ---------------------------------------------------------------
    getline(file, line); // permet de lire une ligne
    int width, height;
    std::istringstream iss(line);
    // -------------------------------------------------------------------------------------------
    if (iss >> width >> height) { // iss permet de récuperer la largeur et la hauteur
        maze->setWidthHeight(width, height);
        getline(file, line);
        while (!file.eof() && line.size() > 0) {
            int x, y;
            std::istringstream iss(line);
            char orientation;
            if (iss >> x >> y >> orientation) {
                // vérification d'erreur ---------------------------------------------------------
                if (orientation != 'H' && orientation != 'V') {
                    exit(MAZE_FILE_ERROR);
                }
                // -------------------------------------------------------------------------------

                // ajout du mur en prenant en compte les potentielles erreurs renvoyer par addWall
                if (!maze->addWall(x, y, orientation == 'H')) {
                    exit(MAZE_FILE_ERROR);
                }
                // -------------------------------------------------------------------------------
            }
            getline(file, line);
        }
    }
    // gestion d'erreur --------------------------------------------------------------------------
    else {
        exit(MAZE_FILE_ERROR);
    }
    // ------------------------------------------------------------------------------------------
    file.close();
}
