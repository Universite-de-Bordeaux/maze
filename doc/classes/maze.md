# Classe [`Maze`](../../src/lib/maze.hpp)

## Description

La classe `Maze` représente un labyrinthe. Elle gère l'initialisation, la génération, et la manipulation des cellules et
des murs du labyrinthe. Cette classe permet de créer, modifier, et afficher dynamiquement un labyrinthe.

## Constructeurs

### `Maze()`

**Description**:

Constructeur par défaut. Initialise un labyrinthe avec des dimensions par défaut (0x0).

### `Maze(int width, int height)`

**Description**:

Constructeur qui initialise un labyrinthe avec la largeur et la hauteur spécifiées. Les coordonnées de départ et
d'arrivée sont générées aléatoirement.

- **Paramètres**:
    - `width`: Largeur du labyrinthe.
    - `height`: Hauteur du labyrinthe.

### `Maze(int width, int height, int startX, int startY, int endX, int endY)`

**Description**:

Constructeur qui initialise un labyrinthe avec la largeur, la hauteur, et les coordonnées de départ et d'arrivée
spécifiées.

- **Paramètres**:
    - `width`: Largeur du labyrinthe.
    - `height`: Hauteur du labyrinthe.
    - `startX`: Coordonnée x de la cellule de départ.
    - `startY`: Coordonnée y de la cellule de départ.
    - `endX`: Coordonnée x de la cellule d'arrivée.
    - `endY`: Coordonnée y de la cellule d'arrivée.

### `~Maze()`

**Description**:

Destructeur. Libère la mémoire allouée pour le labyrinthe.

---

## Méthodes

### **Accesseurs**

#### `int getWidth() const`

- **Description** : Retourne la largeur du labyrinthe.
- **Retour** : Un entier représentant la largeur du labyrinthe.

#### `int getHeight() const`

- **Description** : Retourne la hauteur du labyrinthe.
- **Retour** : Un entier représentant la hauteur du labyrinthe.

#### `int getSize() const`

- **Description** : Retourne la taille totale du labyrinthe (largeur × hauteur).
- **Retour** : Un entier représentant la taille du labyrinthe.

#### `Cell ***getCells() const`

- **Description** : Retourne un tableau tridimensionnel contenant toutes les cellules du labyrinthe.
- **Retour** : Un tableau tridimensionnel de pointeurs de type `Cell`.

#### `Cell *getCell(int x, int y) const`

- **Description** : Récupère une cellule spécifique dans le labyrinthe à partir de ses coordonnées x et y.
- **Paramètres** :
    - `x`: Coordonnée x de la cellule.
    - `y`: Coordonnée y de la cellule.
- **Retour** : Un pointeur vers la cellule à la position (x, y) ou `nullptr` si les coordonnées sont invalides.

#### `Wall *getWall(int x, int y, bool horizontal) const`

- **Description** : Récupère un mur à partir de ses coordonnées x et y, et indique si ce mur est horizontal.
- **Paramètres**:
    - `x`: Coordonnée x du mur.
    - `y`: Coordonnée y du mur.
    - `horizontal`: `true` si le mur est horizontal, `false` s'il est vertical.
- **Retour** : Un pointeur vers le mur à la position (x, y) ou `nullptr` si les coordonnées sont invalides.

#### `int getStartX() const`

- **Description** : Récupère la coordonnée x de la cellule de départ.
- **Retour** : Un entier représentant la coordonnée x de la cellule de départ.

#### `int getStartY() const`

- **Description** : Récupère la coordonnée y de la cellule de départ.
- **Retour** : Un entier représentant la coordonnée y de la cellule de départ.

#### `int getEndX() const`

- **Description** : Récupère la coordonnée x de la cellule d'arrivée.
- **Retour** : Un entier représentant la coordonnée x de la cellule d'arrivée.

#### `int getEndY() const`

- **Description** : Récupère la coordonnée y de la cellule d'arrivée.
- **Retour** : Un entier représentant la coordonnée y de la cellule d'arrivée.

#### `Cell *getStartCell() const`

- **Description** : Récupère la cellule de départ.
- **Retour** : Un pointeur vers la cellule de départ.

#### `Cell *getEndCell() const`

- **Description** : Récupère la cellule d'arrivée.
- **Retour** : Un pointeur vers la cellule d'arrivée.

---

### **Configuration**

#### `void setWidthHeight(int width, int height)`

- **Description** : Définit la largeur et la hauteur du labyrinthe. Les coordonnées de départ et d'arrivée sont générées
  aléatoirement.
- **Paramètres**:
    - `width`: Nouvelle largeur du labyrinthe.
    - `height`: Nouvelle hauteur du labyrinthe.

#### `void setWidthHeight(int width, int height, int startX, int startY, int endX, int endY)`

- **Description** : Définit la largeur, la hauteur, et les coordonnées de départ et d'arrivée du labyrinthe.
- **Paramètres**:
    - `width`: Nouvelle largeur du labyrinthe.
    - `height`: Nouvelle hauteur du labyrinthe.
    - `startX`: Nouvelles coordonnées x de la cellule de départ.
    - `startY`: Nouvelles coordonnées y de la cellule de départ.
    - `endX`: Nouvelles coordonnées x de la cellule d'arrivée.
    - `endY`: Nouvelles coordonnées y de la cellule d'arrivée.

#### `void setCells(Cell ***cells)`

- **Description** : Définit les cellules du labyrinthe.
- **Paramètres**:
    - `cells`: Tableau tridimensionnel des cellules du labyrinthe.

#### `void setCell(int x, int y, Cell *cell) const`

- **Description** : Remplace une cellule dans le labyrinthe à une position spécifique.
- **Paramètres**:
    - `x`: Coordonnée x de la cellule à remplacer.
    - `y`: Coordonnée y de la cellule à remplacer.
    - `cell`: Nouvelle cellule à insérer à la position (x, y).

#### `void setStart(int x, int y)`

- **Description** : Définit les coordonnées de la cellule de départ.
- **Paramètres**:
    - `x`: Nouvelles coordonnées x de la cellule de départ.
    - `y`: Nouvelles coordonnées y de la cellule de départ.

#### `void setEnd(int x, int y)`

- **Description** : Définit les coordonnées de la cellule d'arrivée.
- **Paramètres**:
    - `x`: Nouvelles coordonnées x de la cellule d'arrivée.
    - `y`: Nouvelles coordonnées y de la cellule d'arrivée.

---

### **Murs**

#### `bool addWall(int x, int y, bool horizontal) const`

- **Description** : Ajoute un mur à une position spécifique dans le labyrinthe. Si le mur est ajouté, les cellules
  adjacentes sont mises à jour pour refléter l'existence du mur.
- **Paramètres**:
    - `x`: Coordonnée x du mur.
    - `y`: Coordonnée y du mur.
    - `horizontal`: `true` si le mur est horizontal, `false` s'il est vertical.
- **Retour** : `true` si le mur a été ajouté avec succès, `false` sinon.

#### `bool addWall(const Cell *cell1, const Cell *cell2) const`

- **Description** : Ajoute un mur entre deux cellules adjacentes.
- **Paramètres**:
    - `cell1`: Pointeur vers la première cellule.
    - `cell2`: Pointeur vers la seconde cellule.
- **Retour** : `true` si le mur a été ajouté avec succès, `false` sinon.

#### `bool removeWall(int x, int y, bool horizontal) const`

- **Description** : Supprime un mur à une position spécifique dans le labyrinthe. Les cellules adjacentes sont mises à
  jour pour refléter la suppression du mur.
- **Paramètres**:
    - `x`: Coordonnée x du mur.
    - `y`: Coordonnée y du mur.
    - `horizontal`: `true` si le mur est horizontal, `false` s'il est vertical.
- **Retour** : `true` si le mur a été supprimé avec succès, `false` sinon.

#### `bool removeWall(const Cell *cell1, const Cell *cell2) const)`

- **Description** : Supprime un mur entre deux cellules adjacentes.
- **Paramètres**:
    - `cell1`: Pointeur vers la première cellule.
    - `cell2`: Pointeur vers la seconde cellule.
- **Retour** : `true` si le mur a été supprimé avec succès, `false` sinon.

---

### **Génération et Nettoyage**

#### `void generate()`

- **Description** : Génère un nouveau labyrinthe. Si un labyrinthe existe déjà, il est libéré de la mémoire.
- **Effets**:
    - Crée un tableau tridimensionnel de cellules.
    - Initialisation des voisins des cellules via `initNeighborsCells_()`.

#### `void initNeighborsCells_() const`

- **Description** : Initialise les voisins de chaque cellule dans le labyrinthe.
- **Effets**:
    - Parcourt chaque cellule et définit ses voisins (gauche, droite, haut, bas).

#### `void freeMaze()`

- **Description** : Libère la mémoire allouée pour le labyrinthe.
- **Effets**:
    - Libère les pointeurs de cellules.
    - Réinitialise les coordonnées de départ et d'arrivée.

#### `void clearMaze() const`

- **Description** : Efface l'état du labyrinthe en remettant toutes les cellules au statut initial.
- **Effets**:
    - Réinitialise `alreadyVisited` à `false` pour toutes les cellules.
    - Réinitialise `status` à `MAZE_STATUS_IDLE` pour toutes les cellules.

---

## Gestionnaires Privés

#### `Rand *getRand()`

- **Description** : Retourne le générateur de nombres aléatoires utilisé par le labyrinthe.
- **Retour** : Un pointeur vers l'objet `Rand`.