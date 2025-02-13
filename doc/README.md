# Structure du Projet

Le projet est organisé de manière modulaire et hiérarchique pour faciliter la lecture, la maintenance et le développement.
Voici une description détaillée de la structure du projet :

## Sommaire

1. [Introduction](#introduction)
2. [Structure du Projet](#structure-du-projet)
3. [Classes du Projet](#classes-du-projet)
4. [Algorithmes Implémentés](#algorithmes-implémentés)
5. [Fichiers Principaux](#fichiers-principaux)

## Introduction

Ce document décrit en détail la structure du projet de programmation de labyrinthes.
Il explique l'organisation des dossiers, les classes utilisées et les algorithmes implémentés.

## Structure du Projet

Le projet est divisé en plusieurs dossiers principaux :

```
maze_project/
├── doc/                           # Documentation du projet
│   ├── README.md                  # Présentation générale
│   └── rapport.pdf                # Document technique complet
├── src/                           # Code source
│   ├── main.cpp                   # Fichier principal du résolveur, vérificateur et joueur
│   ├── maze_generator.cpp         # Fichier principal du générateur
│   └── instances/                 # Exemples de labyrinthes
│   └── lib/                       # Bibliothèques
│       └── algo/                  # Algorithmes de génération
│       └── checker/               # Algorithmes de vérification
│       └── game/                  # Jeux et visites interactives
│       └── solver/                # Algorithmes de résolution
└── CMakeLists.txt                 # Fichier de compilation
```

## Classes du Projet

Les classes suivantes sont utilisées dans le projet :

### 1. `Cell`
- Représente une cellule du labyrinthe.
- Attributs :
    - Coordonnées (x, y) de la cellule.
    - Tableau des murs (nord, sud, est, ouest).
    - État de visite.
- [Documentation complete](doc/classes/cell.md)

### 2. `Maze`
- Représente l'ensemble du labyrinthe.
- Attributs :
    - Largeur et hauteur du labyrinthe.
    - Grille de cellules.
    - Positions de départ et d'arrivée.
- [Documentation complete](doc/classes/maze.md)

### 3. `Wall`
- Représente un mur d'une cellule.
- Attributs :
    - Type de mur (nord, sud, est, ouest).
    - État du mur (présent ou absent).
- [Documentation complete](doc/classes/wall.md)

### 4. `Queue` et `Stack`
- Structures de données utilisées dans les algorithmes de résolution.
- [Documentation Queue](doc/classes/queue.md)
- [Documentation Stack](doc/classes/stack.md)

### 5. `Reader` et `Writer`
- Gèrent la lecture et l'écriture des labyrinthes dans des fichiers.
- [Documentation Reader](doc/classes/reader.md)
- [Documentation Writer](doc/classes/writer.md)

### 6. `Show`
- Gère l'affichage du labyrinthe
- [Documentation complete](doc/classes/show.md)

### 7. `Rand`
- Simplifie l'utilisation de la librairie random
- [Documentation complete](doc/classes/rand.md)

## Algorithmes Implémentés

Le projet implémente plusieurs algorithmes pour la génération, la résolution et la vérification des labyrinthes :

### Génération de Labyrinthes
1. **Backtracking** :
    - Créé en supprimant aléatoirement des murs tout en garantissant la connectivité.
    - Fichier : `lib/algorithms/generation/backtracking.cpp`.

2. **Wall Maker** :
    - Construit les murs de manière aléatoire tout en respectant certaines contraintes.
    - Fichier : `lib/algorithms/generation/wall_maker.cpp`.

3. **Diagonal** :
    - Génère des labyrinthes en suivant une logique diagonale.
    - Fichier : `lib/algorithms/generation/diagonal.cpp`.

4. **Fractal** :
    - Créé des labyrinthes à base de motifs répétitifs.
    - Fichier : `lib/algorithms/generation/fractal.cpp`.

### Résolution de Labyrinthes
1. **Recherche en Profondeur (DFS)** :
    - Exploration exhaustive des chemins.
    - Fichier : `lib/algorithms/solving/depth_first.cpp`.

2. **Recherche en Largeur (BFS)** :
    - Exploration niveau par niveau.
    - Fichier : `lib/algorithms/solving/breadth_first.cpp`.

### Vérification de Labyrinthes
1. **DFS** :
    - Vérifie si le labyrinthe est parfait (sans cycles).
    - Fichier : `lib/algorithms/checking/depth_first.cpp`.

2. **BFS** :
    - Vérifie la connectivité du labyrinthe.
    - Fichier : `lib/algorithms/checking/breadth_first.cpp`.

### Jeu et visite dans le Labyrinthe
1. **Fog** :
    - Marche avec un champ de vision limité.
    - Fichier : `lib/algorithms/game/fog.cpp`.

2. **Walk** :
    - Marche interactive dans le labyrinthe.
    - Fichier : `lib/algorithms/game/walk.cpp`.

## Fichiers Principaux

### 1. `main.cpp`
- Contient le programme principal pour résoudre, vérifier et jouer dans un labyrinthe.
- Fonctionnalités :
    - Chargement d'un labyrinthe depuis un fichier.
    - Résolution du labyrinthe.
    - Vérification de l'intégrité.
    - Mode jeu interactif.

### 2. `maze_generator.cpp`
- Contient le programme de génération de labyrinthes.
- Fonctionnalités :
    - Génération de labyrinthes parfaits ou imparfaits.
    - Sauvegarde du labyrinthe dans un fichier.

## Liens Utiles

- **Rapport de Projet** : [Rapport PDF](doc/rapport.pdf)
- **Repository GitHub** : [Lien GitHub](https://github.com/Universite-de-Bordeaux/maze)