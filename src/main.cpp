#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "lib/checker/breadth_first.hpp"
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
 * Affiche la documentation d'aide pour l'application
 */
void help() {
    std::cout << "============================================================="
                 "====\n";
    std::cout << "=                          MAZE APPLICATION                  "
                 "   =\n";
    std::cout << "============================================================="
                 "====\n";
    std::cout << "\n";

    std::cout << "Usage : ./maze.out [-option] [arguments]\n";
    std::cout << "\n";

    std::cout << "OPTIONS\n";
    std::cout << "------------------------------\n";
    std::cout << "-h, --help                    Affiche cette documentation\n";
    std::cout << "-i, --input <fichier>         Charge un labyrinthe depuis un "
                 "fichier\n";
    std::cout << "-o, --output <fichier>        Sauvegarde le labyrinthe dans "
                 "un fichier\n";
    std::cout
        << "-c, --clear                   Efface complètement le labyrinthe\n";
    std::cout << "-cm, --clear-maze             Efface uniquement les cellules "
                 "du labyrinthe\n";
    std::cout << "\n";

    std::cout << "AFFICHAGE\n";
    std::cout << "------------------------------\n";
    std::cout << "-s, --show                    Affiche le labyrinthe\n";
    std::cout
        << "-f, --framerate <fps>         Définit le framerate d'affichage\n";
    std::cout << "-ds, --delay-show <ms>        Définit le délai entre chaque "
                 "mise à jour\n";
    std::cout << "-lf, --low-freq               Affiche le labyrinthe à basse "
                 "fréquence\n";
    std::cout << "\n";

    std::cout << "      RACCOURCIS CLAVIER\n";
    std::cout << "      ------------------------\n";
    std::cout << "      Echap                   Ferme l'affichage\n";
    std::cout << "      Espace                  Met en pause le programme\n";
    std::cout
        << "      D                       Rafraîchit toutes les cellules\n";
    std::cout << "      R                       Réinitialise les paramètres "
                 "d'affichage\n";
    std::cout << "      L                       Inverse la fréquence "
                 "d'affichage ( haute/basse)\n";
    std::cout << "      +                       Augmente le framerate\n";
    std::cout << "      -                       Diminue le framerate\n";
    std::cout
        << "      *                       Augmente le délai d'affichage\n";
    std::cout << "      /                       Diminue le délai d'affichage\n";
    std::cout << "\n";

    std::cout << "      SOURIS\n";
    std::cout << "      ------------------------\n";
    std::cout << "      Clic gauche +           Déplace la vue du labyrinthe "
                 "déplacement souris (seulement si le labyrinthe est inférieur "
                 "à 100 x 100)\n";
    std::cout
        << "      Molette                 Zoom avant/arrière sur l'affichage "
           "(seulement si le labyrinthe est inférieur à 100 x 100)\n";
    std::cout << "\n";

    std::cout << "RESOLUTION\n";
    std::cout << "------------------------------\n";
    std::cout << "-r, --resolve                 Résout le labyrinthe\n";
    std::cout << "  -a, --algorithm <algo>      Sélectionne l'algorithme de "
                 "résolution\n";
    std::cout << "    Algorithmes disponibles : dfl, dfr, bf\n";
    std::cout
        << "                              dfl : depth_first_left (default)\n";
    std::cout << "                              dfr : depth_first_right\n";
    std::cout << "                              bf : breadth_first\n";
    std::cout << "\n";

    std::cout << "VERIFICATION\n";
    std::cout << "------------------------------\n";
    std::cout << "-v, --verify                  Vérifie si le labyrinthe est "
                 "valide\n";
    std::cout << "  -p, --perfect               Vérifie la perfection du "
                 "labyrinthe\n";
    std::cout << "  -a, --algorithm <algo>      Sélectionne l'algorithme de "
                 "vérification\n";
    std::cout << "    Algorithmes disponibles : dfl, dfr, bf\n";
    std::cout
        << "                              dfl : depth_first_left (default)\n";
    std::cout << "                              dfr : depth_first_right\n";
    std::cout << "                              bf : breadth_first\n";
    std::cout << "\n";

    std::cout << "JEU ET VISITE\n";
    std::cout << "------------------------------\n";
    std::cout << "-g, --game                    Lance le jeu ou la visite du "
                 "labyrinthe\n";
    std::cout << "  -t, --type <type>           Sélectionne le type de jeu ou "
                 "de visite\n";
    std::cout << "    Types disponibles :       f, fr, fl, w, wg\n";
    std::cout << "                              f : fog (default)\n";
    std::cout << "                              fr : fog_right\n";
    std::cout << "                              fl : fog_left\n";
    std::cout << "                              w : walk\n";
    std::cout << "                              wg : walk_ghost\n";
    std::cout << "\n";

    std::cout << "POINTS DE DEPART\n";
    std::cout << "------------------------------\n";
    std::cout
        << "-ps, --player-start <x> <y>   Définit la position de départ\n";
    std::cout
        << "-pe, --player-end <x> <y>     Définit la position d'arrivée\n";
    std::cout << "  Formats acceptés :          pourcentages, indices, "
                 "négatifs (relatifs)\n";
    std::cout << "                              `0.5, 0.5` : centre\n";
    std::cout
        << "                              `0, 0` : coin supérieur gauche\n";
    std::cout
        << "                              `-1, -1` : coin inférieur droit\n";

    std::cout << "\nPour plus d'informations, veuillez consulter la "
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
        checker_depth_first(maze, perfect, false, show);
    else if (algorithm == "depth_first_left" || algorithm == "dfl")
        checker_depth_first(maze, perfect, true, show);
    else if (algorithm == "breadth_first" || algorithm == "bf")
        checker_breadth_first(maze, perfect, show);
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
        } else if (strcmp(argv[i], "-lf") == 0 ||
                   strcmp(argv[i], "--low-freq") == 0) {
            show.setLowFreq(true);
        } else if (strcmp(argv[i], "-ps") == 0 ||
                   strcmp(argv[i], "--player-start") == 0) {
            if (i + 2 >= argc) return help(MAZE_COMMAND_ERROR);
            long double x_tmp = std::stold(argv[i + 1]);
            long double y_tmp = std::stold(argv[i + 2]);
            int x;
            if (x_tmp < 0)
                x = static_cast<int>(static_cast<long double>(maze.getWidth()) +
                                     x_tmp);
            else if (x_tmp > 0 && x_tmp < 1)
                x = static_cast<int>(static_cast<long double>(maze.getWidth()) *
                                     x_tmp);
            else
                x = static_cast<int>(x_tmp);
            int y;
            if (y_tmp < 0)
                y = static_cast<int>(
                    static_cast<long double>(maze.getHeight()) + y_tmp);
            else if (y_tmp > 0 && y_tmp < 1)
                y = static_cast<int>(
                    static_cast<long double>(maze.getHeight()) * y_tmp);
            else
                y = static_cast<int>(y_tmp);
            maze.setStart(x, y);
            i += 2;
        } else if (strcmp(argv[i], "-pe") == 0 ||
                   strcmp(argv[i], "--player-end") == 0) {
            if (i + 2 >= argc) return help(MAZE_COMMAND_ERROR);
            long double x_tmp = std::stold(argv[i + 1]);
            long double y_tmp = std::stold(argv[i + 2]);
            int x;
            if (x_tmp < 0)
                x = static_cast<int>(static_cast<long double>(maze.getWidth()) +
                                     x_tmp);
            else if (x_tmp > 0 && x_tmp < 1)
                x = static_cast<int>(static_cast<long double>(maze.getWidth()) *
                                     x_tmp);
            else
                x = static_cast<int>(x_tmp);
            int y;
            if (y_tmp < 0)
                y = static_cast<int>(
                    static_cast<long double>(maze.getHeight()) + y_tmp);
            else if (y_tmp > 0 && y_tmp < 1)
                y = static_cast<int>(
                    static_cast<long double>(maze.getHeight()) * y_tmp);
            else
                y = static_cast<int>(y_tmp);
            maze.setEnd(x, y);
            i += 2;
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
            std::string algorithm = "depth_first_left";
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
