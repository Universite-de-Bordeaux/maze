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
 * Affiche la documentation d'aide pour l'application de génération
 */
void help() {
    std::cout << "=================================================================\n";
    std::cout << "=                     MAZE GENERATOR APPLICATION               =\n";
    std::cout << "=================================================================\n";
    std::cout << "\n";
    
    std::cout << "Usage : ./maze_generator.out [-option] [arguments]\n";
    std::cout << "\n";
    
    std::cout << "OPTIONS\n";
    std::cout << "------------------------------\n";
    std::cout << "-h, --help                    Affiche cette documentation\n";
    std::cout << "-i, --input <fichier>         Charge un labyrinthe depuis un fichier\n";
    std::cout << "-o, --output <fichier>        Sauvegarde le labyrinthe dans un fichier\n";
    std::cout << "-c, --clear                   Efface complètement le labyrinthe\n";
    std::cout << "--clear-maze                  Efface uniquement les cellules du labyrinthe\n";
    std::cout << "\n";
    
    std::cout << "AFFICHAGE\n";
    std::cout << "------------------------------\n";
    std::cout << "-s, --show                    Affiche le labyrinthe\n";
    std::cout << "-f --framerate <fps>          Définit le framerate d'affichage\n";
    std::cout << "-ds --delay-show <ms>         Définit le délai entre chaque mise à jour\n";
    std::cout << "-lf --low-freq                Affiche le labyrinthe à basse fréquence\n";
    std::cout << "\n";
    
    std::cout << "      RACCOURCIS CLAVIER\n";
    std::cout << "      ------------------------\n";
    std::cout << "      Echap                   Ferme l'affichage\n";
    std::cout << "      Espace                  Met en pause le programme\n";
    std::cout << "      D                       Rafraîchit toutes les cellules\n";
    std::cout << "      R                       Réinitialise les paramètres d'affichage\n";
    std::cout << "      L                       Inverse la fréquence d'affichage ( haute/basse)\n";
    std::cout << "      +                       Augmente le framerate\n";
    std::cout << "      -                       Diminue le framerate\n";
    std::cout << "      *                       Augmente le délai d'affichage\n";
    std::cout << "      /                       Diminue le délai d'affichage\n";
    std::cout << "\n";
    
    std::cout << "      SOURIS\n";
    std::cout << "      ------------------------\n";
    std::cout << "      Clic gauche +           Déplace la vue du labyrinthe déplacement souris (seulement si le labyrinthe est inférieur à 100 x 100)\n";
    std::cout << "      Molette                 Zoom avant/arrière sur l'affichage (seulement si le labyrinthe est inférieur à 100 x 100)\n";
    std::cout << "\n";
    
    std::cout << "GENERATION\n";
    std::cout << "------------------------------\n";
    std::cout << "-g, --generate                Génère un labyrinthe parfait\n";
    std::cout << "  --algorithm <algo>          Sélectionne l'algorithme de génération\n";
    std::cout << "    Algorithmes disponibles : bt, wm, d, f\n";
    std::cout << "                              bt : back_tracking (défaut)\n";
    std::cout << "                              wm : wall_maker\n";
    std::cout << "                              d : diagonal\n";
    std::cout << "                              f : fractal\n";
    std::cout << "  --dimension <w> <h>         Définit les dimensions du labyrinthe\n";
    std::cout << "  --imperfect                 Génère un labyrinthe imparfait\n";
    std::cout << "    --probability <p>         Définit la probabilité de suppression de murs [0.0-1.0]\n";
    std::cout << "\n";
    
    std::cout << "Pour plus d'informations, veuillez consulter la documentation complète.\n";
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
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout
        << "Generated in "
        << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
        << "."
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                   .count() %
               1000
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
                            } else if (strcmp(argv[i + 1], "wall_maker") == 0 ||
                                       strcmp(argv[i + 1], "wm") == 0) {
                                algorithm = "wall_maker";
                            } else if (strcmp(argv[i + 1], "diagonal") == 0 ||
                                       strcmp(argv[i + 1], "d") == 0) {
                                algorithm = "diagonal";
                            } else if (strcmp(argv[i + 1], "fractal") == 0 ||
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
                generateMaze(&maze, algorithm, width, height, perfect,
                             probability, &show);
                while (show.isOpen()) {
                    refreshShow(&show);
                }
                show.destroy();
            } else {
                generateMaze(&maze, algorithm, width, height, perfect,
                             probability, nullptr);
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
