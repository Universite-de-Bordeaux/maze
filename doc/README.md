# Projet de programmation

## Description

L'objectif du projet et de programmer différent algorithme manipulant des labyrinthes.
Il y a différent type d'algorithme :

- Génération de labyrinthes
- Résolution de labyrinthes
- validation de labyrinthes
- Affichage de labyrinthes

## Algorithmes de génération

### Backtracking

Cet algorithmes créer un labyrinthe en se déplaçant aléatoirement dans le
labyrinthe en créant et détruisant des murs pour faire un chemin.
Le labyrinthe est intitialisé avec tous les murs.

Son fonctionnement est le suivant :
- On commence par choisir un cellule dans le labyrinthe, ce sera notre point
de départ.
- Ensuite, on marque cette cellule comme visitée et on se déplace aléatoirement
dans une cellule voisine non visitée en supprimant le mur entre les deux
cellules.
- Si toutes les cellules voisines ont été visitées, on revient en arrière
jusqu'à trouvé une cellule avec des voisins non visités.
- L'algorithme se termine quand on est revenu à la cellule de départ.

### Fractal

Cet algorithme génère un labyrinthes d'une manière qui fait penser aux fractales, d'ou son nom.
Le labyrinthe est initialisé comme un labirynthe de taille 1*1 qui ne contient donc aucun mur.

Son fonctionnement est le suivant : \
- On double la taille du labyrinthe en le dupliquant à droite, en bas, et en bas à droite. \
On se retrouve avec un labyrinthe composé de 4 partie identique.
- On ajoute des murs sur les ligne et colonne du milieu du labyrinthe i.e. on délimite les 4
parties de notre labyrinthe avec des mur. \
On a donc 4 délimitations, une entre les deux partie du haut, du bas, de gauche et de droite.
- On supprime, aléatoirement, 3 murs dans ces délimitations pour créer un chemin entre les 4 parties. \
Il faut pour cela que les mur choisis soit sur des délimitations différente à chaque fois.
- On répète le processus un nombre déterminé de fois.

### Diagonal

Cet algorithme génère un labyrinthe en le parcourant en diagonale.
Le labyrinthe est initialisé sans aucun murs.

Son fonctionnement est le suivant : \
- On commence par choisir un coins du labyrinthe aléatoirement.
-
