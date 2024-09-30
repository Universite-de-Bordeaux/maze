#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lib/reader.hpp"
#include "lib/show.hpp"
#include "lib/maze.hpp"
#include "lib/var.hpp"
#include "lib/algo_cours.hpp"

/**
 * Affiche l'aide
 */
 void help() {
     std::cout << "Usage:./main.out [-option] <instance_file>" << std::endl;
     std::cout << "Options:" << std::endl;
     std::cout << "-h ou --help : Affiche cette aide" << std::endl;
     std::cout << "-s ou --show : Affiche un labyrinthe (nécessite un labyrinthe en mémoire)" << std::endl;
     std::cout << "-o ou --output <fichier> : Spécifie le fichier de sortie (nécessaire pour sauvegarder un labyrinthe, nécessite un labyrinthe en mémoire)" << std::endl;
     std::cout << "-i ou --input <fichier> : Spécifie le fichier d'entrée (nécessaire pour utiliser un labyrinthe se trouvant dans un fichier texte)" << std::endl;
     std::cout << "-c ou --clear : Efface le(s) labyrinthe(s) en mémoire" << std::endl;
     std::cout << "-g ou --generate : Génère un labyrinthe" << std::endl;
     std::cout << "  -t ou --type <type> : Spécifie le type d'algorithme à utiliser pour la génération (cours, perso, par défaut : cours)" << std::endl;
     std::cout << "  -d ou --dimension <x> <y> : Spécifie les dimensions du labyrinthe à générer (par défaut : 10 10)" << std::endl;
     std::cout << "  -u ou --unperfect : Génère un labyrinthe imparfait (le labyrinthe généré est par défaut parfait)" << std::endl;
     std::cout << "-r ou --resolve : Résout un labyrinthe (nécessite un labyrinthe en mémoire)" << std::endl;
     std::cout << "  -a ou --algorithm <algorithme> : Spécifie l'algorithme à utiliser pour la résolution (aaa, bbb, par défaut : aaa)" << std::endl;
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
 * Affiche l'aide et retourne le code d'erreur
 * @param a Code d'erreur
 * @return Code d'erreur
 */
int help(std::string a, int b) {
    std::cout << "Error : " << a << std::endl;
    help();
    return b;
}

/**
 * Commande -o
 * @param file Fichier
 */
void writeMaze(char *file, Maze *maze) {
    std::cout << "Write" << std::endl;
    file = file;
    maze = maze;
}

/**
 * Commande -g
 * @param type Type d'algorithme
 * @param x Dimension x
 * @param y Dimension y
 * @param perfect Parfait
*/
void generateMaze(Maze *maze, std::string type, int x, int y, bool perfect) {
    *maze = Maze();
    // TODO : Générer un labyrinthe
    type = type;
    x = x;
    y = y;
    perfect = perfect;
}

/**
 * Commande -r
 * @param maze Labyrinthe
 * @param algorithm Algorithme
 */
void resolveMaze(Maze *maze, std::string algorithm) {
    std::cout << "Resolve" << std::endl;
    // TODO : Résoudre un labyrinthe
    maze = maze;
    algorithm = algorithm;
}

/**
 * Main
 * @param argc Nombre d'arguments
 * @param argv Arguments
 * @return Code d'erreur
 */
int main(int argc, char *argv[]) {
    if (argc < 2) return help(MAZE_COMMAND_ERROR);

    // Vérifie que le premier argument est une commande
    if (argv[1][0] != '-') {
        std::cout << "Usage:./main [-option] <instance_file>" << std::endl;
        return 1;
    }

    {
        bool mazeLoaded = false;
        Maze maze = Maze();
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) return help(MAZE_OK);
            else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--show") == 0) {
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                show(&maze);
            }
            else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
                std::ofstream file(argv[i + 1]);
                if (!file) {
                    std::cout << "File not found : " << argv[i + 1] << std::endl;
                    return 1;
                }
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                writeMaze(argv[i + 1], &maze);
                i++;
            }
            else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
                if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
                std::ifstream file(argv[i + 1]);
                if (!file) {
                    std::cout << "File not found : " << argv[i + 1] << std::endl;
                    return 1;
                }
                maze = Maze();
                read(argv[i + 1], &maze);
                mazeLoaded = true;
                i++;

                // std::cout << "Maze loaded" << std::endl;
                // for (int x = 0; x < maze.getWidth(); x++) {
                //     for (int y = 0; y < maze.getHeight(); y++) {
                //         Cell* cell = maze.getCell(x, y);
                //         if (cell->getWall(cell->NeighborsEnum::BOTTOM)) {
                //             std::cout << x << ' ' << y << ' ' << 'H' << std::endl;
                //         }
                //         if (cell->getWall(cell->NeighborsEnum::RIGHT)) {
                //             std::cout << x << ' ' << y << ' ' << 'V' << std::endl;
                //         }
                //     }
                // }
            }
            else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--clear") == 0) {
                std::cout << "Clear" << std::endl;
                maze.freeMaze();
                mazeLoaded = false;
            }
            else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--generate") == 0) {
                std::string type = "cours";
                int x = 10, y = 10;
                bool perfect = true;
                // FIXME
                // if (strcmp(argv[i + 1], "-t") == 0 || strcmp(argv[i + 1], "--type") == 0) {
                //     i++;
                //     if (i + 1 >= argc) {
                //         if (strcmp(argv[i + 1], "cours") == 0) {
                //             type = "cours";
                //         } else if (strcmp(argv[i + 1], "perso") == 0) {
                //             type = "perso";
                //         } else {
                //             return help(MAZE_COMMAND_ERROR);
                //         }
                //         i++;
                //     }
                // // }
                // if (strcmp(argv[i + 1], "-d") == 0 || strcmp(argv[i + 1], "--dimension") == 0) {
                //     i++;
                //     if (i + 2 >= argc) {
                //         x = atoi(argv[i + 1]);
                //         y = atoi(argv[i + 2]);
                //         i += 2;
                //     }
                // }
                // if (strcmp(argv[i + 1], "-u") == 0 || strcmp(argv[i + 1], "--unperfect") == 0) {
                //     perfect = false;
                //     i++;
                // }
                generateMaze(&maze, type, x, y, perfect);
                mazeLoaded = true;
            }
            else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--resolve") == 0) {
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                std::string algorithm = "aaa";
                if (strcmp(argv[i + 1], "-a") == 0 || strcmp(argv[i + 1], "--algorithm") == 0) {
                    i++;
                    if (i + 1 >= argc) {
                        if (strcmp(argv[i + 1], "aaa") == 0) {
                            algorithm = "aaa";
                        } else if (strcmp(argv[i + 1], "bbb") == 0) {
                            algorithm = "bbb";
                        } else {
                            return help(MAZE_COMMAND_ERROR);
                        }
                        i++;
                    }
                }
                resolveMaze(&maze, algorithm);
            }
            else {
                return help(argv[i], MAZE_COMMAND_ERROR);
            }
        }
    }

    return 0;
}
