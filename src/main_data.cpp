#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "lib/algo/back_tracking.hpp"
#include "lib/algo/diagonal.hpp"
#include "lib/algo/fractal.hpp"
#include "lib/algo/wall_maker.hpp"
#include "lib/game/fog.hpp"
#include "lib/game/fog_hand.hpp"
#include "lib/maze.hpp"
#include "lib/stack.hpp"
#include "lib/var.hpp"
#include "lib/writer.hpp"

/**
 * Affiche la documentation d'aide pour l'application de génération
 */
void help() {
    std::cout << "============================================================="
                 "====\n";
    std::cout << "=                        MAZE DATA APPLICATION              "
                 "      =\n";
    std::cout << "============================================================="
                 "====\n";
    std::cout << "\n";

    std::cout << "Usage : ./maze_generator.out [-option] [arguments]\n";
    std::cout << "\n";

    std::cout << "OPTIONS\n";
    std::cout << "------------------------------\n";
    std::cout << "-h, --help                    Affiche cette documentation\n";
    std::cout << "-ol, --output-latex <fichier> Sauvegarde les statistiques "
                 "dans un fichier LaTeX\n";
    std::cout << "-os, --output-stats <fichier> Sauvegarde les statistiques "
                 "dans un fichier texte\n";
    std::cout
        << "-ng, --nb-generate <n>        Génère n labyrinthes (défaut : 1)\n";
    std::cout << "-nu, --nb-uses <n>            Utilise n fois le labyrinthe "
                 "(défaut : 1)\n";

    std::cout << "GENERATION\n";
    std::cout << "------------------------------\n";
    std::cout << "-g, --generate                Génère un labyrinthe parfait\n";
    std::cout << "  -a, --algorithm <algo>      Sélectionne l'algorithme de "
                 "génération\n";
    std::cout << "    Algorithmes disponibles : bt, wm, d, f\n";
    std::cout << "                              bt : back_tracking (défaut)\n";
    std::cout << "                              wm : wall_maker\n";
    std::cout << "                              d : diagonal\n";
    std::cout << "                              f : fractal\n";
    std::cout << "  -d, --dimension <w> <h>     Définit les dimensions du "
                 "labyrinthe\n";
    std::cout
        << "  -i, --imperfect             Génère un labyrinthe imparfait\n";
    std::cout << "    -p, --probability <p>     Définit la probabilité de "
                 "suppression de murs [0.0-1.0]\n";
    std::cout << "\n";

    std::cout << "JEU ET VISITE\n";
    std::cout << "------------------------------\n";
    std::cout << "-ga, --game                    Lance le jeu ou la visite du "
                 "labyrinthe\n";
    std::cout << "  -t, --type <type>           Sélectionne le type de jeu ou "
                 "de visite\n";
    std::cout << "    Types disponibles :       f, fr, fl\n";
    std::cout << "                              f : fog (default)\n";
    std::cout << "                              fr : fog_right\n";
    std::cout << "                              fl : fog_left\n";
    std::cout << "\n";

    std::cout << "Pour plus d'informations, veuillez consulter la "
                 "documentation complète.\n";
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
int help(const int error, const std::string &command) {
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
void generateMaze(Maze *maze, const std::string &algorithm, const int width,
                  const int height, const bool isPerfect,
                  const double probability, Show *show) {
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
    // const auto end = std::chrono::high_resolution_clock::now();
    // std::cout
    //     << "Generated in "
    //     << std::chrono::duration_cast<std::chrono::seconds>(end -
    //     start).count()
    //     << "."
    //     << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
    //                .count() %
    //            1000
    //     << "s" << std::endl;
}

/**
 * Commande pour jouer à un jeu de labyrinthe
 * @param maze Labyrinthe
 * @param type Type de jeu
 * @param show Affichage
 */
int gameMaze(Maze *maze, const std::string &type, Show *show) {
    std::cout << "Parameters of game : type=" << type << std::endl;
    // const auto start = std::chrono::high_resolution_clock::now();
    int steps = 0;
    if (type == "fog" || type == "f") {
        steps = game_fog(maze, show);
    } else if (type == "fog_right" || type == "fr") {
        steps = game_fog_hand(maze, show, false);
    } else if (type == "fog_left" || type == "fl") {
        steps = game_fog_hand(maze, show, true);
    } else {
        exit(MAZE_COMMAND_ERROR);
    }
    // const auto end = std::chrono::high_resolution_clock::now();
    // std::cout
    //     << "Resolved in "
    //     << std::chrono::duration_cast<std::chrono::seconds>(end -
    //     start).count()
    //     << "."
    //     << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
    //                .count() %
    //            1000
    //     << "s with " << steps << " steps" << std::endl;
    return steps;
}

/**
 * Main
 * @param argc Nombre d'arguments
 * @param argv Arguments
 * @return Code d'erreur
 */
int main(const int argc, char *argv[]) {
    if (argc < 2) return help(MAZE_COMMAND_ERROR);

    if (argv[1][0] != '-') {
        std::cout << "Usage:./main [-option] [args]" << std::endl;
        return MAZE_COMMAND_ERROR;
    }
    uint nbMazeToGenerate = 1;
    uint nbUsesMaze = 1;
    Stack algorithms;
    int width = 10, height = 10;
    bool perfect = true;
    double probability = 0.01;
    auto types = Stack();
    bool startInitiated = false;
    int startX;
    int startY;
    bool endInitiated = false;
    int endX;
    int endY;
    std::string outputLatex;
    std::string outputStats;

    // Parcours les arguments
    for (int i = 1; i < argc; i++) {
        // Vérifie si l'argument est une commande
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            return help(MAZE_OK);
        // Si l'utilisateur veut afficher le labyrinthe
        if (strcmp(argv[i], "-ps") == 0 ||
            strcmp(argv[i], "--player-start") == 0) {
            if (i + 2 >= argc) return help(MAZE_COMMAND_ERROR);
            long double x_tmp = std::stold(argv[i + 1]);
            long double y_tmp = std::stold(argv[i + 2]);
            if (x_tmp < 0)
                startX =
                    static_cast<int>(static_cast<long double>(width) + x_tmp);
            else if (x_tmp > 0 && x_tmp < 1)
                startX =
                    static_cast<int>(static_cast<long double>(width) * x_tmp);
            else
                startX = static_cast<int>(x_tmp);
            if (y_tmp < 0)
                startY =
                    static_cast<int>(static_cast<long double>(height) + y_tmp);
            else if (y_tmp > 0 && y_tmp < 1)
                startY =
                    static_cast<int>(static_cast<long double>(height) * y_tmp);
            else
                startY = static_cast<int>(y_tmp);
            startInitiated = true;
            i += 2;
        } else if (strcmp(argv[i], "-pe") == 0 ||
                   strcmp(argv[i], "--player-end") == 0) {
            if (i + 2 >= argc) return help(MAZE_COMMAND_ERROR);
            long double x_tmp = std::stold(argv[i + 1]);
            long double y_tmp = std::stold(argv[i + 2]);
            if (x_tmp < 0)
                endX =
                    static_cast<int>(static_cast<long double>(width) + x_tmp);
            else if (x_tmp > 0 && x_tmp < 1)
                endX =
                    static_cast<int>(static_cast<long double>(width) * x_tmp);
            else
                endX = static_cast<int>(x_tmp);
            if (y_tmp < 0)
                endY =
                    static_cast<int>(static_cast<long double>(height) + y_tmp);
            else if (y_tmp > 0 && y_tmp < 1)
                endY =
                    static_cast<int>(static_cast<long double>(height) * y_tmp);
            else
                endY = static_cast<int>(y_tmp);
            endInitiated = true;
            i += 2;
        }  // Si l'utilisateur a précisé le nombre de labyrinthes à générer
        else if (strcmp(argv[i], "-ng") == 0 ||
                 strcmp(argv[i], "--number-generations") == 0) {
            if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
            const int nbMaze = std::atoi(argv[i + 1]);
            if (nbMaze > 0)
                nbMazeToGenerate = nbMaze;
            else
                return help(MAZE_COMMAND_ERROR);
            i++;
        } else if (strcmp(argv[i], "-nu") == 0 ||
                   strcmp(argv[i], "--number-uses") == 0) {
            if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
            const int nbUses = std::atoi(argv[i + 1]);
            if (nbUses > 0)
                nbUsesMaze = nbUses;
            else
                return help(MAZE_COMMAND_ERROR);
            i++;
        } else if (strcmp(argv[i], "-g") == 0 ||
                   strcmp(argv[i], "--generate") == 0) {
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
                                std::string *algo =
                                    new std::string("back_tracking");
                                algorithms.push(algo);
                            } else if (strcmp(argv[i + 1], "wall_maker") == 0 ||
                                       strcmp(argv[i + 1], "wm") == 0) {
                                std::string *algo =
                                    new std::string("wall_maker");
                                algorithms.push(algo);
                            } else if (strcmp(argv[i + 1], "diagonal") == 0 ||
                                       strcmp(argv[i + 1], "d") == 0) {
                                std::string *algo = new std::string("diagonal");
                                algorithms.push(algo);
                            } else if (strcmp(argv[i + 1], "fractal") == 0 ||
                                       strcmp(argv[i + 1], "f") == 0) {
                                std::string *algo = new std::string("fractal");
                                algorithms.push(algo);
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
        }
        // Vérifie si le labyrinthe est valide
        // Si l'utilisateur veut sauvegarder le labyrinthe chargé en mémoire
        else if (strcmp(argv[i], "-ol") == 0 ||
                 strcmp(argv[i], "--output-latex") == 0) {
            // Si aucun fichier n'est spécifié
            if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
            outputLatex = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-os") == 0 ||
                   strcmp(argv[i], "--output-stats") == 0) {
            // Si aucun fichier n'est spécifié
            if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
            outputStats = argv[i + 1];
            i++;
        }
        // Si l'utilisateur veut jouer à un jeu de labyrinthe
        else if (strcmp(argv[i], "-ga") == 0 ||
                 strcmp(argv[i], "--game") == 0) {
            // Si l'utilisateur a spécifié le type de jeu
            while (i + 1 < argc && argv[i + 1][0] == '-' &&
                   (strcmp(argv[i + 1], "-t") == 0 ||
                    strcmp(argv[i + 1], "--type") == 0)) {
                i++;
                if (i + 1 < argc) {
                    if (strcmp(argv[i + 1], "fog") == 0 ||
                        strcmp(argv[i + 1], "f") == 0) {
                        std::string *type = new std::string("fog");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "fog_right") == 0 ||
                               strcmp(argv[i + 1], "fr") == 0) {
                        std::string *type = new std::string("fog_right");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "fog_left") == 0 ||
                               strcmp(argv[i + 1], "fl") == 0) {
                        std::string *type = new std::string("fog_left");
                        types.push(type);
                    } else {
                        return help(MAZE_COMMAND_ERROR);
                    }
                    i++;
                } else {
                    return help(MAZE_COMMAND_ERROR);
                }
            }
        }
        // Si l'utilisateur a spécifié une commande inconnue
        else {
            return help(MAZE_COMMAND_ERROR, argv[i]);
        }
    }
    auto maze = Maze();
    std::ofstream fileLatex(outputLatex);
    std::ofstream fileStats(outputStats);

    while (!algorithms.empty()) {
        std::string *algorithm = static_cast<std::string *>(algorithms.top());
        algorithms.pop();
        for (int i = 0; i < nbMazeToGenerate; i++) {
            generateMaze(&maze, *algorithm, width, height, perfect, probability,
                         nullptr);
            if (startInitiated) maze.setStart(startX, startY);
            if (endInitiated) maze.setEnd(endX, endY);

            maze.setStart(startX, startY);
            maze.setEnd(endX, endY);
            for (int j = 0; j < types.size(); j++) {
                std::string *type = static_cast<std::string *>(types.get(j));
                for (int k = 0; k < nbUsesMaze; k++) {
                    int steps = gameMaze(&maze, *type, nullptr);
                    std::cout << "Maze " << i << " : game " << k
                              << " resolved in " << steps << " steps"
                              << std::endl;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}