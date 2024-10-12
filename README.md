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
sudo apt-get install g++ cmake make libsfml-dev
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
./main.out [-option] <instance_file>
```

### Options

#### Générales

* `-h` ou `--help` : Affiche cette aide
* `-s` ou `--show` : Affiche un labyrinthe (nécessite un labyrinthe en mémoire)
* `-o` ou `--output` `<fichier>` : Spécifie le fichier de sortie (nécessaire pour sauvegarder un labyrinthe, nécessite un labyrinthe en mémoire)
* `-i` ou `--input` `<fichier>` : Spécifie le fichier d'entrée (nécessaire pour utiliser un labyrinthe se trouvant dans un fichier texte)
* `-c` ou `--clear` : Efface le(s) labyrinthe(s) en mémoire

#### Génération de labyrinthe

* `-g` ou `--generate` : Génère un labyrinthe
	+ `-t` ou `--type` `<type>` : Spécifie le type d'algorithme à utiliser pour la génération (cours, perso, 1, par défaut : cours)
	+ `-d` ou `--dimension` `<x> <y>` : Spécifie les dimensions du labyrinthe à générer (par défaut : 10 10)
	+ `-u` ou `--unperfect` : Génère un labyrinthe imparfait (le labyrinthe généré est par défaut parfait)

#### Résolution de labyrinthe

* `-r` ou `--resolve` : Résout un labyrinthe (nécessite un labyrinthe en mémoire)
	+ `-a` ou `--algorithm` `<algorithme>` : Spécifie l'algorithme à utiliser pour la résolution (aaa, bbb, par défaut : aaa)

#### Vérification de labyrinthe

* `-v` ou `--verify` : Vérifie si un labyrinthe est parfait (nécessite un labyrinthe en mémoire)
  + `-p` ou `--perfect` : Vérifie si un labyrinthe est parfait (on ne vérifie pas la perfection par défaut)

### Codes d'erreur

- 0 : Aucune erreur
- 1 : Erreur dans les arguments de l'appel du fichier
- 2 : Erreur avec une intéraction sur un fichier (lecture ou écriture)
- 3 : Erreur lors de l'affichage d'un labyrinthe

## Exemples

- Générer un labyrinthe parfait avec l'algorithme perso de dimensions 10x10 et l'afficher puis l'enregistrer dans un fichier :
  ```bash
  ./main.out -g -t perso -d 10 10 -s -o labyrinthe.txt
  ```
- Résoudre un labyrinthe avec l'algorithme de aaa et l'afficher :
  ```bash
  ./main.out -i labyrinthe.txt -r -a aaa -s
  ```
