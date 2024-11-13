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
- À chaque étape, il place des murs horizontalement ou verticalement, en fonction de la position actuelle. Une ouverture est laissée à un endroit choisi aléatoirement pour permettre un passage.

### Wallmaker

Cet algorithme génère un labyrinthe en créant des murs aléatoirement.
Le labyrinthe est initialisé sans aucun murs.

Son fonctionnement est le suivant : \
- On part d'une grille vide et on va créer les murs.
- On crée un tableau avec tous les murs possible de la grille.
- On a choisi un mur aléatoirement dans la liste et on vérifie :
    - si le mur appartient à une chaine de mur (côte à côte) :
        - si oui : si la chaine de mur touche deux fois le bord du labyrinthe → le mur ne peut pas être mis là, donc on l’enlève ce mur du tableau.
    - sinon : on pose le mur et on l’enlève du tableau
    - On sait le nb de mur au maximum que l’on doit poser (L-1)*(l-1)


## Algorithmes de résolution

### Depth First Search

Le parcours en profondeur (Depth-First Search) est un algorithme de recherche qui explore un chemin en allant aussi loin que possible dans une direction avant de revenir en arrière pour explorer d'autres chemins.

Son fonctionnement est le suivant : \
- Commencer à partir de la cellule de départ du labyrinthe. Marquer cette cellule comme visitée.

Exploration des chemins :
- Depuis la cellule courante, sélectionner une cellule voisine qui n’a pas encore été visitée et qui n’est pas bloquée par un mur.
- Aller dans cette cellule et marquer ce nouveau point comme visité.

Retour en arrière :
- Si la cellule courante n'a aucune cellule voisine accessible et non visitée, revenir à la cellule précédente (retour en arrière dans la pile des cellules visitées).
- Continuer ce processus jusqu'à trouver la cellule de sortie ou épuiser toutes les options.

- L'algorithme se termine une fois que la sortie du labyrinthe est atteinte, ou qu'il n'existe plus de cellules non visitées accessibles, signalant qu'il n'y a pas de solution.

### Breadth First Search

Le parcours en largeur (Breadth-First Search) est un algorithme de recherche qui visite d'abord tous les voisins directs d'un point avant de passer aux voisins de ces voisins, garantissant ainsi de trouver le chemin le plus court vers une cible si elle existe.

Son fonctionnement est le suivant : \
- Commencer à partir de la cellule de départ. Placer cette cellule dans une file d'attente et marquer comme visitée.

Exploration par niveaux :
- Tant que la file d'attente n'est pas vide, retirer la cellule en tête de la file (cellule actuelle).
- Examiner toutes les cellules voisines accessibles (sans murs).
- Pour chaque voisine non encore visitée, l'ajouter à la file d'attente, marquer comme visitée.

Trouver la sortie :
- Ce processus se poursuit jusqu'à atteindre la cellule de sortie (si elle est accessible) ou jusqu'à ce que la file soit vide.
- À chaque étape, l'algorithme explore d'abord les cellules les plus proches, garantissant ainsi de trouver le chemin le plus court.


- L'algorithme se termine lorsqu'il atteint la sortie, ou qu'il a exploré toutes les cellules accessibles sans trouver de solution.

### Validation de labyrinthes

Cet algorithme utilise une approche récursive pour vérifier la validité d'un labyrinthe et sa perfection (absence de cycles). En fonction du type de vérification souhaité (simple ou parfaite), il utilise différentes stratégies de parcours pour déterminer si toutes les cellules du labyrinthe sont accessibles et correctement connectées.

Son fonctionnement est le suivant : \

- L’algorithme commence par vérifier chaque cellule du labyrinthe en utilisant une approche récursive. Il vérifie d'abord si le labyrinthe est valide et, si nécessaire, s'il est parfait.

Exploration des cellules :
- Chaque cellule est marquée comme visitée et ses voisins non visités sont explorés.
- Si une cellule n'a plus de voisins accessibles, elle est marquée comme un cul-de-sac.
- Pour un labyrinthe parfait, l'algorithme vérifie également qu'il n'y a pas de cycles (plus de 2 voisins déjà visités).

Vérification de la validité :
- L'algorithme parcourt toutes les cellules et s'assure qu'elles sont toutes accessibles.
- Si un cycle est détecté dans un labyrinthe parfait, il est marqué comme non parfait.


- Lorsque toutes les cellules sont explorées, l’algorithme affiche si le labyrinthe est valide et, si vérifié, s'il est parfait.
