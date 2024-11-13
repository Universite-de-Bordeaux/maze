# Projet Maze

## Description

Le projet Maze est un projet de programmation en C++ réalisé dans le cadre de la formation CMI OPTIM.
Le but de ce projet est de générer des labyrinthes parfaits et imparfaits, de les résoudre et de les afficher en utilisant plusieurs algorithmes de générations et de résolutions.

## Auteurs

- [**Arnaud Aloyse**](https://github.com/aloyse33)
- [**Glasson Lucien**](https://github.com/lulu-froid)
- [**Facca Ethan**](https://github.com/untypequicode)

## Prérequis

Pour compiler le projet, il est nécessaire d'avoir installé `g++`, `cmake`, `make` et `sfml` sur sa machine.

Pour installer ces outils, il suffit de lancer la commande suivante :
```bash
# Pour Debian et dérivés
sudo apt-get install g++ cmake make libsfml-dev
# Pour Arch Linux et dérivés
sudo pacman -S g++ cmake make sfml
```

## Compilation

Pour compiler le projet, il suffit de lancer la commande `cmake .` puis `make`.

```bash
cmake .
make
```

## Utilisation

L'utilisation de l'application est la suivante :

```bash
./main.out [-option] [argument]
```

### Options

#### Générales

* `-h` ou `--help` : Affiche cette aide
* `-i` ou `--input` `<fichier>` : Spécifie le fichier d'un labyrinthe à charger en mémoire
* `-s` ou `--show` : Affiche le labyrinthe en mémoire
* `-o` ou `--output` `<fichier>` : Spécifie le fichier où sauvegarder le labyrinthe en mémoire
* `-c` ou `--clear` : Efface le labyrinthe en mémoire
  + `-cm` ou `--clear-maze` : Nettoie les cellules du labyrinthe en mémoire

#### Génération de labyrinthe

* `-g` ou `--generate` : Génère un labyrinthe (écrase le labyrinthe en mémoire)
  + `-gs` ou `--generate-show` : Génère un labyrinthe et l'affiche pendant la génération (nécessite un labyrinthe en mémoire)
  + `-a` ou `--algorithm` `<algorithme>` : Spécifie l'algorithme à utiliser pour la génération (backtracking (bt), wallmaker (wm), diagonal (d), fractal (f), par défaut : backtracking)
  + `-d` ou `--dimension` `<largueur> <hauteur>` : Spécifie les dimensions du labyrinthe à générer (par défaut : 10 10)
  + `-u` ou `--unperfect` : Génère un labyrinthe imparfait (le labyrinthe généré est par défaut parfait)

#### Résolution de labyrinthe

* `-r` ou `--resolve` : Résout le labyrinthe en mémoire
  + `-rs` ou `--resolve-show` : Résout le labyrinthe en mémoire et l'affiche pendant la résolution
  + `-a` ou `--algorithm` `<algorithme>` : Spécifie l'algorithme à utiliser pour la résolution (depthfirstleft (dfl), depthfirstright (dfr), breadthfirst (bf), par défaut : depthfirstleft)

#### Vérification de labyrinthe

* `-v` ou `--verify` : Vérifie si un labyrinthe est parfait (nécessite un labyrinthe en mémoire)
  + `-vs` ou `--verify-show` : Vérifie si un labyrinthe est valide et l'affiche pendant la vérification (nécessite un labyrinthe en mémoire)
  + `-p` ou `--perfect` : Vérifie si un labyrinthe est parfait (on ne vérifie pas la perfection par défaut)
  + `-a` ou `--algorithm` `<algorithme>` : Spécifie l'algorithme à utiliser pour la vérification (depthfirstleft (dfl), depthfirstright (dfr), breadthfirst (bf), par défaut : depthfirstleft)

### Codes d'erreur

- 0 : Aucune erreur
- 1 : Erreur dans les arguments de l'appel du fichier
- 2 : Erreur avec une intéraction sur un fichier (lecture ou écriture)
- 3 : Erreur lors de l'affichage d'un labyrinthe

## Exemples

### Générer un labyrinthe

Pour générer un labyrinthe de dimensions 20x20 avec l'algorithme de backtracking, il suffit de lancer la commande suivante :
```bash
./main.out -g -d 20 20 -a bt
```

Pour générer un labyrinthe imparfait de dimensions 20x20 avec l'algorithme de wallmaker, il suffit de lancer la commande suivante :
```bash
./main.out -g -d 20 20 -a wm -u
```

Pour générer un labyrinthe de dimensions 20x20 avec l'algorithme de diagonal, il suffit de lancer la commande suivante :
```bash
./main.out -g -d 20 20 -a d
```

Pour générer un labyrinthe de dimensions 20x20 avec l'algorithme de fractal, il suffit de lancer la commande suivante :
```bash
./main.out -g -d 20 20 -a f
```

### Résoudre un labyrinthe

Pour résoudre un labyrinthe avec l'algorithme de depthfirstleft, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -r -a dfl
```

Pour résoudre un labyrinthe avec l'algorithme de depthfirstright, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -r -a dfr
```

Pour résoudre un labyrinthe avec l'algorithme de breadthfirst, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -r -a bfs
```

### Vérifier un labyrinthe

Pour vérifier si un labyrinthe est parfait avec l'algorithme de depthfirstleft, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -v -a dfl
```

Pour vérifier si un labyrinthe est parfait avec l'algorithme de depthfirstright, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -v -a dfr
```

Pour vérifier si un labyrinthe est parfait avec l'algorithme de breadthfirst, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -v -a bf
```

### Afficher un labyrinthe

Pour afficher un labyrinthe, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -s
```

### Sauvegarder un labyrinthe

Pour sauvegarder un labyrinthe, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -o labyrinthe2.txt
```

### Nettoyer un labyrinthe

Pour nettoyer un labyrinthe, et manipuler deux labyrinthes, il suffit de lancer la commande suivante :
```bash
./main.out -i labyrinthe.txt -r -a dfl -c -i labyrinthe2.txt -g -d 20 20 -a bt
```