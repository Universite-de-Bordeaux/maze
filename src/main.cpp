#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lib/reader.hpp"
#include "lib/show.hpp"
#include "lib/maze.hpp"
#include "lib/var.hpp"
#include "lib/algo_cours.hpp"
#include "lib/algo_1.hpp"
#include "lib/writer.hpp"
#include "lib/checker.hpp"

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
    std::cout << "  -t ou --type <type> : Spécifie le type d'algorithme à utiliser pour la génération (cours, perso, 1, par défaut : cours)" << std::endl;
    std::cout << "  -d ou --dimension <x> <y> : Spécifie les dimensions du labyrinthe à générer (par défaut : 10 10)" << std::endl;
    std::cout << "  -u ou --unperfect : Génère un labyrinthe imparfait (le labyrinthe généré est par défaut parfait)" << std::endl;
    std::cout << "-r ou --resolve : Résout un labyrinthe (nécessite un labyrinthe en mémoire)" << std::endl;
    std::cout << "  -a ou --algorithm <algorithme> : Spécifie l'algorithme à utiliser pour la résolution (aaa, bbb, par défaut : aaa)" << std::endl;
    std::cout << "-v ou --verify : Vérifie si un labyrinthe est valide (nécessite un labyrinthe en mémoire)" << std::endl;
    std::cout << "  -p ou --perfect : Vérifie si un labyrinthe est parfait (on ne vérifie pas la perfection par défaut)" << std::endl;
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
 * Commande -g
 * @param type Type d'algorithme
 * @param x Dimension x
 * @param y Dimension y
 * @param perfect Parfait
*/
void generateMaze(Maze *maze, std::string type, int x, int y, bool perfect) {
    // TODO : Générer un labyrinthe
    if (type == "cours") algo_cours(maze, x, y, perfect);
    else if ((type == "perso")) std::cout << "PERSOOO" << std::endl;
    else if ((type == "1")) algo_1(maze, x, y, perfect);
    else exit(MAZE_COMMAND_ERROR);
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
        Show show = Show(&maze);
        // Parcours les arguments
        for (int i = 1; i < argc; i++) {
            // Vérifie si l'argument est une commande
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) return help(MAZE_OK);
            // Si l'utilisateur veut afficher le labyrinthe
            else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--show") == 0) {
                // Si aucun labyrinthe n'est chargé
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                show.create();
                while (show.isOpen()) {
                    show.update();
                }
                show.destroy();
            }
            // Vérifie si le labyrinthe est valide
            else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verify") == 0) {
                // Si aucun labyrinthe n'est chargé
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                bool perfect = false;
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié le type d'algorithme
                    if (strcmp(argv[i + 1], "-p") == 0 || strcmp(argv[i + 1], "--perfect") == 0) {
                        i++;
                        perfect = true;
                    }
                }
                checker(&maze, perfect);
            }
            // Si l'utilisateur veut sauvegarder le labyrinthe chargé en mémoire
            else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                // Si aucun fichier n'est spécifié
                if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
                std::ofstream file(argv[i + 1]);
                // Si le fichier n'existe pas
                if (!file) {
                    std::cout << "File not found : " << argv[i + 1] << std::endl;
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
            // Si l'utilisateur veut charger un labyrinthe depuis un fichier
            else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
                // Si aucun fichier n'est spécifié
                if (i + 1 >= argc) return help(MAZE_COMMAND_ERROR);
                std::ifstream file(argv[i + 1]);
                // Si le fichier n'existe pas
                if (!file) {
                    std::cout << "File not found : " << argv[i + 1] << std::endl;
                    return 1;
                }
                maze = Maze();
                read(argv[i + 1], &maze);
                mazeLoaded = true;
                i++;
            }
            // Si l'utilisateur veut effacer le labyrinthe chargé en mémoire
            else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--clear") == 0) {
                std::cout << "Clear" << std::endl;
                // maze.freeMaze();
                show.destroy();
                mazeLoaded = false;
            }
            // Si l'utilisateur veut générer un labyrinthe
            else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--generate") == 0) {
                std::string type = "cours";
                int x = 10, y = 10;
                bool perfect = true;
                // Si l'utilisateur a spécifié des options
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié le type d'algorithme
                    if (strcmp(argv[i + 1], "-t") == 0 || strcmp(argv[i + 1], "--type") == 0) {
                        i++;
                        if (i + 1 < argc) {
                            if (strcmp(argv[i + 1], "cours") == 0) {
                                type = "cours";
                            } else if (strcmp(argv[i + 1], "perso") == 0) {
                                type = "perso";
                            } else if (strcmp(argv[i + 1], "1") == 0) {
                                type = "1";
                            } else {
                                return help(MAZE_COMMAND_ERROR);
                            }
                            i++;
                        }
                        std::cout << "Type : " << type << std::endl;
                    }
                }
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié les dimensions du labyrinthe
                    if (strcmp(argv[i + 1], "-d") == 0 || strcmp(argv[i + 1], "--dimension") == 0) {
                        i++;
                        if (i + 2 < argc) {
                            x = atoi(argv[i + 1]);
                            y = atoi(argv[i + 2]);
                            i += 2;
                        }
                        std::cout << "Dimension : " << x << "x" << y << std::endl;
                    }
                }
                if (i + 1 < argc) {
                    // Si l'utilisateur a spécifié que le labyrinthe n'est pas parfait
                    if (strcmp(argv[i + 1], "-u") == 0 || strcmp(argv[i + 1], "--unperfect") == 0) {
                        perfect = false;
                        i++;
                        std::cout << "Unperfect" << std::endl;
                    }
                }
                generateMaze(&maze, type, x, y, perfect);
                mazeLoaded = true;
            }
            // Si l'utilisateur veut résoudre un labyrinthe
            else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--resolve") == 0) {
                // Si aucun labyrinthe n'est chargé
                if (!mazeLoaded) {
                    std::cout << "No maze loaded" << std::endl;
                    return 1;
                }
                std::string algorithm = "aaa";
                // Si l'utilisateur a spécifié l'algorithme
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
            // Si l'utilisateur a spécifié une commande inconnue
            else {
                return help(argv[i], MAZE_COMMAND_ERROR);
            }
        }
    }

    return 0;
}
