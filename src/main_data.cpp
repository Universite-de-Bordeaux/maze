#include <sys/sysinfo.h>
#include <unistd.h>

#include <cstring>
#include <fstream>
#include <iostream>
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
#include "lib/game/splatoon_dead_end.hpp"
#include "lib/game/splatoon_dead_end_hand.hpp"
#include "lib/game/splatoon_hand.hpp"
#include "lib/game/tom_thumb.hpp"
#include "lib/game/tom_thumb_hand.hpp"
#include "lib/maze.hpp"
#include "lib/queue_file.hpp"
#include "lib/solver/breadth_first.hpp"
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
                 "dans un fichier LaTeX\n";
    std::cout << "-ng, --number-generations <n>        Génère n labyrinthes "
                 "(défaut : 1)\n";
    std::cout << "-nu, --nb-uses <n>            Utilise n fois le labyrinthe "
                 "(défaut : 1)\n";

    std::cout << "GENERATION\n";
    std::cout << "------------------------------\n";
    std::cout << "-g, --generate                Génère un labyrinthe parfait\n";
    std::cout << "  -a, --algorithm <algo>      Sélectionne l'algorithme de "
                 "génération\n";
    std::cout << "    Algorithmes disponibles : all, bt, wm, d, f\n";
    std::cout << "                              all : tous les algorithmes\n";
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
    std::cout << "    Types disponibles : all, de, der, del, f, fr, fl, s, sr, "
                 "sl, sde, "
                 "sder, sdel, tt, ttr, ttl\n";
    std::cout << "                              all : tous les types\n";
    std::cout << "                              de : dead_end\n";
    std::cout << "                              der : dead_end_right\n";
    std::cout << "                              del : dead_end_left\n";
    std::cout << "                              f : fog (default)\n";
    std::cout << "                              fr : fog_right\n";
    std::cout << "                              fl : fog_left\n";
    std::cout << "                              s : splatoon\n";
    std::cout << "                              sr : splatoon_right\n";
    std::cout << "                              sl : splatoon_left\n";
    std::cout << "                              sde : splatoon_dead_end\n";
    std::cout
        << "                              sder : splatoon_dead_end_right\n";
    std::cout
        << "                              sdel : splatoon_dead_end_left\n";
    std::cout << "                              tt : tom_thumb\n";
    std::cout << "                              ttr : tom_thumb_right\n";
    std::cout << "                              ttl : tom_thumb_left\n";
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
                  const int height, bool isPerfect, const double probability,
                  Show *show) {
    if (probability == 0.0) {
        isPerfect = false;
    }
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
        steps = game_splatoon_hand(maze, show, false);
    } else if (type == "splatoon_left" || type == "sl") {
        steps = game_splatoon_hand(maze, show, true);
    } else if (type == "splatoon_dead_end" || type == "sde") {
        steps = game_splatoon_dead_end(maze, show);
    } else if (type == "splatoon_dead_end_right" || type == "sder") {
        steps = game_splatoon_dead_end_hand(maze, show, false);
    } else if (type == "splatoon_dead_end_left" || type == "sdel") {
        steps = game_splatoon_dead_end_hand(maze, show, true);
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

struct size {
    int width;
    int height;
};

struct typesStruct {
    long sum = 0;
    int sumOptimum = 0;
    int sumDiffOptimum = 0;
    int nbSolveValid = 0;
    int nbOptimalSolution = 0;
    QueueFile stepsQueue;
};

std::string replaceUnderscoresWithSpaces(const std::string &str) {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find('_')) != std::string::npos) {
        result.replace(pos, 1, " ");
    }
    return result;
}

long getTotalSystemMemory() {
    struct sysinfo memInfo {};
    sysinfo(&memInfo);
    long long totalPhysMem = static_cast<long long>(memInfo.totalram) +
                             static_cast<long long>(memInfo.totalswap);
    totalPhysMem *= memInfo.mem_unit;
    return totalPhysMem;
}

long getCurrentRSS() {
    long rss = 0L;
    FILE *fp = nullptr;
    if ((fp = fopen("/proc/self/statm", "r")) == nullptr) {
        return static_cast<size_t>(0L); /* Can't open? */
    }
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), fp) == nullptr) {
        fclose(fp);
        return static_cast<size_t>(0L); /* Can't read? */
    }
    rss = strtol(buffer, nullptr, 10);
    return rss * sysconf(_SC_PAGESIZE);
}

void contentStats(const std::string &outputStats, std::ofstream &file,
                  const long double sum, const int sumOptimum,
                  const int nbSolveValid, const int nbOptimalSolution,
                  const QueueFile &stepsQueue, const std::string *type) {
    const long double average =
        static_cast<long double>(sum) / static_cast<long double>(nbSolveValid);

    // Calcul de l'écart avec l'optimum
    const long double optimumAverage = static_cast<long double>(sumOptimum) /
                                       static_cast<long double>(nbSolveValid);

    const long double absoluteDiffOptimum = average - optimumAverage;
    const long double relativeDiffOptimum = 100 * (optimumAverage / average);

    // Calcul de la variance
    long double variance = 0;
    for (int i = 0; i < stepsQueue.size(); i++) {
        const auto *steps = static_cast<int *>(stepsQueue.get(i));
        if (*steps >= 0) {
            variance += (static_cast<long double>(*steps) - average) *
                        (static_cast<long double>(*steps) - average);
        }
    }
    variance /= stepsQueue.size();
    const long double standardDeviation = sqrt(static_cast<double>(variance));

    if (!outputStats.empty()) {
        file << replaceUnderscoresWithSpaces(*type) << " & ";
        file << "$ " << static_cast<int>(round(static_cast<double>(average)))
             << " $ "
             << " & ";
        file << "$ "
             << static_cast<int>(round(static_cast<double>(standardDeviation)))
             << " $ "
             << " & ";
        file << "$ "
             << static_cast<int>(
                    round(static_cast<double>(absoluteDiffOptimum)))
             << " $ "
             << " & ";
        file << "$ "
             << round(1000 * static_cast<double>(relativeDiffOptimum)) / 1000
             << "\\%"
             << " $"
             << " & ";
        file << "$ " << nbSolveValid << " $"
             << " & ";
        file << "$ "
             << round(1000 * static_cast<double>(nbOptimalSolution) /
                      static_cast<double>(nbSolveValid)) /
                    1000
             << "\\%"
             << " $"
             << " \\\\ " << std::endl;
    }
}

void endStats(const std::string &outputStats, std::ofstream &file) {
    if (!outputStats.empty()) {
        file << "\\bottomrule" << std::endl;
        file << "\\end{tabular}" << std::endl;
        file << "\\end{table}" << std::endl;
        file << "\\FloatBarrier" << std::endl;
    }
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
    QueueFile algorithms("tmp/queue_algorithms.bin");
    QueueFile sizes("tmp/queue_sizes.bin");
    QueueFile types("tmp/queue_types.bin");
    bool perfect = true;
    QueueFile probabilities("tmp/queue_probabilities.bin");
    bool startInitiated = false;
    long double startX;
    long double startY;
    bool endInitiated = false;
    long double endX;
    long double endY;
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
            startX = std::stold(argv[i + 1]);
            startY = std::stold(argv[i + 2]);
            startInitiated = true;
            i += 2;
        } else if (strcmp(argv[i], "-pe") == 0 ||
                   strcmp(argv[i], "--player-end") == 0) {
            if (i + 2 >= argc) return help(MAZE_COMMAND_ERROR);
            endX = std::stold(argv[i + 1]);
            endY = std::stold(argv[i + 2]);
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
                   (strcmp(argv[i + 1], "-a") == 0 ||
                    strcmp(argv[i + 1], "--algorithm") == 0 ||
                    (strcmp(argv[i + 1], "-d") == 0 ||
                     strcmp(argv[i + 1], "--dimension") == 0) ||
                    (strcmp(argv[i + 1], "-i") == 0 ||
                     strcmp(argv[i + 1], "--imperfect") == 0) ||
                    (strcmp(argv[i + 1], "-p") == 0 ||
                     strcmp(argv[i + 1], "--probability") == 0))) {
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié le type d'algorithme
                    if (strcmp(argv[i + 1], "-a") == 0 ||
                        strcmp(argv[i + 1], "--algorithm") == 0) {
                        i++;
                        if (i + 1 < argc) {
                            if (strcmp(argv[i + 1], "all") == 0) {
                                algorithms.push(
                                    new std::string("back_tracking"));
                                algorithms.push(new std::string("diagonal"));
                                algorithms.push(new std::string("fractal"));
                                algorithms.push(new std::string("wall_maker"));
                            } else if (strcmp(argv[i + 1], "back_tracking") ==
                                           0 ||
                                       strcmp(argv[i + 1], "bt") == 0) {
                                algorithms.push(
                                    new std::string("back_tracking"));
                            } else if (strcmp(argv[i + 1], "wall_maker") == 0 ||
                                       strcmp(argv[i + 1], "wm") == 0) {
                                algorithms.push(new std::string("wall_maker"));
                            } else if (strcmp(argv[i + 1], "diagonal") == 0 ||
                                       strcmp(argv[i + 1], "d") == 0) {
                                algorithms.push(new std::string("diagonal"));
                            } else if (strcmp(argv[i + 1], "fractal") == 0 ||
                                       strcmp(argv[i + 1], "f") == 0) {
                                algorithms.push(new std::string("fractal"));
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
                            sizes.push(new size{std::stoi(argv[i + 1]),
                                                std::stoi(argv[i + 2])});
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
                            double probabilityTmp = std::stod(argv[i + 1]);
                            probabilities.push(new double(probabilityTmp));

                            if (probabilityTmp < 0.0 || probabilityTmp > 1.0) {
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
                    if (strcmp(argv[i + 1], "all") == 0) {
                        types.push(new std::string("dead_end"));
                        types.push(new std::string("dead_end_right"));
                        types.push(new std::string("dead_end_left"));
                        types.push(new std::string("fog"));
                        types.push(new std::string("fog_right"));
                        types.push(new std::string("fog_left"));
                        types.push(new std::string("splatoon"));
                        types.push(new std::string("splatoon_right"));
                        types.push(new std::string("splatoon_left"));
                        types.push(new std::string("splatoon_dead_end"));
                        types.push(new std::string("splatoon_dead_end_right"));
                        types.push(new std::string("splatoon_dead_end_left"));
                        types.push(new std::string("tom_thumb"));
                        types.push(new std::string("tom_thumb_right"));
                        types.push(new std::string("tom_thumb_left"));
                    } else if (strcmp(argv[i + 1], "fog") == 0 ||
                               strcmp(argv[i + 1], "f") == 0) {
                        types.push(new std::string("fog"));
                    } else if (strcmp(argv[i + 1], "fog_right") == 0 ||
                               strcmp(argv[i + 1], "fr") == 0) {
                        types.push(new std::string("fog_right"));
                    } else if (strcmp(argv[i + 1], "fog_left") == 0 ||
                               strcmp(argv[i + 1], "fl") == 0) {
                        types.push(new std::string("fog_left"));
                    } else if (strcmp(argv[i + 1], "splatoon") == 0 ||
                               strcmp(argv[i + 1], "s") == 0) {
                        types.push(new std::string("splatoon"));
                    } else if (strcmp(argv[i + 1], "splatoon_right") == 0 ||
                               strcmp(argv[i + 1], "sr") == 0) {
                        types.push(new std::string("splatoon_right"));
                    } else if (strcmp(argv[i + 1], "splatoon_left") == 0 ||
                               strcmp(argv[i + 1], "sl") == 0) {
                        types.push(new std::string("splatoon_left"));
                    } else if (strcmp(argv[i + 1], "splatoon_dead_end") == 0 ||
                               strcmp(argv[i + 1], "sde") == 0) {
                        types.push(new std::string("splatoon_dead_end"));
                    } else if (strcmp(argv[i + 1], "splatoon_dead_end_right") ==
                                   0 ||
                               strcmp(argv[i + 1], "sder") == 0) {
                        types.push(new std::string("splatoon_dead_end_right"));
                    } else if (strcmp(argv[i + 1], "splatoon_dead_end_left") ==
                                   0 ||
                               strcmp(argv[i + 1], "sdel") == 0) {
                        types.push(new std::string("splatoon_dead_end_left"));
                    } else if (strcmp(argv[i + 1], "tom_thumb") == 0 ||
                               strcmp(argv[i + 1], "tt") == 0) {
                        types.push(new std::string("tom_thumb"));
                    } else if (strcmp(argv[i + 1], "tom_thumb_right") == 0 ||
                               strcmp(argv[i + 1], "ttr") == 0) {
                        types.push(new std::string("tom_thumb_right"));
                    } else if (strcmp(argv[i + 1], "tom_thumb_left") == 0 ||
                               strcmp(argv[i + 1], "ttl") == 0) {
                        types.push(new std::string("tom_thumb_left"));
                    } else if (strcmp(argv[i + 1], "dead_end") == 0 ||
                               strcmp(argv[i + 1], "de") == 0) {
                        types.push(new std::string("dead_end"));
                    } else if (strcmp(argv[i + 1], "dead_end_right") == 0 ||
                               strcmp(argv[i + 1], "der") == 0) {
                        types.push(new std::string("dead_end_right"));
                    } else if (strcmp(argv[i + 1], "dead_end_left") == 0 ||
                               strcmp(argv[i + 1], "del") == 0) {
                        types.push(new std::string("dead_end_left"));
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
    if (sizes.empty()) sizes.push(new size{10, 10});
    if (algorithms.empty()) algorithms.push(new std::string("back_tracking"));
    if (types.empty()) types.push(new std::string("fog"));
    if (probabilities.empty()) probabilities.push(new double(0.01));

    std::ofstream fileLatex(outputLatex);
    if (!outputLatex.empty()) {
        std::cout << "Output file : " << outputLatex << std::endl;
        if (!fileLatex) {
            std::cout << "File not found : " << outputLatex << std::endl;
            return MAZE_FILE_ERROR;
        }
        fileLatex << "\\begin{table}[ht]" << std::endl;
        fileLatex << "\\centering" << std::endl;
        fileLatex << "\\caption{Statistiques ";
        if (types.size() == 1) {
            auto *type = static_cast<std::string *>(types.get(0));
            fileLatex << "pour le type de visite "
                      << replaceUnderscoresWithSpaces(*type);
        } else {
            fileLatex << "pour les types de visite ";
            for (int i = 0; i < types.size(); i++) {
                auto *type = static_cast<std::string *>(types.get(i));
                fileLatex << replaceUnderscoresWithSpaces(*type);
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
        if (sizes.size() == 1) {
            auto *size = static_cast<struct size *>(sizes.get(0));
            fileLatex << " de taille " << size->width << "x" << size->height;
        } else {
            fileLatex << " de tailles ";
            for (int i = 0; i < sizes.size(); i++) {
                auto *size = static_cast<struct size *>(sizes.get(i));
                fileLatex << size->width << "x" << size->height;
                if (i < sizes.size() - 1) fileLatex << ", ";
            }
        }
        if (!perfect) {
            if (probabilities.size() == 1) {
                auto *probability = static_cast<double *>(probabilities.get(0));
                fileLatex << " avec une probabilité de " << *probability;
            } else {
                fileLatex << " avec des probabilités de ";
                for (int i = 0; i < probabilities.size(); i++) {
                    auto *probability =
                        static_cast<double *>(probabilities.get(i));
                    fileLatex << *probability;
                    if (i < probabilities.size() - 1) fileLatex << ", ";
                }
            }
        }
        if (nbMazeToGenerate > 1)
            fileLatex << " générés";
        else
            fileLatex << " généré";
        fileLatex << " avec";
        if (algorithms.size() == 1) {
            auto *algorithm = static_cast<std::string *>(algorithms.front());
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
    }

    std::ofstream fileStats(outputStats);
    if (!outputStats.empty()) {
        if (!fileStats) {
            std::cout << "File not found : " << outputStats << std::endl;
            return MAZE_FILE_ERROR;
        }
    }

    auto maze = Maze();
    long iteration = sizes.size() * algorithms.size() * nbMazeToGenerate *
                     types.size() * nbUsesMaze * probabilities.size();
    long currentIteration = 0;
    QueueFile typesStats("tmp/queue_types_stats.bin");
    for (int j = 0; j < types.size(); j++) {
        typesStats.push(new typesStruct());
    }
    for (int f = 0; f < probabilities.size(); f++) {
        auto *probability = static_cast<double *>(probabilities.get(f));
        for (int g = 0; g < sizes.size(); g++) {
            auto *size = static_cast<struct size *>(sizes.get(g));
            int width = size->width;
            int height = size->height;
            QueueFile typesStructs("tmp/queue_types_structs_" +
                                   std::to_string(f) + "_" + std::to_string(g) +
                                   ".bin");
            for (int j = 0; j < types.size(); j++) {
                typesStructs.push(new typesStruct());
            }
            for (int h = 0; h < algorithms.size(); h++) {
                auto *algorithm = static_cast<std::string *>(algorithms.get(h));
                if (!outputStats.empty()) {
                    fileStats << "\\begin{table}[ht]" << std::endl;
                    fileStats << "\\centering" << std::endl;
                    fileStats << "\\caption{Algorithme ";
                    fileStats << replaceUnderscoresWithSpaces(*algorithm);
                    fileStats << " $" << width << " \\times " << height << "$";
                    if (perfect) {
                        fileStats << " parfait";
                    } else {
                        fileStats << " imparfait avec une probabilité de "
                                  << *probability;
                    }
                    fileStats << " pour " << nbMazeToGenerate
                              << " labyrinthes générés et "
                                 "visités "
                              << nbUsesMaze << " fois";
                    fileStats << "}" << std::endl;

                    fileStats << "\\begin{tabular}{lcccccc}"
                              << std::endl;  // mise en forme du tableau
                    fileStats << "\\toprule Type & Moyenne & Ecart-type & EAO "
                                 "& ERO & "
                                 "Valide & Optimale \\\\"
                              << std::endl;  // première ligne indiquant le
                    // contenu des
                    // colonnes

                    fileStats << "\\midrule" << std::endl;  // corps du tableau
                }
                for (int j = 0; j < types.size(); j++) {
                    auto *type = static_cast<std::string *>(types.get(j));
                    QueueFile stepsQueue(
                        "tmp/queue_steps_" + std::to_string(f) + "_" +
                        std::to_string(g) + "_" + std::to_string(h) + "_" +
                        std::to_string(j) + ".bin");
                    int sumOptimum = 0;
                    int sumDiffOptimum = 0;
                    int nbSolveValid = 0;
                    int nbOptimalSolution = 0;
                    auto *typesStruct =
                        static_cast<struct typesStruct *>(typesStructs.get(j));
                    auto *typesStat =
                        static_cast<struct typesStruct *>(typesStats.get(j));

                    for (int i = 0; i < nbMazeToGenerate; i++) {
                        generateMaze(&maze, *algorithm, width, height, perfect,
                                     *probability, nullptr);
                        if (startInitiated) {
                            int x_tmp;
                            int y_tmp;
                            if (startX < 0)
                                x_tmp = static_cast<int>(
                                    static_cast<long double>(width) + startX);
                            else if (startX > 0 && startX < 1)
                                x_tmp = static_cast<int>(
                                    static_cast<long double>(width) * startX);
                            else
                                x_tmp = static_cast<int>(startX);
                            if (startY < 0)
                                y_tmp = static_cast<int>(
                                    static_cast<long double>(height) + startY);
                            else if (startY > 0 && startY < 1)
                                y_tmp = static_cast<int>(
                                    static_cast<long double>(height) * startY);
                            else
                                y_tmp = static_cast<int>(startY);
                            maze.setStart(x_tmp, y_tmp);
                        }
                        if (endInitiated) {
                            int x_tmp;
                            int y_tmp;
                            if (endX < 0)
                                x_tmp = static_cast<int>(
                                    static_cast<long double>(width) + endX);
                            else if (endX > 0 && endX < 1)
                                x_tmp = static_cast<int>(
                                    static_cast<long double>(width) * endX);
                            else
                                x_tmp = static_cast<int>(endX);
                            if (endY < 0)
                                y_tmp = static_cast<int>(
                                    static_cast<long double>(height) + endY);
                            else if (endY > 0 && endY < 1)
                                y_tmp = static_cast<int>(
                                    static_cast<long double>(height) * endY);
                            else
                                y_tmp = static_cast<int>(endY);
                            maze.setEnd(x_tmp, y_tmp);
                        }
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

                            if (steps != -1) {
                                sumOptimum += nbCellsSolution;
                                sumDiffOptimum += steps - nbCellsSolution;
                                nbSolveValid++;
                                if (steps == nbCellsSolution) {
                                    nbOptimalSolution++;
                                }
                            }

                            stepsQueue.push(new int(steps));
                            if (!outputLatex.empty()) {
                                if (*algorithm == "back_tracking") {
                                    fileLatex << "back tracking";
                                } else if (*algorithm == "wall_maker") {
                                    fileLatex << "wall maker";
                                } else {
                                    fileLatex << *algorithm;
                                }
                                fileLatex << " & " << width << "x" << height
                                          << " & ";
                                if (perfect)
                                    fileLatex << "Oui";
                                else
                                    fileLatex << "Non" << *probability;
                                fileLatex << " & ";
                                fileLatex
                                    << replaceUnderscoresWithSpaces(*type);
                                fileLatex << " & " << steps << " & "
                                          << nbCellsSolution << " \\\\"
                                          << std::endl;
                            }
                            std::cout
                                << "\r" << currentIteration * 100 / iteration
                                << "% - " << currentIteration << "/"
                                << iteration << " | RAM used: "
                                << round(static_cast<double>(getCurrentRSS()) /
                                         1024.0 / 1024.0 / 1024.0 * 100.0) /
                                       100.0
                                << " GB"
                                << " / "
                                << round(static_cast<double>(
                                             getTotalSystemMemory()) /
                                         1024 / 1024 / 1024 * 100.0) /
                                       100.0
                                << " GB"
                                << " | probability " << *probability << " - "
                                << f + 1 << "/" << probabilities.size()
                                << " | size " << width << "x" << height << " - "
                                << g + 1 << "/" << sizes.size()
                                << " | algorithm " << *algorithm << " - "
                                << h + 1 << "/" << algorithms.size()
                                << " | type " << *type << " - " << j + 1 << "/"
                                << types.size() << " | maze " << i + 1 << "/"
                                << nbMazeToGenerate << " | uses " << k + 1
                                << "/" << nbUsesMaze << std::flush;
                        }
                    }
                    // calcul des statistiques
                    // Calcul de la moyenne
                    long sum = 0;
                    for (int i = 0; i < stepsQueue.size(); i++) {
                        auto *steps = static_cast<int *>(stepsQueue.get(i));
                        if (*steps >= 0) {
                            sum += *steps;
                        }
                    }

                    contentStats(outputStats, fileStats, sum, sumOptimum,
                                 nbSolveValid, nbOptimalSolution, stepsQueue,
                                 type);

                    typesStruct->sum += sum;
                    typesStruct->sumOptimum += sumOptimum;
                    typesStruct->sumDiffOptimum += sumDiffOptimum;
                    typesStruct->nbSolveValid += nbSolveValid;
                    typesStruct->nbOptimalSolution += nbOptimalSolution;
                    typesStat->sum += sum;
                    typesStat->sumOptimum += sumOptimum;
                    typesStat->sumDiffOptimum += sumDiffOptimum;
                    typesStat->nbSolveValid += nbSolveValid;
                    typesStat->nbOptimalSolution += nbOptimalSolution;
                    for (int i = 0; i < stepsQueue.size(); i++) {
                        auto *steps = static_cast<int *>(stepsQueue.get(i));
                        if (*steps >= 0) {
                            typesStruct->stepsQueue.push(new int(*steps));
                            typesStat->stepsQueue.push(new int(*steps));
                        }
                    }
                }
                endStats(outputStats, fileStats);
            }
            if (!outputStats.empty()) {
                fileStats << "\\begin{table}[ht]" << std::endl;
                fileStats << "\\centering" << std::endl;
                fileStats
                    << "\\caption{Statistiques pour les labyrinthes de taille "
                       "$"
                    << width << " \\times " << height << "$";
                if (perfect) {
                    fileStats << " parfait";
                } else {
                    fileStats << " imparfait avec une probabilité de "
                              << *probability;
                }
                fileStats << " pour " << nbMazeToGenerate
                          << " labyrinthes générés avec " << algorithms.size()
                          << " algorithmes et visités " << nbUsesMaze
                          << " fois";
                fileStats << "}" << std::endl;

                fileStats << "\\begin{tabular}{lcccccc}"
                             "\n";  // mise en forme du tableau
                fileStats << "\\toprule Type & Moyenne & Ecart-type & EAO "
                             "& ERO & "
                             "Valide & Optimale \\\\"
                             "\n";  // première ligne indiquant le contenu des
                // colonnes

                fileStats << "\\midrule" << std::endl;  // corps du tableau
            }
            for (int j = 0; j < types.size(); j++) {
                auto *typesStruct =
                    static_cast<struct typesStruct *>(typesStructs.get(j));
                auto *type = static_cast<std::string *>(types.get(j));
                int nbSolveValid = typesStruct->nbSolveValid;
                if (nbSolveValid > 0) {
                    long sum = typesStruct->sum;
                    int sumOptimum = typesStruct->sumOptimum;
                    QueueFile stepsQueue = typesStruct->stepsQueue;
                    int nbOptimalSolution = typesStruct->nbOptimalSolution;

                    contentStats(outputStats, fileStats, sum, sumOptimum,
                                 nbSolveValid, nbOptimalSolution, stepsQueue,
                                 type);
                }
            }
            endStats(outputStats, fileStats);
        }
    }
    if (!outputStats.empty()) {
        fileStats << "\\begin{table}[ht]" << std::endl;
        fileStats << "\\centering" << std::endl;
        fileStats << "\\caption{Statistiques pour les labyrinthes de taille [";
        for (int i = 0; i < sizes.size(); i++) {
            auto *size = static_cast<struct size *>(sizes.get(i));
            fileStats << size->width << "x" << size->height;
            if (i < sizes.size() - 1) fileStats << ", ";
        }
        fileStats << "]";
        if (perfect) {
            fileStats << " parfait";
        } else {
            if (probabilities.size() == 1) {
                auto *probability = static_cast<double *>(probabilities.get(0));
                fileStats << " imparfait avec une probabilité de "
                          << *probability;
            } else {
                fileStats << " imparfait avec des probabilités de ";
                for (int i = 0; i < probabilities.size(); i++) {
                    auto *probability =
                        static_cast<double *>(probabilities.get(i));
                    fileStats << *probability;
                    if (i < probabilities.size() - 1) fileStats << ", ";
                }
            }
        }
        fileStats << " pour " << nbMazeToGenerate
                  << " labyrinthes générés avec " << algorithms.size()
                  << " algorithmes et visités " << nbUsesMaze << " fois";
        fileStats << "}" << std::endl;
        fileStats << "\\begin{tabular}{lcccccc}"
                     "\n";  // mise en forme du tableau
        fileStats << "\\toprule Type & Moyenne & Ecart-type & EAO "
                     "& ERO & "
                     "Valide & Optimale \\\\"
                     "\n";  // première ligne indiquant le contenu des
        // colonnes
        fileStats << "\\midrule" << std::endl;  // corps du tableau
    }
    for (int j = 0; j < types.size(); j++) {
        auto *typesStat = static_cast<struct typesStruct *>(typesStats.get(j));
        auto *type = static_cast<std::string *>(types.get(j));
        int nbSolveValid = typesStat->nbSolveValid;
        if (nbSolveValid > 0) {
            long sum = typesStat->sum;
            int sumOptimum = typesStat->sumOptimum;
            QueueFile stepsQueue = typesStat->stepsQueue;
            int nbOptimalSolution = typesStat->nbOptimalSolution;

            contentStats(outputStats, fileStats, sum, sumOptimum, nbSolveValid,
                         nbOptimalSolution, stepsQueue, type);
        }
    }
    endStats(outputStats, fileStats);

    std::cout << std::endl;
    // écriture de la fin des fichiers
    if (!outputLatex.empty()) {
        fileLatex << "\\end{tabular}" << std::endl;
        fileLatex << "\\end{table}" << std::endl;
        fileLatex << "\\FloatBarrier" << std::endl;
        std::cout << "File " << outputLatex << " saved" << std::endl;
    }
    fileLatex.close();

    fileStats.close();
    if (!outputStats.empty()) {
        std::cout << "File " << outputStats << " saved" << std::endl;
    }

    return EXIT_SUCCESS;
}
