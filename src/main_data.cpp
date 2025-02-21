#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "lib/algo/back_tracking.hpp"
#include "lib/algo/diagonal.hpp"
#include "lib/algo/fractal.hpp"
#include "lib/algo/wall_maker.hpp"
#include "lib/game/dead_end.hpp"
#include "lib/game/dead_end_hand.hpp"
#include "lib/game/fog.hpp"
#include "lib/game/fog_hand.hpp"
#include "lib/game/splatoon.hpp"
#include "lib/game/splatoon_hand.hpp"
#include "lib/game/tom_thumb.hpp"
#include "lib/game/tom_thumb_hand.hpp"
#include "lib/maze.hpp"
#include "lib/solver/breadth_first.hpp"
#include "lib/stack.hpp"
#include "lib/var.hpp"

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
    std::cout
        << "    Types disponibles :       f, fr, fl, s, sr, sl, tt, ttr, ttl\n";
    std::cout << "                              f : fog (default)\n";
    std::cout << "                              fr : fog_right\n";
    std::cout << "                              fl : fog_left\n";
    std::cout << "                              s : splatoon\n";
    std::cout << "                              sr : splatoon_right\n";
    std::cout << "                              sl : splatoon_left\n";
    std::cout << "                              tt : tom_thumb\n";
    std::cout << "                              ttr : tom_thumb_right\n";
    std::cout << "                              ttl : tom_thumb_left\n";
    std::cout << "                              de : dead_end\n";
    std::cout << "                              der : dead_end_right\n";
    std::cout << "                              del : dead_end_left\n";
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
    if (algorithm == "back_tracking" || algorithm == "bt")
        algo_back_tracking(maze, width, height, isPerfect, probability, show);
    else if (algorithm == "wall_maker" || algorithm == "wm")
        algo_wall_maker(maze, width, height, isPerfect, probability, show);
    else if (algorithm == "diagonal" || algorithm == "d")
        algo_diagonal(maze, width, height, isPerfect, probability, show);
    else if (algorithm == "fractal" || algorithm == "f")
        algo_fractal(maze, static_cast<int>(log2(width)), isPerfect,
                     probability, show);
    else
        exit(MAZE_COMMAND_ERROR);
}

/**
 * Commande pour jouer à un jeu de labyrinthe
 * @param maze Labyrinthe
 * @param type Type de jeu
 * @param show Affichage
 */
int gameMaze(Maze *maze, const std::string &type, Show *show) {
    int steps = 0;
    if (type == "fog" || type == "f") {
        steps = game_fog(maze, show);
    } else if (type == "fog_right" || type == "fr") {
        steps = game_fog_hand(maze, show, false);
    } else if (type == "fog_left" || type == "fl") {
        steps = game_fog_hand(maze, show, true);
    } else if (type == "splatoon" || type == "s") {
        steps = game_splatoon(maze, show);
    } else if (type == "splatoon_right" || type == "sr") {
        // steps = game_splatoon_hand(maze, show, false);
    } else if (type == "splatoon_left" || type == "sl") {
        // steps = game_splatoon_hand(maze, show, true);
    } else if (type == "tom_thumb" || type == "tt") {
        steps = game_tom_thumb(maze, show);
    } else if (type == "tom_thumb_right" || type == "ttr") {
        steps = game_tom_thumb_hand(maze, show, false);
    } else if (type == "tom_thumb_left" || type == "ttl") {
        steps = game_tom_thumb_hand(maze, show, true);
    } else if (type == "dead_end" || type == "de") {
        steps = game_dead_end(maze, show);
    } else if (type == "dead_end_right" || type == "der") {
        steps = game_dead_end_hand(maze, show, false);
    } else if (type == "dead_end_left" || type == "del") {
        steps = game_dead_end_hand(maze, show, true);
    } else {
        exit(MAZE_COMMAND_ERROR);
    }
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
            const int nbMaze = std::stoi(argv[i + 1]);
            if (nbMaze > 0)
                nbMazeToGenerate = nbMaze;
            else
                return help(MAZE_COMMAND_ERROR);
            i++;
        } else if (strcmp(argv[i], "-nu") == 0 ||
                   strcmp(argv[i], "--number-uses") == 0) {
            if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
            const int nbUses = std::stoi(argv[i + 1]);
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
                                auto *algo = new std::string("back_tracking");
                                algorithms.push(algo);
                            } else if (strcmp(argv[i + 1], "wall_maker") == 0 ||
                                       strcmp(argv[i + 1], "wm") == 0) {
                                auto *algo = new std::string("wall_maker");
                                algorithms.push(algo);
                            } else if (strcmp(argv[i + 1], "diagonal") == 0 ||
                                       strcmp(argv[i + 1], "d") == 0) {
                                auto *algo = new std::string("diagonal");
                                algorithms.push(algo);
                            } else if (strcmp(argv[i + 1], "fractal") == 0 ||
                                       strcmp(argv[i + 1], "f") == 0) {
                                auto *algo = new std::string("fractal");
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
                        auto *type = new std::string("fog");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "fog_right") == 0 ||
                               strcmp(argv[i + 1], "fr") == 0) {
                        auto *type = new std::string("fog_right");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "fog_left") == 0 ||
                               strcmp(argv[i + 1], "fl") == 0) {
                        auto *type = new std::string("fog_left");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "splatoon") == 0 ||
                               strcmp(argv[i + 1], "s") == 0) {
                        auto *type = new std::string("splatoon");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "splatoon_right") == 0 ||
                               strcmp(argv[i + 1], "sr") == 0) {
                        auto *type = new std::string("splatoon_right");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "splatoon_left") == 0 ||
                               strcmp(argv[i + 1], "sl") == 0) {
                        auto *type = new std::string("splatoon_left");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "tom_thumb") == 0 ||
                               strcmp(argv[i + 1], "tt") == 0) {
                        auto *type = new std::string("tom_thumb");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "tom_thumb_right") == 0 ||
                               strcmp(argv[i + 1], "ttr") == 0) {
                        auto *type = new std::string("tom_thumb_right");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "tom_thumb_left") == 0 ||
                               strcmp(argv[i + 1], "ttl") == 0) {
                        auto *type = new std::string("tom_thumb_left");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "dead_end") == 0 ||
                               strcmp(argv[i + 1], "de") == 0) {
                        auto *type = new std::string("dead_end");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "dead_end_right") == 0 ||
                               strcmp(argv[i + 1], "der") == 0) {
                        auto *type = new std::string("dead_end_right");
                        types.push(type);
                    } else if (strcmp(argv[i + 1], "dead_end_left") == 0 ||
                               strcmp(argv[i + 1], "del") == 0) {
                        auto *type = new std::string("dead_end_left");
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

    std::ofstream fileLatex(outputLatex);
    if (!fileLatex) {
        std::cout << "File not found : " << outputLatex << std::endl;
        return MAZE_FILE_ERROR;
    }
    fileLatex << "\\begin{table}[ht]" << std::endl;
    fileLatex << "\\centering" << std::endl;
    fileLatex << "\\caption{Statistiques ";
    if (types.size() == 1) {
        auto *type = static_cast<std::string *>(types.get(0));
        fileLatex << "pour le type de visite " << *type;
    } else {
        fileLatex << "pour les types de visite ";
        for (int i = 0; i < types.size(); i++) {
            auto *type = static_cast<std::string *>(types.get(i));
            if (*type == "fog_left") {
                fileLatex << "fog left";
            } else if (*type == "fog_right") {
                fileLatex << "fog right";
            } else if (*type == "splatoon_right") {
                fileLatex << "splatoon right";
            } else if (*type == "splatoon_left") {
                fileLatex << "splatoon left";
            } else if (*type == "tom_thumb") {
                fileLatex << "tom thumb";
            } else if (*type == "tom_thumb_right") {
                fileLatex << "tom thumb right";
            } else if (*type == "tom_thumb_left") {
                fileLatex << "tom thumb left";
            } else if (*type == "dead_end_right") {
                fileLatex << "dead end right";
            } else if (*type == "dead_end_left") {
                fileLatex << "dead end left";
            } else if (*type == "dead_end") {
                fileLatex << "dead end";
            } else {
                fileLatex << *type;
            }
            if (i < types.size() - 1) fileLatex << ", ";
        }
    }
    fileLatex << " sur " << nbMazeToGenerate;
    if (nbMazeToGenerate > 1) {
        fileLatex << " labyrinthes";
        if (perfect)
            fileLatex << " parfaits";
        else
            fileLatex << " imparfaits";
    } else {
        fileLatex << " labyrinthe";
        if (perfect)
            fileLatex << " parfait";
        else
            fileLatex << " imparfait";
    }
    fileLatex << " de taille " << width << "x" << height;
    if (!perfect) fileLatex << " avec une probabilité de " << probability;
    if (nbMazeToGenerate > 1)
        fileLatex << " générés";
    else
        fileLatex << " généré";
    fileLatex << " avec";
    if (algorithms.size() == 1) {
        auto *algorithm = static_cast<std::string *>(algorithms.top());
        fileLatex << " l'algorithme " << *algorithm;
    } else {
        fileLatex << " les algorithmes ";
        for (int i = 0; i < algorithms.size(); i++) {
            auto *algorithm = static_cast<std::string *>(algorithms.get(i));
            if (*algorithm == "back_tracking") {
                fileLatex << "back tracking";
            } else if (*algorithm == "wall_maker") {
                fileLatex << "wall maker";
            } else {
                fileLatex << *algorithm;
            }
            if (i < algorithms.size() - 1) fileLatex << ", ";
        }
    }
    fileLatex << "}" << std::endl;
    fileLatex << "\\begin{tabular}{";
    if (perfect)
        fileLatex << "lccccc}";
    else
        fileLatex << "lcccccc}";
    fileLatex << "\\toprule" << std::endl;
    fileLatex << "Générateur & Taille & Parfait ";
    if (!perfect) fileLatex << "& Probabilité ";
    fileLatex << "& Visite & "
                 "Nombre de pas & Optimale \\\\"
              << std::endl;
    fileLatex << "\\midrule" << std::endl;

    std::ofstream fileStats(outputStats);
    if (!fileStats) {
        std::cout << "File not found : " << outputStats << std::endl;
        return MAZE_FILE_ERROR;
    }

    fileStats << "\\begin{table}[ht]" << std::endl;
    fileStats << "\\centering" << std::endl;
    fileStats << "\\caption{Algo ";

    auto *algorithm = static_cast<std::string *>(algorithms.top());

    if (*algorithm == "back_tracking") {
        fileStats << "back tracking";
    } else if (*algorithm == "wall_maker") {
        fileStats << "wall maker";
    } else {
        fileStats << *algorithm;
    }
    fileStats << " $" << width << " \\times " << height << "$";
    if (perfect) {
        fileStats << " parfait"
                  << "}" << std::endl;
    } else {
        fileStats << " imparfait"
                  << "}" << std::endl;
    }

    fileStats << "\\begin{tabular}{lccc}"
              << std::endl;  // mise en forme du tableau
    fileStats << "\\toprule type & moyenne & écart-type"
              << std::endl;  // première ligne indiquant le contenu des colonnes

    Stack stepsStack;
    auto maze = Maze();
    long iteration =
        algorithms.size() * nbMazeToGenerate * types.size() * nbUsesMaze;
    long currentIteration = 0;

    fileStats << "\\midrule" << std::endl;  // corps du tableau

    for (int j = 0; j < types.size(); j++) {
        auto *type = static_cast<std::string *>(types.get(j));
        while (!algorithms.empty()) {
            auto *algorithm = static_cast<std::string *>(algorithms.top());
            algorithms.pop();
            for (int i = 0; i < nbMazeToGenerate; i++) {
                generateMaze(&maze, *algorithm, width, height, perfect,
                             probability, nullptr);
                if (startInitiated) maze.setStart(startX, startY);
                if (endInitiated) maze.setEnd(endX, endY);
                for (int k = 0; k < nbUsesMaze; k++) {
                    currentIteration++;
                    if (!startInitiated) maze.resetStart();
                    if (!endInitiated) maze.resetEnd();
                    solver_breadth_first(&maze, nullptr);
                    int nbCellsSolution = 0;
                    for (int x = 0; x < maze.getWidth(); x++) {
                        for (int y = 0; y < maze.getHeight(); y++) {
                            if (maze.getCell(x, y)->getStatus() ==
                                MAZE_STATUS_WAY_OUT)
                                nbCellsSolution++;
                        }
                    }
                    maze.clearMaze();
                    int steps = gameMaze(&maze, *type, nullptr);
                    stepsStack.push(new int(steps));
                    if (*algorithm == "back_tracking") {
                        fileLatex << "back tracking";
                    } else if (*algorithm == "wall_maker") {
                        fileLatex << "wall maker";
                    } else {
                        fileLatex << *algorithm;
                    }
                    fileLatex << " & " << width << "x" << height << " & ";
                    if (perfect)
                        fileLatex << "Oui";
                    else
                        fileLatex << "Non" << probability;
                    fileLatex << " & ";
                    if (*type == "fog_left") {
                        fileLatex << "fog left";
                    } else if (*type == "fog_right") {
                        fileLatex << "fog right";
                    } else if (*type == "splatoon_right") {
                        fileLatex << "splatoon right";
                    } else if (*type == "splatoon_left") {
                        fileLatex << "splatoon left";
                    } else if (*type == "tom_thumb") {
                        fileLatex << "tom thumb";
                    } else if (*type == "tom_thumb_right") {
                        fileLatex << "tom thumb right";
                    } else if (*type == "tom_thumb_left") {
                        fileLatex << "tom thumb left";
                    } else if (*type == "dead_end_right") {
                        fileLatex << "dead end right";
                    } else if (*type == "dead_end_left") {
                        fileLatex << "dead end left";
                    } else if (*type == "dead_end") {
                        fileLatex << "dead end";
                    } else {
                        fileLatex << *type;
                    }
                    fileLatex << " & " << steps << " & " << nbCellsSolution
                              << " \\\\" << std::endl;
                    std::cout
                        << "\rProgress : " << currentIteration * 100 / iteration
                        << "% - " << currentIteration << "/" << iteration << " "
                        << std::flush;
                }
            }
        }
        // Calcul de la moyenne
        long sum = 0;
        for (int i = 0; i < stepsStack.size(); i++) {
            auto *steps = static_cast<int *>(stepsStack.get(i));
            sum += *steps;
        }
        long double average = static_cast<long double>(sum) /
                              static_cast<long double>(stepsStack.size());
        // Calcul de la variance
        long double variance = 0;
        for (int i = 0; i < stepsStack.size(); i++) {
            auto *steps = static_cast<int *>(stepsStack.get(i));
            variance += (static_cast<long double>(*steps) - average) *
                        (static_cast<long double>(*steps) - average);
        }
        variance /= stepsStack.size();
        // Calcul de l'écart-type
        long double standardDeviation = sqrt(static_cast<double>(variance));
        // Calcul de l'écart-type de la moyenne
        long double standardDeviationAverage =
            standardDeviation / sqrt(stepsStack.size());
        fileStats << *type << " & ";
        std::cout << "Type : " << *type << std::endl;
        fileStats << average << " & ";
        std::cout << "Moyenne : " << average << std::endl;
        // fileStats << variance << std::endl;
        // std::cout << "Variance : " << variance << std::endl;
        fileStats << standardDeviation << "\\\\" << std::endl;
        std::cout << "Ecart-type : " << standardDeviation << std::endl;
        // fileStats << "Ecart-type de la moyenne : " <<
        // standardDeviationAverage
        // << std::endl;
        // std::cout << "Ecart-type de la moyenne : " <<
        // standardDeviationAverage
        //           << std::endl;
        // calcul des statistiques
    }

    // écriture de la fin des fichiers
    std::cout << std::endl;
    fileStats << "\\bottomrule" << std::endl;
    fileLatex << "\\end{tabular}" << std::endl;
    fileLatex << "\\end{table}" << std::endl;
    fileLatex << "\\FloatBarrier" << std::endl;
    fileLatex.close();
    std::cout << "File " << outputLatex << " saved" << std::endl;

    fileLatex << "\\bottomrule" << std::endl;
    fileStats << "\\end{tabular}" << std::endl;
    fileStats << "\\end{table}" << std::endl;
    fileStats << "\\FloatBarrier" << std::endl;
    fileStats.close();
    std::cout << "File " << outputStats << " saved" << std::endl;

    return EXIT_SUCCESS;
}
