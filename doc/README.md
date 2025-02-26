# Structure du Projet

Le projet est organisé de manière modulaire et hiérarchique pour faciliter la lecture, la maintenance et le
développement.
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
│   ├── main.hpp                   # Fichier principal du résolveur, vérificateur et joueur
│   ├── maze_generator.hpp         # Fichier principal du générateur
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
- [Documentation complete](classes/cell.md)

### 2. `Maze`

- Représente l'ensemble du labyrinthe.
- Attributs :
    - Largeur et hauteur du labyrinthe.
    - Grille de cellules.
    - Positions de départ et d'arrivée.
- [Documentation complete](classes/maze.md)

### 3. `Wall`

- Représente un mur d'une cellule.
- Attributs :
    - Type de mur (nord, sud, est, ouest).
    - État du mur (présent ou absent).
- [Documentation complete](classes/wall.md)

### 4. `Queue` et `Stack`

- Structures de données utilisées dans les algorithmes de résolution.
- [Documentation Queue](classes/queue.md)
- [Documentation Stack](classes/stack.md)

### 5. `Reader` et `Writer`

- Gèrent la lecture et l'écriture des labyrinthes dans des fichiers.
- [Documentation Reader](classes/reader.md)
- [Documentation Writer](classes/writer.md)

### 6. `Show`

- Gère l'affichage du labyrinthe
- [Documentation complete](classes/show.md)

### 7. `Rand`

- Simplifie l'utilisation de la librairie random
- [Documentation complete](classes/rand.md)

## Algorithmes Implémentés

Le projet implémente plusieurs algorithmes pour la génération, la résolution et la vérification des labyrinthes :

### Génération de Labyrinthes

1. **Backtracking** :
    - Créé en supprimant aléatoirement des murs tout en garantissant la connectivité.
    - Fichier :  [`src/lib/algo/back_tracking.hpp`](../src/lib/algo/back_tracking.hpp).

2. **Wall Maker** :
    - Construit les murs de manière aléatoire tout en respectant certaines contraintes.
    - Fichier : [`src/lib/algo/wall_maker.hpp`](../src/lib/algo/wall_maker.hpp).

3. **Diagonal** :
    - Génère des labyrinthes en suivant une logique diagonale.
    - Fichier : [`src/lib/algo/diagonal.hpp`](../src/lib/algo/diagonal.hpp).

4. **Fractal** :
    - Créé des labyrinthes à base de motifs répétitifs.
    - Fichier : [`src/lib/algo/fractal.hpp`](../src/lib/algo/fractal.hpp).

### Résolution de Labyrinthes

1. **Recherche en Profondeur (DFS)** :
    - Exploration exhaustive des chemins.
    - Fichier : [`src/lib/solver/depth_first.hpp`](../src/lib/solver/depth_first.hpp).

2. **Recherche en Largeur (BFS)** :
    - Exploration niveau par niveau.
    - Fichier : [`src/lib/solver/breadth_first.hpp`](../src/lib/solver/breadth_first.hpp).

### Vérification de Labyrinthes

1. **DFS** :
    - Vérifie si le labyrinthe est parfait (sans cycles).
    - Fichier : [`src/lib/checker/depth_first.hpp`](../src/lib/checker/depth_first.hpp).

2. **BFS** :
    - Vérifie la connectivité du labyrinthe.
    - Fichier : [`src/lib/checker/breadth_first.hpp`](../src/lib/checker/breadth_first.hpp).

### Jeu et visite dans le Labyrinthe

1. **Fog** :
    - Visite dans le brouillard.
    - Fichier : [`src/lib/game/fog.hpp`](../src/lib/game/fog.hpp).

2. **Fog Hand** :
    - Visite dans le brouillard avec la main gauche ou droite.
    - Fichier : [`src/lib/game/fog_hand.hpp`](../src/lib/game/fog_hand.hpp).

3. **Dead End** :
    - Visite en marquant dans les culs-de-sac.
    - Fichier : [`src/lib/game/dead_end.hpp`](../src/lib/game/dead_end.hpp).

4. **Dead End Hand** :
    - Visite en marquant dans les culs-de-sac avec la main gauche ou droite.
    - Fichier : [`src/lib/game/dead_end_hand.hpp`](../src/lib/game/dead_end_hand.hpp).

5. **Tom Thumb** :
    - Visite en marquant les cellules visitées.
    - Fichier : [`src/lib/game/tom_thumb.hpp`](../src/lib/game/tom_thumb.hpp).

6. **Tom Thumb Hand** :
    - Visite en marquant les cellules visitées avec la main gauche ou droite.
    - Fichier : [`src/lib/game/tom_thumb_hand.hpp`](../src/lib/game/tom_thumb_hand.hpp).

7. **Splatoon** :
    - Visite en marquant le nombre de passages par cellule.
    - Fichier : [`src/lib/game/splatoon.hpp`](../src/lib/game/splatoon.hpp).

8. **Splatoon Hand** :
    - Visite en marquant le nombre de passages par cellule avec la main gauche ou droite.
    - Fichier : [`src/lib/game/splatoon_hand.hpp`](../src/lib/game/splatoon_hand.hpp).

9. **Splatoon Dead End** :
    - Visite en marquant le nombre de passages par cellule et les culs-de-sac.
    - Fichier : [`src/lib/game/splatoon_dead_end.hpp`](../src/lib/game/splatoon_dead_end.hpp).

10. **Splatoon Dead End Hand** :
    - Visite en marquant le nombre de passages par cellule et les culs-de-sac avec la main gauche ou droite.
    - Fichier : [`src/lib/game/splatoon_dead_end_hand.hpp`](../src/lib/game/splatoon_dead_end_hand.hpp).

2. **Walk** :
    - Marche interactive dans le labyrinthe.
    - Fichier : [`src/lib/game/walk.hpp`](../src/lib/game/walk.hpp).

## Fichiers Principaux

### 1. `main.hpp`

- Contient le programme principal pour résoudre, vérifier et jouer dans un labyrinthe.
- Fonctionnalités :
    - Chargement d'un labyrinthe depuis un fichier.
    - Résolution du labyrinthe.
    - Vérification de l'intégrité.
    - Mode jeu interactif.

### 2. `maze_generator.hpp`

- Contient le programme de génération de labyrinthes.
- Fonctionnalités :
    - Génération de labyrinthes parfaits ou imparfaits.
    - Sauvegarde du labyrinthe dans un fichier.

## Liens Utiles

- **Rapport de Projet** : [Rapport PDF](rapport.pdf)
- **Repository GitHub** : [Lien GitHub](https://github.com/Universite-de-Bordeaux/maze)