#include "reader.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "var.hpp"

void read(const std::string& filename, Maze* maze) {
    // Ouvre le fichier en mode lecture
    std::fstream file;
    file.open(filename, std::ios_base::in);
    std::string line;

    // Lit la première ligne qui contient la largeur et la hauteur du labyrinthe
    getline(file, line);
    int width, height;
    std::istringstream iss(line);

    // Tente de récupérer la largeur et la hauteur à partir de la première ligne
    if (iss >> width >> height) {
        // Met à jour les dimensions du labyrinthe
        maze->setWidthHeight(width, height);
        getline(file, line);  // Passe à la ligne suivante

        // Lit les lignes restantes qui contiennent les informations des murs
        while (!file.eof() && !line.empty()) {
            int x, y;
            std::istringstream iss_tmp(line);
            char orientation;

            // Tente de récupérer les coordonnées (x, y) et l'orientation du mur
            if (iss_tmp >> x >> y >> orientation) {
                // Vérifie que l'orientation est valide ('H' pour horizontal ou
                // 'V' pour vertical)
                if (orientation != 'H' && orientation != 'V') {
                    exit(MAZE_FILE_ERROR);  // Sort si l'orientation est invalid
                }

                // Ajoute le mur au labyrinthe
                maze->addWall(x, y, orientation == 'H');
            }
            getline(file, line);  // Passe à la ligne suivante
        }
    }
    // Gestion d'erreur si la première ligne ne peut pas être lue correctement
    else {
        exit(MAZE_FILE_ERROR);
    }
    file.close();  // Ferme le fichier
}