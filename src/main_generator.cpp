#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "lib/algo/algo_backtracking.hpp"
#include "lib/algo/algo_diagonal.hpp"
#include "lib/algo/algo_fractal.hpp"
#include "lib/algo/algo_wallmaker.hpp"
#include "lib/maze.hpp"
#include "lib/reader.hpp"
#include "lib/show.hpp"
#include "lib/var.hpp"
#include "lib/writer.hpp"

/**
 * Affiche l'aide
 */
void help() {
    std::cout << "Options du programme" << std::endl;
    std::cout << "-------------------" << std::endl;

    std::cout << "Générales" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "  -h ou --help : Affiche cette aide" << std::endl;
    std::cout << "  -s ou --show : Affiche le labyrinthe en mémoire"
              << std::endl;
    std::cout << "  -o ou --output <fichier> : Spécifie le fichier où "
                 "sauvegarder le labyrinthe en mémoire"
              << std::endl;
    std::cout << "  -c ou --clear : Efface le labyrinthe en mémoire"
              << std::endl;
    std::cout << "    -cm ou --clear-maze : Nettoie les cellules du labyrinthe "
                 "en mémoire"
              << std::endl;

    std::cout << "\nGénération de labyrinthe" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "  -g ou --generate : Génère un labyrinthe (écrase le "
                 "labyrinthe en mémoire)"
              << std::endl;
    std::cout << "    -gs ou --generate-show : Génère un labyrinthe et "
                 "l'affiche pendant la génération"
              << std::endl;
    std::cout << "    -a ou --algorithm <algorithme> : Spécifie l'algorithme à "
                 "utiliser pour la génération (bt/breadthfirst, wm/wallmaker, "
                 "d/diagonal, f/fractal)"
              << std::endl;
    std::cout << "    -d ou --dimension <largeur> <hauteur> : Spécifie les "
                 "dimensions du labyrinthe à générer"
              << std::endl;
    std::cout << "    -u ou --unperfect : Génère un labyrinthe imparfait"
              << std::endl;
}

/**
 * Affiche l'aide et retourne le code d'erreur
 * @param a Code d'erreur
 * @return Code d'erreur
 */
int help(int error) {
    help();
    return error;
}

/**
 * Affiche l'aide et retourne le code d'erreur
 * @param a Code d'erreur
 * @return Code d'erreur
 */
int help(int error, std::string command) {
    std::cout << "Error : " << command << std::endl;
    return help(error);
}

/**
 * Commande -g
 * @param type Type d'algorithme
 * @param width Dimension en largeur
 * @param height Dimension en hauteur
 * @param perfect Parfait
 */
void generateMaze(Maze *maze, std::string algorithm, int width, int height,
                  bool isPerfect, Show *show) {
    std::cout << "Parameters of generation : algorithm=" << algorithm
              << ", width=" << width << ", height=" << height
              << ", isPerfect=" << isPerfect << std::endl;
    srand(time(0));
    clock_t start = clock();
    if (algorithm == "backtracking" || algorithm == "bt")
        algo_backtracking(maze, width, height, isPerfect, show);
    else if (algorithm == "wallmaker" || algorithm == "wm")
        algo_wallmaker(maze, width, height, isPerfect, show);
    else if (algorithm == "diagonal" || algorithm == "d")
        algo_diagonal(maze, width, height, isPerfect, show);
    else if (algorithm == "fractal" || algorithm == "f")
        algo_fractal(maze, width, isPerfect, show);
    else
        exit(MAZE_COMMAND_ERROR);
    clock_t end = clock();
    std::cout << "Generated in "
              << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms"
              << std::endl;
}

/**
 * Main
 * @param argc Nombre d'arguments
 * @param argv Arguments
 * @return Code d'erreur
 */
int main(const int argc, char *argv[]) {
    if (argc < 2) return help(MAZE_COMMAND_ERROR);

    // Vérifie que le premier argument est une commande
    if (argv[1][0] != '-') {
        std::cout << "Usage:./main [-option] [args]" << std::endl;
        return 1;
    }

    {
        bool mazeLoaded = false;
        Maze maze = Maze();
        Show show = Show(&maze);
        // Parcours les arguments
        for (int i = 1; i < argc; i++) {
            // Vérifie si l'argument est une commande
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
                return help(MAZE_OK);
            // Si l'utilisateur veut afficher le labyrinthe
            if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--show") == 0) {
                // Si aucun labyrinthe n'est chargé
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                show.create();
                while (show.isOpen()) {
                    show.update();
                }
            }
            // Si l'utilisateur veut sauvegarder le labyrinthe chargé en mémoire
            else if (strcmp(argv[i], "-o") == 0 ||
                     strcmp(argv[i], "--output") == 0) {
                // Si aucun fichier n'est spécifié
                if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
                std::ofstream file(argv[i + 1]);
                // Si le fichier n'existe pas
                if (!file) {
                    std::cout << "File not found : " << argv[i + 1]
                              << std::endl;
                    return 1;
                }
                // Si aucun labyrinthe n'est chargé
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                write(&maze, argv[i + 1]);
                i++;
            }
            // Si l'utilisateur veut effacer le labyrinthe chargé en mémoire
            else if (strcmp(argv[i], "-c") == 0 ||
                     strcmp(argv[i], "--clear") == 0 ||
                     strcmp(argv[i], "-cm") == 0 ||
                     strcmp(argv[i], "--clear-maze") == 0) {
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                if (strcmp(argv[i], "-cm") == 0 ||
                    strcmp(argv[i], "--clear-maze") == 0) {
                    std::cout << "Clear cells" << std::endl;
                    maze.clearMaze();
                } else {
                    std::cout << "Clear all" << std::endl;
                    mazeLoaded = false;
                    show.destroy();
                }
            }
            // Si l'utilisateur veut générer un labyrinthe
            else if (strcmp(argv[i], "-g") == 0 ||
                     strcmp(argv[i], "--generate") == 0 ||
                     strcmp(argv[i], "-gs") == 0 ||
                     strcmp(argv[i], "--generate-show") == 0) {
                const bool isShow = (strcmp(argv[i], "-gs") == 0 ||
                                     strcmp(argv[i], "--generate-show") == 0);
                std::string algorithm = "backtracking";
                int width = 10, height = 10;
                bool perfect = true;
                // Si l'utilisateur a spécifié des options
                while (i + 1 < argc && argv[i + 1][0] == '-' &&
                       ((strcmp(argv[i + 1], "-a") == 0 ||
                         strcmp(argv[i + 1], "--algorithm") == 0) ||
                        (strcmp(argv[i + 1], "-d") == 0 ||
                         strcmp(argv[i + 1], "--dimension") == 0) ||
                        (strcmp(argv[i + 1], "-u") == 0 ||
                         strcmp(argv[i + 1], "--unperfect") == 0))) {
                    if (i + 1 < argc) {
                        // Si l'utilisateur a spécifié le type d'algorithme
                        if (strcmp(argv[i + 1], "-a") == 0 ||
                            strcmp(argv[i + 1], "--algorithm") == 0) {
                            i++;
                            if (i + 1 < argc) {
                                if (strcmp(argv[i + 1], "backtracking") == 0 ||
                                    strcmp(argv[i + 1], "bt") == 0) {
                                    algorithm = "backtracking";
                                } else if (strcmp(argv[i + 1], "wallmaker") ==
                                               0 ||
                                           strcmp(argv[i + 1], "wm") == 0) {
                                    algorithm = "wallmaker";
                                } else if (strcmp(argv[i + 1], "diagonal") ==
                                               0 ||
                                           strcmp(argv[i + 1], "d") == 0) {
                                    algorithm = "diagonal";
                                } else if (strcmp(argv[i + 1], "fractal") ==
                                               0 ||
                                           strcmp(argv[i + 1], "f") == 0) {
                                    algorithm = "fractal";
                                } else {
                                    return help(MAZE_COMMAND_ERROR);
                                }
                                i++;
                            }
                        }
                    }
                    if (i + 1 < argc) {
                        // Si l'utilisateur a spécifié les dimensions du
                        // labyrinthe
                        if (strcmp(argv[i + 1], "-d") == 0 ||
                            strcmp(argv[i + 1], "--dimension") == 0) {
                            i++;
                            if (i + 2 < argc) {
                                width = atoi(argv[i + 1]);
                                height = atoi(argv[i + 2]);
                                i += 2;
                            }
                        }
                    }
                    if (i + 1 < argc) {
                        // Si l'utilisateur a spécifié que le labyrinthe n'est
                        // pas parfait
                        if (strcmp(argv[i + 1], "-u") == 0 ||
                            strcmp(argv[i + 1], "--unperfect") == 0) {
                            perfect = false;
                            i++;
                        }
                    }
                }
                //                maze.setWidthHeight(width, height);
                if (isShow) {
                    //                    show.create();
                    generateMaze(&maze, algorithm, width, height, perfect,
                                 &show);
                    while (show.isOpen()) {
                        show.update();
                    }
                } else {
                    generateMaze(&maze, algorithm, width, height, perfect,
                                 nullptr);
                }
                mazeLoaded = true;
            }
            // Si l'utilisateur a spécifié une commande inconnue
            else {
                return help(MAZE_COMMAND_ERROR, argv[i]);
            }
        }
    }

    return 0;
}
