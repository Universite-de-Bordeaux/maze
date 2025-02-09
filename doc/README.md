# Projet de Programmation de Labyrinthes

Bienvenue dans notre projet de programmation de labyrinthes ! Ce document vous guidera à travers la structure de notre projet et vous expliquera comment il fonctionne.

## Structure du Projet

Notre projet est organisé en plusieurs dossiers et fichiers, chacun ayant un rôle spécifique. Voici un aperçu de la structure du projet :

---

## Dossier `doc`
Ce dossier contient toute la documentation relative au projet.

## Dossier `src`
Le dossier `src` est le cœur du projet et contient plusieurs sous-dossiers et fichiers :

### Dossier `asserts`
Ce dossier contient les ressources nécessaires au projet.

### Dossier `instances`
Ce dossier contient des instances de labyrinthes pour tester le programme.

### Dossier `lib`
Le dossier `lib` est subdivisé en plusieurs sous-dossiers :

#### Dossier `algo`
Ce dossier contient les algorithmes de génération de labyrinthes :
- `back_tracking.cpp` et `back_tracking.hpp` : Algorithme de génération par backtracking.
- `diagonal.cpp` et `diagonal.hpp` : Algorithme de génération en diagonale.
- `fractal.cpp` et `fractal.hpp` : Algorithme de génération fractale.
- `wall_maker.cpp` et `wall_maker.hpp` : Algorithme de génération par ajout de murs.

#### Dossier `solver`
Ce dossier contient les algorithmes de résolution de labyrinthes :
- `breadth_first.cpp` et `breadth_first.hpp` : Algorithme de résolution par recherche en largeur.
- `depth_first.cpp` et `depth_first.hpp` : Algorithme de résolution par recherche en profondeur.

#### Dossier `checker`
Ce dossier contient les algorithmes de vérification de labyrinthes :
- `breadth_first.cpp` et `breadth_first.hpp` : Algorithme de vérification par recherche en largeur.
- `depth_first.cpp` et `depth_first.hpp` : Algorithme de vérification par recherche en profondeur.

#### Dossier `game`
Ce dossier contient les algorithmes de jeu dans un labyrinthe :
- `fog.cpp` et `fog.hpp` : Algorithme de jeu avec brouillard.
- `fog_hand.cpp` et `fog_hand.hpp` : Algorithme de jeu avec brouillard et méthode de la main gauche/droite.
- `walk.cpp` et `walk.hpp` : Algorithme de jeu avec déplacement manuel.

### Fichiers de Classes
Ces fichiers contiennent les définitions et prototypes des classes utilisées dans le projet :
- `cell.cpp` et `cell.hpp` : Classe `Cell` représentant une cellule d'un labyrinthe. [Documentation de la classe Cell](doc_classe/doc_classe_cell.md)
- `maze.cpp` et `maze.hpp` : Classe `Maze` représentant un labyrinthe. [Documentation de la classe Maze](doc_classe/doc_classe_maze.md)
- `wall.cpp` et `wall.hpp` : Classe `Wall` représentant un mur d'une cellule d'un labyrinthe. [Documentation de la classe Wall](doc_classe/doc_classe_wall.md)
- `queue.cpp` et `queue.hpp` : Classe `Queue` représentant une file. [Documentation de la classe Queue](doc_classe/doc_classe_queue.md)
- `reader.cpp` et `reader.hpp` : Classe `Reader` permettant de lire un labyrinthe depuis un fichier. [Documentation de la classe Reader](doc_classe/doc_classe_reader.md)
- `show.cpp` et `show.hpp` : Classe `Show` permettant d'afficher un labyrinthe. [Documentation de la classe Show](doc_classe/doc_classe_show.md)
- `stack.cpp` et `stack.hpp` : Classe `Stack` représentant une pile. [Documentation de la classe Stack](doc_classe/doc_classe_stack.md)
- `writer.cpp` et `writer.hpp` : Classe `Writer` permettant d'écrire un labyrinthe dans un fichier. [Documentation de la classe Writer](doc_classe/doc_classe_writer.md)
- `var.hpp` : Contient les variables globales du programme.

### Fichiers Principaux
- `main.cpp` : Contient le programme principal.
- `main_generator.cpp` : Contient le programme de génération de labyrinthes.
