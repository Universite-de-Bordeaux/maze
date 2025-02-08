#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "lib/checker/depth_first.hpp"
#include "lib/game/fog.hpp"
#include "lib/game/fog_hand.hpp"
#include "lib/game/walk.hpp"
#include "lib/maze.hpp"
#include "lib/reader.hpp"
#include "lib/show.hpp"
#include "lib/solver/breadth_first.hpp"
#include "lib/solver/depth_first.hpp"
#include "lib/var.hpp"
#include "lib/writer.hpp"

/**
 * Affiche l'aide
 */
void help() {
    std::cout << "Options du programme" << std::endl;
    std::cout << "-------------------" << std::endl;

    std::cout << "Générales" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "  -h ou --help : Affiche cette aide" << std::endl;
    std::cout << "  -i ou --input <fichier> : Spécifie le fichier d'un "
                 "labyrinthe à charger en mémoire"
              << std::endl;
    std::cout << "  -s ou --show : Affiche le labyrinthe en mémoire"
              << std::endl;
    std::cout << "    -f ou --framerate <framerate> : Spécifie le framerate de "
                 "l'affichage (par défaut : 60)"
              << std::endl;
    std::cout
        << "    -ds ou --delay-show <delay> : Spécifie le délai d'affichage "
           "entre chaque cellule en millisecondes (par défaut : 0.0 (précis à "
           "la nanoseconde))"
        << std::endl;
    std::cout << "  -o ou --output <fichier> : Spécifie le fichier où "
                 "sauvegarder le labyrinthe en mémoire"
              << std::endl;
    std::cout << "  -c ou --clear : Efface le labyrinthe en mémoire"
              << std::endl;
    std::cout << "  -cm ou --clear-maze : Nettoie les cellules du labyrinthe "
                 "en mémoire"
              << std::endl;

    std::cout << "\nRésolution de labyrinthe" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "  -r ou --resolve : Résout le labyrinthe en mémoire"
              << std::endl;
    std::cout << "  -rs ou --resolve-show : Résout le labyrinthe en mémoire et "
                 "l'affiche pendant la résolution"
              << std::endl;
    std::cout << "    -a ou --algorithm <algorithme> : Spécifie l'algorithme à "
                 "utiliser pour la résolution (dfr/depth_first_right, "
                 "dfl/depth_first_left, bf/breadth_first)"
              << std::endl;

    std::cout << "\nVérification de labyrinthe" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "  -v ou --verify : Vérifie si un labyrinthe est parfait"
              << std::endl;
    std::cout << "  -vs ou --verify-show : Vérifie si un labyrinthe est valide "
                 "et l'affiche pendant la vérification"
              << std::endl;
    std::cout << "    -p ou --perfect : Vérifie si un labyrinthe est parfait"
              << std::endl;
    std::cout << "    -a ou --algorithm <algorithme> : Spécifie l'algorithme à "
                 "utiliser pour la vérification (dfr/depth_first_right, "
                 "dfl/depth_first_left, bf/breadth_first)"
              << std::endl;

    std::cout << "\nJeux de labyrinthe" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "  -g ou --game : Joue à un jeu de labyrinthe" << std::endl;
    std::cout << "  -gs ou --game-show : Joue à un jeu de labyrinthe et "
                 "l'affiche pendant le jeu"
              << std::endl;
    std::cout << "    -t ou --type <type> : Spécifie le type de jeu à jouer "
                 "(f/fog, fr/fog_right, fl/fog_left, w/walk, wg/walk_ghost)"
              << std::endl;
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
 * Commande pour résoudre un labyrinthe
 * @param maze Labyrinthe
 * @param algorithm Algorithme
 * @param show Affichage
 */
void resolveMaze(Maze *maze, const std::string &algorithm, Show *show) {
    std::cout << "Parameters of resolution : algorithm=" << algorithm
              << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    if (algorithm == "depth_first_right" || algorithm == "dfr")
        solver_depth_first(maze, show, false);
    else if (algorithm == "depth_first_left" || algorithm == "dfl")
        solver_depth_first(maze, show, true);
    else if (algorithm == "breadth_first" || algorithm == "bf")
        solver_breadth_first(maze, show);
    else
        exit(MAZE_COMMAND_ERROR);
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout
        << "Resolved in "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << "."
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                   .count() %
               1000
        << "s" << std::endl;
}

/**
 * Commande pour vérifier un labyrinthe
 * @param maze Labyrinthe
 * @param algorithm Algorithme
 * @param perfect Parfait
 * @param show Affichage
 */
void checkMaze(Maze *maze, const std::string &algorithm, const bool perfect,
               Show *show) {
    std::cout << "Parameters of checking : algorithm=" << algorithm
              << ", perfect=" << perfect << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    if (algorithm == "depth_first_right" || algorithm == "dfr")
        checker_depth_first(maze, perfect, show);  // TODO
    else if (algorithm == "depth_first_left" || algorithm == "dfl")
        checker_depth_first(maze, perfect, show);
    //    else if (algorithm == "breadth_first" || algorithm == "bf") // TODO
    //    checker_breadth_first(maze, perfect, show); // TODO
    else
        exit(MAZE_COMMAND_ERROR);
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout
        << "Resolved in "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << "."
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                   .count() %
               1000
        << "s" << std::endl;
}

/**
 * Commande pour jouer à un jeu de labyrinthe
 * @param maze Labyrinthe
 * @param type Type de jeu
 * @param show Affichage
 */
void gameMaze(Maze *maze, const std::string &type, Show *show) {
    std::cout << "Parameters of game : type=" << type << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    int steps = 0;
    if (type == "fog" || type == "f") {
        steps = game_fog(maze, show);
    } else if (type == "fog_right" || type == "fr") {
        steps = game_fog_hand(maze, show, false);
    } else if (type == "fog_left" || type == "fl") {
        steps = game_fog_hand(maze, show, true);
    } else if (type == "walk" || type == "w") {
        steps = game_walk(maze, show, false);
    } else if (type == "walk_ghost" || type == "wg") {
        steps = game_walk(maze, show, true);
    } else {
        exit(MAZE_COMMAND_ERROR);
    }
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout
        << "Resolved in "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << "."
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                   .count() %
               1000
        << "s with " << steps << " steps" << std::endl;
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
        std::cout << "Usage:./main [-option] [args]" << std::endl;
        return MAZE_COMMAND_ERROR;
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
                refreshShow(&show);
            }
            show.destroy();
        } else if (strcmp(argv[i], "-f") == 0 ||
                   strcmp(argv[i], "--framerate") == 0) {
            if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
            show.setRefreshRate(std::stoi(argv[i + 1]));
            i++;
        } else if (strcmp(argv[i], "-ds") == 0 ||
                   strcmp(argv[i], "--delay-show") == 0) {
            if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
            show.setDelay(std::stof(argv[i + 1]));
            i++;
        }
        // Vérifie si le labyrinthe est valide
        else if (strcmp(argv[i], "-v") == 0 ||
                 strcmp(argv[i], "--verify") == 0 ||
                 strcmp(argv[i], "-vs") == 0 ||
                 strcmp(argv[i], "--verify-show") == 0) {
            // Si aucun labyrinthe n'est chargé
            if (!mazeLoaded) {
                std::cout << "No maze loaded" << std::endl;
                return MAZE_COMMAND_ERROR;
            }
            bool isShow = strcmp(argv[i], "-vs") == 0 ||
                          strcmp(argv[i], "--verify-show") == 0;
            bool perfect = false;
            std::string algorithm = "dfl";
            while (i + 1 < argc && argv[i + 1][0] == '-' &&
                   ((strcmp(argv[i + 1], "-p") == 0 ||
                     strcmp(argv[i + 1], "--perfect") == 0) ||
                    (strcmp(argv[i + 1], "-a") == 0 ||
                     strcmp(argv[i + 1], "--algorithm") == 0))) {
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié que le labyrinthe doit être
                    // parfait
                    if (strcmp(argv[i + 1], "-p") == 0 ||
                        strcmp(argv[i + 1], "--perfect") == 0) {
                        perfect = true;
                    }
                    // Si l'utilisateur a spécifié l'algorithme à utiliser
                    else if (strcmp(argv[i + 1], "-a") == 0 ||
                             strcmp(argv[i + 1], "--algorithm") == 0) {
                        i++;
                        if (i + 1 < argc) {
                            if (strcmp(argv[i + 1], "depth_first_right") == 0 ||
                                strcmp(argv[i + 1], "dfr") == 0) {
                                algorithm = "depth_first_right";
                            } else if (strcmp(argv[i + 1],
                                              "depth_first_left") == 0 ||
                                       strcmp(argv[i + 1], "dfl") == 0) {
                                algorithm = "depth_first_left";
                            } else if (strcmp(argv[i + 1], "breadth_first") ==
                                           0 ||
                                       strcmp(argv[i + 1], "bf") == 0) {
                                algorithm = "breadth_first";
                            } else {
                                return help(MAZE_COMMAND_ERROR);
                            }
                            i++;
                        }
                    }
                }
                i++;
            }
            if (isShow) {
                show.create();
                checkMaze(&maze, algorithm, perfect, &show);
                while (show.isOpen()) {
                    refreshShow(&show);
                }
                show.destroy();
            } else {
                checkMaze(&maze, algorithm, perfect, nullptr);
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
                std::cout << "File not found : " << argv[i + 1] << std::endl;
                return MAZE_FILE_ERROR;
            }
            write(&maze, argv[i + 1]);
            i++;
        }
        // Si l'utilisateur veut charger un labyrinthe depuis un fichier
        else if (strcmp(argv[i], "-i") == 0 ||
                 strcmp(argv[i], "--input") == 0) {
            // Si aucun fichier n'est spécifié
            if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
            std::ifstream file(argv[i + 1]);
            // Si le fichier n'existe pas
            if (!file) {
                std::cout << "File not found : " << argv[i + 1] << std::endl;
                return MAZE_FILE_ERROR;
            }
            maze = Maze();
            read(argv[i + 1], &maze);
            mazeLoaded = true;
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
            }
        }
        // Si l'utilisateur veut résoudre un labyrinthe
        else if (strcmp(argv[i], "-r") == 0 ||
                 strcmp(argv[i], "--resolve") == 0 ||
                 strcmp(argv[i], "-rs") == 0 ||
                 strcmp(argv[i], "--resolve-show") == 0) {
            bool isShow = (strcmp(argv[i], "-rs") == 0 ||
                           strcmp(argv[i], "--resolve-show") == 0);
            // Si aucun labyrinthe n'est chargé
            if (!mazeLoaded) {
                std::cout << "No maze loaded" << std::endl;
                return MAZE_COMMAND_ERROR;
            }
            std::string algorithm = "depth_first_left";
            // Si l'utilisateur a spécifié l'algorithme
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "-a") == 0 ||
                    strcmp(argv[i + 1], "--algorithm") == 0) {
                    i++;
                    if (i + 1 < argc) {
                        if (strcmp(argv[i + 1], "depth_first_right") == 0 ||
                            strcmp(argv[i + 1], "dfr") == 0) {
                            algorithm = "depth_first_right";
                        } else if (strcmp(argv[i + 1], "depth_first_left") ==
                                       0 ||
                                   strcmp(argv[i + 1], "dfl") == 0) {
                            algorithm = "depth_first_left";
                        } else if (strcmp(argv[i + 1], "breadth_first") == 0 ||
                                   strcmp(argv[i + 1], "bf") == 0) {
                            algorithm = "breadth_first";
                        } else {
                            return help(MAZE_COMMAND_ERROR);
                        }
                        i++;
                    } else {
                        return help(MAZE_COMMAND_ERROR);
                    }
                }
            }
            if (isShow) {
                show.create();
                resolveMaze(&maze, algorithm, &show);
                while (show.isOpen()) {
                    refreshShow(&show);
                }
                show.destroy();
            } else {
                resolveMaze(&maze, algorithm, nullptr);
            }
        }
        // Si l'utilisateur veut jouer à un jeu de labyrinthe
        else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--game") == 0 ||
                 strcmp(argv[i], "-gs") == 0 ||
                 strcmp(argv[i], "--game-show") == 0) {
            bool isShow = (strcmp(argv[i], "-gs") == 0 ||
                           strcmp(argv[i], "--game-show") == 0);
            // Si aucun labyrinthe n'est chargé
            if (!mazeLoaded) {
                std::cout << "No maze loaded" << std::endl;
                return MAZE_COMMAND_ERROR;
            }
            std::string type = "fog";
            // Si l'utilisateur a spécifié le type de jeu
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "-t") == 0 ||
                    strcmp(argv[i + 1], "--type") == 0) {
                    i++;
                    if (i + 1 < argc) {
                        if (strcmp(argv[i + 1], "fog") == 0 ||
                            strcmp(argv[i + 1], "f") == 0) {
                            type = "fog";
                        } else if (strcmp(argv[i + 1], "fog_right") == 0 ||
                                   strcmp(argv[i + 1], "fr") == 0) {
                            type = "fog_right";
                        } else if (strcmp(argv[i + 1], "fog_left") == 0 ||
                                   strcmp(argv[i + 1], "fl") == 0) {
                            type = "fog_left";
                        } else if (strcmp(argv[i + 1], "walk") == 0 ||
                                   strcmp(argv[i + 1], "w") == 0) {
                            type = "walk";
                        } else if (strcmp(argv[i + 1], "walk_ghost") == 0 ||
                                   strcmp(argv[i + 1], "wg") == 0) {
                            type = "walk_ghost";
                        } else {
                            return help(MAZE_COMMAND_ERROR);
                        }
                        i++;
                    } else {
                        return help(MAZE_COMMAND_ERROR);
                    }
                }
            }
            if (isShow) {
                show.create();
                gameMaze(&maze, type, &show);
                while (show.isOpen()) {
                    refreshShow(&show);
                }
                show.destroy();
            } else {
                gameMaze(&maze, type, nullptr);
            }
        }
        // Si l'utilisateur a spécifié une commande inconnue
        else {
            return help(MAZE_COMMAND_ERROR, argv[i]);
        }
    }

    return 0;
}
