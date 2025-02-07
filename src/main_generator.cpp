#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "lib/algo/back_tracking.hpp"
#include "lib/algo/diagonal.hpp"
#include "lib/algo/fractal.hpp"
#include "lib/algo/wall_maker.hpp"
#include "lib/maze.hpp"
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
    std::cout << "  -i ou --input <fichier> : Spécifie le fichier d'un labyrinthe à charger en mémoire" << std::endl;
    std::cout << "  -s ou --show : Affiche le labyrinthe en mémoire" << std::endl;
    std::cout << "  -o ou --output <fichier> : Spécifie le fichier où sauvegarder le labyrinthe en mémoire" << std::endl;
    std::cout << "  -c ou --clear : Efface le labyrinthe en mémoire" << std::endl;
    std::cout << "  -cm ou --clear-maze : Nettoie les cellules du labyrinthe en mémoire" << std::endl;

    std::cout << "\nGénération de labyrinthe" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "  -g ou --generate : Génère un labyrinthe (écrase le labyrinthe en mémoire)" << std::endl;
    std::cout << "  -gs ou --generate-show : Génère un labyrinthe et l'affiche pendant la génération" << std::endl;
    std::cout << "    -a ou --algorithm <algorithme> : Spécifie l'algorithme à utiliser pour la génération (bt, wm, d, f)" << std::endl;
    std::cout << "    -d ou --dimension <largeur> <hauteur> : Spécifie les dimensions du labyrinthe à générer" << std::endl;
    std::cout << "    -i ou --imperfect : Génère un labyrinthe imparfait" << std::endl;
    std::cout << "      -p ou --probability <probabilité> : Spécifie la probabilité de suppression d'un mur pour un labyrinthe imparfait (0.0-1.0)" << std::endl;
}

/**
 * Affiche l'aide et retourne le code d'erreur
 * @param error Code d'erreur
 * @return Code d'erreur
 */
int help(const int error) {
    help();
    return error;
}

/**
 * Affiche l'aide et retourne le code d'erreur
 * @param error Code d'erreur
 * @param command Commande
 * @return Code d'erreur
 */
int help(const int error, const std::string& command) {
    std::cout << "Error : " << command << std::endl;
    return help(error);
}

/**
 * Commande -g
 * @param maze Labyrinthe
 * @param algorithm Algorithme
 * @param width Dimension en largeur
 * @param height Dimension en hauteur
 * @param isPerfect Parfait
 * @param probability Probabilité
 * @param show Affichage
 */
void generateMaze(Maze *maze, const std::string& algorithm, const int width, const int height,
                  const bool isPerfect, const double probability, Show *show) {
    std::cout << "Parameters of generation : algorithm=" << algorithm
              << ", width=" << width << ", height=" << height
              << ", isPerfect=" << isPerfect;
    if (!isPerfect) std::cout << ", probability=" << probability;
    std::cout << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    if (algorithm == "back_tracking" || algorithm == "bt")
        algo_back_tracking(maze, width, height, isPerfect, probability, show);
    else if (algorithm == "wall_maker" || algorithm == "wm")
        algo_wall_maker(maze, width, height, isPerfect, probability, show);
    else if (algorithm == "diagonal" || algorithm == "d")
        algo_diagonal(maze, width, height, isPerfect, probability, show);
    else if (algorithm == "fractal" || algorithm == "f")
        algo_fractal(maze, width, isPerfect, probability, show);
    else
        exit(MAZE_COMMAND_ERROR);
    const auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Generated in "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << "."
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() % 1000
        << "s" << std::endl;
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

    bool mazeLoaded = false;
    auto maze = Maze();
    auto show = Show(&maze);
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
                return MAZE_COMMAND_ERROR;
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
            // Si aucun labyrinthe n'est chargé
            if (!mazeLoaded) {
                std::cout << "No maze loaded" << std::endl;
                return MAZE_COMMAND_ERROR;
            }
            std::ofstream file(argv[i + 1]);
            // Si le fichier n'existe pas
            if (!file) {
                std::cout << "File not found : " << argv[i + 1]
                          << std::endl;
                return MAZE_FILE_ERROR;
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
                return MAZE_COMMAND_ERROR;
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
            std::string algorithm = "back_tracking";
            int width = 10, height = 10;
            bool perfect = true;
            double probability = 0.01;
            // Si l'utilisateur a spécifié des options
            while (i + 1 < argc && argv[i + 1][0] == '-' &&
                   ((strcmp(argv[i + 1], "-a") == 0 ||
                     strcmp(argv[i + 1], "--algorithm") == 0) ||
                    (strcmp(argv[i + 1], "-d") == 0 ||
                     strcmp(argv[i + 1], "--dimension") == 0) ||
                    (strcmp(argv[i + 1], "-i") == 0 ||
                     strcmp(argv[i + 1], "--imperfect") == 0))) {
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié le type d'algorithme
                    if (strcmp(argv[i + 1], "-a") == 0 ||
                        strcmp(argv[i + 1], "--algorithm") == 0) {
                        i++;
                        if (i + 1 < argc) {
                            if (strcmp(argv[i + 1], "back_tracking") == 0 ||
                                strcmp(argv[i + 1], "bt") == 0) {
                                algorithm = "back_tracking";
                            } else if (strcmp(argv[i + 1], "wall_maker") ==
                                           0 ||
                                       strcmp(argv[i + 1], "wm") == 0) {
                                algorithm = "wall_maker";
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
                            width = std::stoi(argv[i + 1]);
                            height = std::stoi(argv[i + 2]);
                            i += 2;
                        }
                    }
                }
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié que le labyrinthe n'est
                    // pas parfait
                    if (strcmp(argv[i + 1], "-i") == 0 ||
                        strcmp(argv[i + 1], "--imperfect") == 0) {
                        perfect = false;
                        i++;
                    }
                }
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié la probabilité de mur
                    if (strcmp(argv[i + 1], "-p") == 0 ||
                        strcmp(argv[i + 1], "--probability") == 0) {
                        i++;
                        if (i + 1 < argc) {
                            probability = std::stod(argv[i + 1]);
                            if (probability <= 0.0 || probability > 1.0) {
                                return help(MAZE_COMMAND_ERROR);
                            }
                            i++;
                        } else {
                            return help(MAZE_COMMAND_ERROR);
                        }
                    }
                }
            }
            if (isShow) {
                generateMaze(&maze, algorithm, width, height, perfect, probability,
                             &show);
                while (show.isOpen()) {
                    show.update();
                }
            } else {
                generateMaze(&maze, algorithm, width, height, perfect, probability,
                             nullptr);
            }
            mazeLoaded = true;
        }
        // Si l'utilisateur a spécifié une commande inconnue
        else {
            return help(MAZE_COMMAND_ERROR, argv[i]);
        }
    }
    return 0;
}
