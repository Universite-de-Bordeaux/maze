# Classe [`Cell`](../../src/lib/cell.hpp)

## Description

La classe `Cell` représente une cellule dans un labyrinthe. Elle contient des informations sur sa position, ses murs, ses voisins, et son statut. Cette classe est essentielle pour construire et gérer dynamiquement un labyrinthe.

## Constructeurs

### `Cell()`
**Description**: Constructeur par défaut. Initialise une cellule avec des coordonnées x et y à 0, sans murs ni voisins.

### `Cell(int x, int y)`
**Description**: Constructeur qui initialise une cellule avec les coordonnées x et y spécifiées.
- **Paramètres**:
    - `x`: Coordonnée x de la cellule.
    - `y`: Coordonnée y de la cellule.

### `Cell(int x, int y, int width, int height)`
**Description**: Constructeur qui initialise une cellule avec les coordonnées x et y, ainsi que la largeur et la hauteur du labyrinthe.
- **Paramètres**:
    - `x`: Coordonnée x de la cellule.
    - `y`: Coordonnée y de la cellule.
    - `width`: Largeur du labyrinthe.
    - `height`: Hauteur du labyrinthe.

### `~Cell()`
**Description**: Destructeur. Libère les ressources allouées pour les murs de la cellule.

---

## Méthodes

### **Accesseurs**

#### `int getX() const`
- **Description**: Récupère la coordonnée x de la cellule.
- **Retour**: Un entier représentant la coordonnée x.

#### `int getY() const`
- **Description**: Récupère la coordonnée y de la cellule.
- **Retour**: Un entier représentant la coordonnée y.

---

### **Voisins**

#### `Cell **getNeighbors()`
- **Description**: Retourne un tableau des pointeurs vers les voisins de la cellule. Les voisins peuvent être situés à gauche, à droite, en haut ou en bas.
- **Retour**: Un tableau de pointeurs de type `Cell`.

#### `Cell *getNeighbor(int i) const`
- **Description**: Récupère un voisin de la cellule à partir de son index. L'index correspond à une direction spécifique (gauche, droite, haut, bas).
- **Paramètres**:
    - `i`: Index du voisin (0-3).
- **Retour**: Un pointeur vers le voisin à l'index spécifié.

#### `Cell *getRelativeNeighbor(int i) const`
- **Description**: Récupère un voisin relatif de la cellule, c'est-à-dire les cellules qui sont en contact direct avec la cellule actuelle, en tenant compte des limites du labyrinthe.
- **Paramètres**:
    - `i`: Index du voisin relatif (0-3).
- **Retour**: Un pointeur vers le voisin relatif à l'index spécifié.

---

### **Murs**

#### `Wall **getWalls()`
- **Description**: Retourne un tableau des pointeurs vers les murs de la cellule. Les murs peuvent être situés à gauche, à droite, en haut ou en bas.
- **Retour**: Un tableau de pointeurs de type `Wall`.

#### `Wall *getWall(int i) const`
- **Description**: Récupère un mur de la cellule à partir de son index.
- **Paramètres**:
    - `i`: Index du mur (0-3).
- **Retour**: Un pointeur vers le mur à l'index spécifié.

#### `bool isWall(int i) const`
- **Description**: Vérifie si un mur existe à l'index spécifié.
- **Paramètres**:
    - `i`: Index du mur à vérifier (0-3).
- **Retour**: Vrai si un mur existe à l'index spécifié, faux sinon.

---

### **Statut et Visite**

#### `bool isAlreadyVisited() const`
- **Description**: Vérifie si la cellule a déjà été visitée.
- **Retour**: Vrai si la cellule a déjà été visitée, faux sinon.

#### `void setAlreadyVisited(bool alreadyVisited)`
- **Description**: Définit le statut de visite de la cellule.
- **Paramètres**:
    - `alreadyVisited`: Une valeur booléenne indiquant si la cellule a été visitée.

#### `int getStatus() const`
- **Description**: Retourne le statut actuel de la cellule.
- **Retour**: Un entier représentant le statut de la cellule (par exemple, statut_IDLE, statut(Target), etc.).

#### `void setStatus(int status)`
- **Description**: Définit le statut de la cellule.
- **Paramètres**:
    - `status`: Un entier représentant le statut que doit posséder la cellule.

---

### **Navigation**

#### `int getAbsoluteNumberOfNeighbors() const`
- **Description**: Compte le nombre de voisins non nuls (non `null`) de la cellule.
- **Retour**: Un entier représentant le nombre de voisins non nuls.

#### `void getAbsoluteNeighbors(Cell **neighbors) const`
- **Description**: Remplit un tableau avec les voisins non nuls de la cellule.
- **Paramètres**:
    - `neighbors`: Un tableau de pointeurs de type `Cell` dans lequel les voisins non nuls sont stockés.

#### `int getAbsoluteNumberOfNeighborsNotVisited() const`
- **Description**: Compte le nombre de voisins non visités de la cellule.
- **Retour**: Un entier représentant le nombre de voisins non visités.

#### `void getAbsoluteNeighborsNotVisited(Cell **neighbors) const`
- **Description**: Remplit un tableau avec les voisins non visités de la cellule.
- **Paramètres**:
    - `neighbors`: Un tableau de pointeurs de type `Cell` dans lequel les voisins non visités sont stockés.

#### `int getRelativeNumberOfNeighborsNotVisited() const`
- **Description**: Compte le nombre de voisins relatifs non visités de la cellule. Les voisins relatifs sont ceux qui ne sont pas situés aux bords du labyrinthe.
- **Retour**: Un entier représentant le nombre de voisins relatifs non visités.

#### `void getRelativeNeighborsNotVisited(Cell **neighbors) const`
- **Description**: Remplit un tableau avec les voisins relatives non visités de la cellule.
- **Paramètres**:
    - `neighbors`: Un tableau de pointeurs de type `Cell` dans lequel les voisins relatifs non visités sont stockés.

---

### **Configuration**

#### `void setX(int x)`
- **Description**: Définit la coordonnée x de la cellule.
- **Paramètres**:
    - `x`: Une coordonnée x.

#### `void setY(int y)`
- **Description**: Définit la coordonnée y de la cellule.
- **Paramètres**:
    - `y`: Une coordonnée y.

#### `void setXY(int x, int y)`
- **Description**: Définit les coordonnées x et y de la cellule.
- **Paramètres**:
    - `x`: Une coordonnée x.
    - `y`: Une coordonnée y.

#### `void setNeighbors(Cell *neighbors[4])`
- **Description**: Définit les voisins de la cellule.
- **Paramètres**:
    - `neighbors`: Un tableau de pointeurs de type `Cell` qui contient les voisins.

#### `void setNeighbor(int i, Cell *neighbor)`
- **Description**: Définit un voisin de la cellule pour un index donné.
- **Paramètres**:
    - `i`: L'index du voisin (0-3).
    - `neighbor`: Un pointeur vers le voisin.

#### `void setWalls(Wall *walls[4])`
- **Description**: Définit les murs de la cellule.
- **Paramètres**:
    - `walls`: Un tableau de pointeurs de type `Wall` contenant les murs.

#### `void setWall(int i, Wall *wall)`
- **Description**: Définit un mur de la cellule pour un index donné.
- **Paramètres**:
    - `i`: L'index du mur (0-4).
    - `wall`: Un pointeur vers le mur.

---

### **Libération des Ressources**

#### `void freeWall(int i) const`
- **Description**: Libère un mur de la cellule. Cette méthode est utilisée pour éviter les fuites de mémoire.
- **Paramètres**:
    - `i`: L'index du mur à libérer (0-3).

#### `void freeWalls() const`
- **Description**: Libère tous les murs de la cellule.

---

## Conclusion

La classe `Cell` fournit une structure fondamentale pour représenter et gérer une cellule dans un labyrinthe. Elle inclut des méthodes pour accéder et modifier ses coordonnées, ses murs, ses voisins, et son statut. Ces fonctionnalités sont essentielles pour construire, afficher, et résoudre des labyrinthes dans différentes applications comme les jeux vidéo ou les algorithmes de recherche.