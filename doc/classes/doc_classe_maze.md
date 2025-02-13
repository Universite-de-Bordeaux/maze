# Classe `Maze`

---

### Maze()
Constructeur par défaut de la classe Maze.

**Paramètres** : Aucun

**Renvoie** :  *Maze*  Une instance de Maze

---

### Maze( width, height)
Constructeur de la classe Maze avec largeur et hauteur.

**Paramètres** :
- *int*  width : Largeur du labyrinthe
- *int*  height : Hauteur du labyrinthe

**Renvoie** :  *Maze*  Une instance de Maze

---

### Maze( width, height, startX, startY, endX, endY)
Constructeur de la classe Maze avec largeur, hauteur, coordonnées de départ et coordonnées de fin.

**Paramètres** :
- *int*  width : Largeur du labyrinthe
- *int*  height : Hauteur du labyrinthe
- *int*  startX : Coordonnée X de départ
- *int*  startY : Coordonnée Y de départ
- *int*  endX : Coordonnée X de fin
- *int*  endY : Coordonnée Y de fin

**Renvoie** :  *Maze*  Une instance de Maze

---

### ~Maze()
Destructeur de la classe Maze.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### getWidth()
Retourne la largeur du labyrinthe.

**Paramètres** : Aucun

**Renvoie** :  *int*  Largeur du labyrinthe

---

### getHeight()
Retourne la hauteur du labyrinthe.

**Paramètres** : Aucun

**Renvoie** :  *int*  Hauteur du labyrinthe

---

### getSize()
Retourne la taille du labyrinthe (largeur * hauteur).

**Paramètres** : Aucun

**Renvoie** :  *int*  Taille du labyrinthe

---

### getCells()
Retourne les cellules du labyrinthe.

**Paramètres** : Aucun

**Renvoie** :  *Cell***  Tableau de pointeurs vers les cellules du labyrinthe

---

### getCell( x, y)
Retourne la cellule à la position spécifiée.

**Paramètres** :
- *int*  x : Coordonnée X de la cellule
- *int*  y : Coordonnée Y de la cellule

**Renvoie** :  *Cell*  Pointeur vers la cellule à la position spécifiée

---

### getWall( x, y, horizontal)
Retourne le mur à la position spécifiée.

**Paramètres** :
- *int*  x : Coordonnée X de la cellule
- *int*  y : Coordonnée Y de la cellule
- *bool*  horizontal : Indique si le mur est horizontal

**Renvoie** :  *Wall*  Pointeur vers le mur à la position spécifiée

---

### getStartX()
Retourne la coordonnée X de départ.

**Paramètres** : Aucun

**Renvoie** :  *int*  Coordonnée X de départ

---

### getStartY()
Retourne la coordonnée Y de départ.

**Paramètres** : Aucun

**Renvoie** :  *int*  Coordonnée Y de départ

---

### getEndX()
Retourne la coordonnée X de fin.

**Paramètres** : Aucun

**Renvoie** :  *int*  Coordonnée X de fin

---

### getEndY()
Retourne la coordonnée Y de fin.

**Paramètres** : Aucun

**Renvoie** :  *int*  Coordonnée Y de fin

---

### getStartCell()
Retourne la cellule de départ.

**Paramètres** : Aucun

**Renvoie** :  *Cell*  Pointeur vers la cellule de départ

---

### getEndCell()
Retourne la cellule de fin.

**Paramètres** : Aucun

**Renvoie** :  *Cell*  Pointeur vers la cellule de fin

---

### setWidthHeight( width, height)
Définit la largeur et la hauteur du labyrinthe.

**Paramètres** :
- *int*  width : Largeur du labyrinthe
- *int*  height : Hauteur du labyrinthe

**Renvoie** :  *void*  Aucune valeur de retour

---

### setWidthHeight( width, height, startX, startY, endX, endY)
Définit la largeur, la hauteur, les coordonnées de départ et de fin du labyrinthe.

**Paramètres** :
- *int*  width : Largeur du labyrinthe
- *int*  height : Hauteur du labyrinthe
- *int*  startX : Coordonnée X de départ
- *int*  startY : Coordonnée Y de départ
- *int*  endX : Coordonnée X de fin
- *int*  endY : Coordonnée Y de fin

**Renvoie** :  *void*  Aucune valeur de retour

---

### setCells( cells)
Définit les cellules du labyrinthe.

**Paramètres** :
- *Cell***  cells : Tableau de pointeurs vers les cellules du labyrinthe

**Renvoie** :  *void*  Aucune valeur de retour

---

### setCell( x, y, cell)
Définit une cellule à la position spécifiée.

**Paramètres** :
- *int*  x : Coordonnée X de la cellule
- *int*  y : Coordonnée Y de la cellule
- *Cell*  cell : Pointeur vers la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### generate()
Génère le labyrinthe.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### setStart( x, y)
Définit la position de départ du labyrinthe.

**Paramètres** :
- *int*  x : Coordonnée X de départ
- *int*  y : Coordonnée Y de départ

**Renvoie** :  *void*  Aucune valeur de retour

---

### setEnd( x, y)
Définit la position de fin du labyrinthe.

**Paramètres** :
- *int*  x : Coordonnée X de fin
- *int*  y : Coordonnée Y de fin

**Renvoie** :  *void*  Aucune valeur de retour

---

### addWall( x, y, horizontal)
Ajoute un mur à la position spécifiée.

**Paramètres** :
- *int*  x : Coordonnée X de la cellule
- *int*  y : Coordonnée Y de la cellule
- *bool*  horizontal : Indique si le mur est horizontal

**Renvoie** :  *bool*  Indique si le mur a été ajouté avec succès

---

### addWall( x, y, horizontal, neighborsConnection)
Ajoute un mur à la position spécifiée avec une connexion aux voisins.

**Paramètres** :
- *int*  x : Coordonnée X de la cellule
- *int*  y : Coordonnée Y de la cellule
- *bool*  horizontal : Indique si le mur est horizontal
- *bool*  neighborsConnection : Indique si le mur doit être connecté aux voisins

**Renvoie** :  *bool*  Indique si le mur a été ajouté avec succès

---

### addWall( cell1, cell2)
Ajoute un mur entre deux cellules spécifiées.

**Paramètres** :
- *Cell*  cell1 : Pointeur vers la première cellule
- *Cell*  cell2 : Pointeur vers la deuxième cellule

**Renvoie** :  *bool*  Indique si le mur a été ajouté avec succès

---

### removeWall( x, y, horizontal)
Supprime un mur à la position spécifiée.

**Paramètres** :
- *int*  x : Coordonnée X de la cellule
- *int*  y : Coordonnée Y de la cellule
- *bool*  horizontal : Indique si le mur est horizontal

**Renvoie** :  *bool*  Indique si le mur a été supprimé avec succès

---

### removeWall( x, y, horizontal, neighborsConnection)
Supprime un mur à la position spécifiée avec une connexion aux voisins.

**Paramètres** :
- *int*  x : Coordonnée X de la cellule
- *int*  y : Coordonnée Y de la cellule
- *bool*  horizontal : Indique si le mur est horizontal
- *bool*  neighborsConnection : Indique si le mur doit être connecté aux voisins

**Renvoie** :  *bool*  Indique si le mur a été supprimé avec succès

---

### removeWall( cell1, cell2)
Supprime un mur entre deux cellules spécifiées.

**Paramètres** :
- *Cell*  cell1 : Pointeur vers la première cellule
- *Cell*  cell2 : Pointeur vers la deuxième cellule

**Renvoie** :  *bool*  Indique si le mur a été supprimé avec succès

---

### initNeighborsCells_()
Initialise les voisins des cellules du labyrinthe.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### freeMaze()
Libère la mémoire allouée pour le labyrinthe.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### clearMaze()
Réinitialise le labyrinthe en marquant toutes les cellules comme non visitées et en réinitialisant leur statut.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour
