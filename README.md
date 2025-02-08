# Projet Maze

## Description

Le projet Maze est un projet de programmation en C++ réalisé dans le cadre de la formation CMI OPTIM.
Le but de ce projet est de générer des labyrinthes parfaits et imparfaits, de les résoudre et de les afficher en
utilisant plusieurs algorithmes de générations et de résolutions.

La description de la structure du projet peut être trouvé dans la [documentation](doc/README.md)

La description complète du projet peut être trouvé dans la [documentation](doc/documentation.pdf)

## Auteurs

- [**Arnaud Aloyse**](https://github.com/aloyse33)
- [**Facca Ethan**](https://github.com/untypequicode)
- [**Glasson Lucien**](https://github.com/lulu-froid)

## Prérequis

Pour compiler le projet, il est nécessaire d'avoir installé `g++`, `cmake`, `make` et `sfml` sur sa machine.

Pour installer ces outils, il suffit de lancer la commande suivante :

```bash
# Pour Debian et dérivés
sudo apt-get install g++ cmake make libsfml-dev
# Pour Arch Linux et dérivés
sudo pacman -S g++ cmake make sfml
# Pour Fedora et dérivés
sudo dnf install g++ cmake make SFML
# Pour NixOS
nix-env -i g++ cmake make sfml
```

## Compilation

Pour compiler le projet, il suffit de lancer la commande `cmake .` puis `make`.

```bash
cmake .
make
```

## Utilisation

L'utilisation de l'application de génération est la suivante :

```bash
./maze_generator.out [-option] [argument]
```

L'utilisation de l'application avec le reste des fonctionnalités est la suivante :

```bash
./maze.out [-option] [argument]
```

### Options

#### Générales

* `-h` ou `--help` : Affiche cette aide
* `-i` ou `--input` `<fichier>` : Spécifie le fichier d'un labyrinthe à charger en mémoire
* `-s` ou `--show` : Affiche le labyrinthe en mémoire
    + `-f` ou `--framerate` `<framerate>` : Spécifie le framerate de l'affichage (par défaut : 60)
    + `-ds` ou `--delay-show` `<delay>` : Spécifie le délai d'affichage entre chaque cellule en millisecondes (par défaut : 0.0 (précis à la microseconde))
* `-o` ou `--output` `<fichier>` : Spécifie le fichier où sauvegarder le labyrinthe en mémoire
* `-c` ou `--clear` : Efface le labyrinthe en mémoire
* `-cm` ou `--clear-maze` : Nettoie les cellules du labyrinthe en mémoire

> Il est possible de définir les valeurs framerate et delay-show dans le fichier .env
> ```dotenv
> FRAMERATE=60
> DELAY_SHOW=0.0
```

#### Génération de labyrinthe (maze_generator)

* `-g` ou `--generate` : Génère un labyrinthe (écrase le labyrinthe en mémoire)
* `-gs` ou `--generate-show` : Génère un labyrinthe et l'affiche pendant la génération (nécessite un labyrinthe en mémoire)
    + `-a` ou `--algorithm` `<algorithme>` : Spécifie l'algorithme à utiliser pour la génération (back_tracking (bt), wall_maker (wm), diagonal (d), fractal (f), par défaut : back_tracking)
    + `-d` ou `--dimension` `<largueur> <hauteur>` : Spécifie les dimensions du labyrinthe à générer (par défaut : 10 10)
    + `-i` ou `--imperfect` : Génère un labyrinthe imparfait (le labyrinthe généré est par défaut parfait)
        + `-p` ou `--probability` `<probabilité>` : Spécifie la probabilité de suppression d'un mur pour un labyrinthe imparfait (par défaut : 0.1 soit 10%)

#### Résolution de labyrinthe (maze)

* `-r` ou `--resolve` : Résout le labyrinthe en mémoire (nécessite un labyrinthe en mémoire)
* `-rs` ou `--resolve-show` : Résout le labyrinthe en mémoire et l'affiche pendant la résolution (nécessite un labyrinthe en mémoire)
    + `-a` ou `--algorithm` `<algorithme>` : Spécifie l'algorithme à utiliser pour la résolution (depth_first_left (dfl), depth_first_right (dfr), breadth_first (bf), par défaut : depth_first_left)

#### Vérification de labyrinthe (maze)

* `-v` ou `--verify` : Vérifie si un labyrinthe est parfait (nécessite un labyrinthe en mémoire)
* `-vs` ou `--verify-show` : Vérifie si un labyrinthe est valide et l'affiche pendant la vérification (nécessite un labyrinthe en mémoire)
    + `-p` ou `--perfect` : Vérifie si un labyrinthe est parfait (on ne vérifie pas la perfection par défaut)
    + `-a` ou `--algorithm` `<algorithme>` : Spécifie l'algorithme à utiliser pour la vérification (depth_first_left (dfl), depth_first_right (dfr), breadth_first (bf), par défaut : depth_first_left)

#### Jeu de labyrinthe (maze)

* `-g` ou `--game` : Lance le jeu de labyrinthe (nécessite un labyrinthe en mémoire)
* `-gs` ou `--game-show` : Lance le jeu de labyrinthe et l'affiche pendant le jeu (nécessite un labyrinthe en
      mémoire)
        + `-t` ou `--type` `<type>` : Spécifie le type de jeu à lancer (fog (f), fog_right (fr), fog_left (fl), walk (w), walk_ghost (wg), par défaut : fog)

## Lancement automatisé

### Lancement d'algorithmes

On peut lancer automatiquement nos algorithmes en utilisant la commande

```bash
make run_[algo/solver/checker]_[nom de l'algorithme à utiliser]
```

Par exemple pour générer un labyrinthe avec l'algorithme fractal :

```bash
make run_algo_fractal
```

Pour résoudre un labyrinthe avec l'algorithme breadth_first :

```bash
make run_solver_breadth_first
```

Pour jouer à un labyrinthe avec l'algorithme fog :

```bash
make run_game_fog
```

### Lancement de tests

On peut ajouter _test à la fin de la commande pour lancer les tests. Il est possibles
que cela fasse crasher le programme, car les tests vont dépasser les limites du programme

Par exemple pour tester les algorithmes de vérification de labyrinthe depth_first_left et depth_first_right :

```bash
make run_checker_depth_first_test
```

### Lancement particulier

Il existe 3 lancements particuliers

#### Lancement de tous les algorithmes

```bash
make run_all
```

#### Lancement de tous les tests

```bash
make run_all_test
```

#### Lancement d'un test manuel

```bash
make run_test
```

### Codes d'erreur

- 0 : Aucune erreur
- 1 : Erreur dans les arguments de l'appel du fichier
- 2 : Erreur avec une intéraction sur un fichier (lecture ou écriture)
- 3 : Erreur lors de l'affichage d'un labyrinthe

## Exemples

### Générer un labyrinthe

Pour générer un labyrinthe de dimensions 20x20 avec l'algorithme de back_tracking, il suffit de lancer la commande
suivante :

```bash
./maze_generator.out -g -d 20 20 -a bt
```

Pour générer un labyrinthe imparfait de dimensions 20x20 avec l'algorithme de wall_maker, il suffit de lancer la
commande suivante :

```bash
./maze_generator.out -g -d 20 20 -a wm -i
```

Pour générer un labyrinthe de dimensions 20x20 avec l'algorithme de diagonal, il suffit de lancer la commande suivante :

```bash
./maze_generator.out -g -d 20 20 -a d
```

Pour générer un labyrinthe de dimensions 20x20 avec l'algorithme de fractal, il suffit de lancer la commande suivante :

```bash
./maze_generator.out -g -d 10 10 -a f
```

### Résoudre un labyrinthe

Pour résoudre un labyrinthe avec l'algorithme de depth_first_left, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -r -a dfl
```

Pour résoudre un labyrinthe avec l'algorithme de depth_first_right, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -r -a dfr
```

Pour résoudre un labyrinthe avec l'algorithme de breadth_first, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -r -a bf
```

### Vérifier un labyrinthe

Pour vérifier si un labyrinthe est parfait avec l'algorithme de depth_first_left, il suffit de lancer la commande
suivante :

```bash
./maze.out -i labyrinthe.txt -v -a dfl
```

Pour vérifier si un labyrinthe est parfait avec l'algorithme de depth_first_right, il suffit de lancer la commande
suivante :

```bash
./maze.out -i labyrinthe.txt -v -a dfr
```

Pour vérifier si un labyrinthe est parfait avec l'algorithme de breadth_first, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -v -a bf
```

### Jouer à un labyrinthe

Pour jouer à un labyrinthe avec l'algorithme de fog, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -g -t f
```

Pour jouer à un labyrinthe avec l'algorithme de fog_right, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -g -t fr
```

### Afficher un labyrinthe

Pour afficher un labyrinthe, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -s
```

### Sauvegarder un labyrinthe

Pour sauvegarder un labyrinthe, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -o labyrinthe2.txt
```

### Nettoyer un labyrinthe

Pour nettoyer un labyrinthe, et manipuler deux labyrinthes, il suffit de lancer la commande suivante :

```bash
./maze.out -i labyrinthe.txt -r -a dfl -c -i labyrinthe2.txt -r -a dfr
```
