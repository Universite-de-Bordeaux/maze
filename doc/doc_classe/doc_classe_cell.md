# Classe `Cell`

---

### Cell()
Constructeur par défaut de la classe Cell.

**Paramètres** : Aucun

**Renvoie** :  *Cell*  Une instance de Cell

---

### Cell( x, y)
Constructeur de la classe Cell.

**Paramètres** :
- *int*  x : Coordonnée x de la cellule
- *int*  y : Coordonnée y de la cellule

**Renvoie** :  *Cell*  Une instance de Cell

---

### Cell( x, y, width, height)
Constructeur de la classe Cell.

**Paramètres** :
- *int*  x : Coordonnée x de la cellule
- *int*  y : Coordonnée y de la cellule
- *int*  width : Largeur du labyrinthe
- *int*  height : Hauteur du labyrinthe

**Renvoie** :  *Cell*  Une instance de Cell

---

### ~Cell()
Destructeur de la classe Cell.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### getX()
Récupère la coordonnée x de la cellule.

**Paramètres** : Aucun

**Renvoie** :  *int*  La coordonnée x de la cellule

---

### getY()
Récupère la coordonnée y de la cellule.

**Paramètres** : Aucun

**Renvoie** :  *int*  La coordonnée y de la cellule

---

### getNeighbors()
Récupère les voisins de la cellule.

**Paramètres** : Aucun

**Renvoie** :  *Cell***  Les voisins de la cellule

---

### getNeighbor( i)
Récupère un voisin de la cellule.

**Paramètres** :
- *int*  i : Voisin à récupérer

**Renvoie** :  *Cell*  Le voisin de la cellule

---

### getRelativeNeighbor( i)
Récupère un voisin relatif de la cellule.

**Paramètres** :
- *int*  i : Voisin relatif à récupérer

**Renvoie** :  *Cell*  Le voisin relatif de la cellule

---

### getWalls()
Récupère les murs de la cellule.

**Paramètres** : Aucun

**Renvoie** :  *Wall***  Les murs de la cellule

---

### getWall( i)
Récupère un mur de la cellule.

**Paramètres** :
- *int*  i : Mur à récupérer

**Renvoie** :  *Wall*  Le mur de la cellule

---

### isWall( i)
Récupère si la cellule a un mur.

**Paramètres** :
- *int*  i : Emplacement du mur à vérifier

**Renvoie** :  *bool*  Vrai si la cellule a un mur à l'emplacement donné

---

### isAlreadyVisited()
Récupère si la cellule a déjà été visitée.

**Paramètres** : Aucun

**Renvoie** :  *bool*  Vrai si la cellule a déjà été visitée

---

### getAbsoluteNumberOfNeighbors()
Récupère le nombre de voisins de la cellule.

**Paramètres** : Aucun

**Renvoie** :  *int*  Le nombre de voisins de la cellule

---

### getAbsoluteNeighbors( neighbors)
Récupère les voisins de la cellule qui n'ont pas encore été visités.

**Paramètres** :
- *Cell***  neighbors : Tableau de cellules dans lesquelles stocker les voisins

**Renvoie** :  *void*  Aucune valeur de retour

---

### getAbsoluteNumberOfNeighborsNotVisited()
Récupère le nombre de voisins de la cellule qui n'ont pas encore été visités.

**Paramètres** : Aucun

**Renvoie** :  *int*  Le nombre de voisins de la cellule qui n'ont pas encore été visités

---

### getAbsoluteNeighborsNotVisited( neighbors)
Récupère les voisins de la cellule qui n'ont pas encore été visités.

**Paramètres** :
- *Cell***  neighbors : Tableau de cellules dans lesquelles stocker les voisins

**Renvoie** :  *void*  Aucune valeur de retour

---

### getRelativeNumberOfNeighborsNotVisited()
Récupère le nombre de voisins relatifs de la cellule qui n'ont pas encore été visités.

**Paramètres** : Aucun

**Renvoie** :  *int*  Le nombre de voisins relatifs de la cellule qui n'ont pas encore été visités

---

### getRelativeNeighborsNotVisited( neighbors)
Récupère les voisins relatifs de la cellule qui n'ont pas encore été visités.

**Paramètres** :
- *Cell***  neighbors : Tableau de cellules relatives dans lequel stocker les voisins

**Renvoie** :  *void*  Aucune valeur de retour

---

### getStatus()
Récupère le statut de la cellule.

**Paramètres** : Aucun

**Renvoie** :  *int*  Le statut de la cellule

---

### isNeighbor( i)
Récupère si la cellule est un voisin.

**Paramètres** :
- *int*  i : Voisin à vérifier

**Renvoie** :  *bool*  Vrai si la cellule est un voisin

---

### isRelativeNeighbor( i)
Récupère si la cellule est un voisin relatif.

**Paramètres** :
- *int*  i : Voisin relatif à vérifier

**Renvoie** :  *bool*  Vrai si la cellule est un voisin relatif

---

### setX( x)
Définit la coordonnée x de la cellule.

**Paramètres** :
- *int*  x : Nouvelle coordonnée x de la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### setY( y)
Définit la coordonnée y de la cellule.

**Paramètres** :
- *int*  y : Nouvelle coordonnée y de la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### setXY( x, y)
Définit les coordonnées de la cellule.

**Paramètres** :
- *int*  x : Nouvelle coordonnée x de la cellule
- *int*  y : Nouvelle coordonnée y de la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### setNeighbors( neighbors)
Définit les voisins de la cellule.

**Paramètres** :
- *Cell***  neighbors : Nouveaux voisins de la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### setNeighbor( i, neighbor)
Définit un voisin de la cellule.

**Paramètres** :
- *int*  i : Voisin à définir
- *Cell*  neighbor : Nouveau voisin de la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### setWalls( walls)
Définit les murs de la cellule.

**Paramètres** :
- *Wall***  walls : Nouveaux murs de la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### setWall( i, wall)
Définit un mur de la cellule.

**Paramètres** :
- *int*  i : Mur à définir
- *Wall*  wall : Nouveau mur de la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### setAlreadyVisited( alreadyVisited)
Définit si la cellule a déjà été visitée.

**Paramètres** :
- *bool*  alreadyVisited : Vrai si la cellule a déjà été visitée

**Renvoie** :  *void*  Aucune valeur de retour

---

### setStatus( status)
Définit le statut de la cellule.

**Paramètres** :
- *int*  status : Nouveau statut de la cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### freeWall( i)
Supprime un mur de la cellule.

**Paramètres** :
- *int*  i : Mur à supprimer

**Renvoie** :  *void*  Aucune valeur de retour

---

### freeWalls()
Supprime les murs de la cellule.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour
