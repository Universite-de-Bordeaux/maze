# Classe `Wall`

---

### Wall()
Constructeur par défaut de la classe Wall.

**Paramètres** : Aucun

**Renvoie** :  *Wall*  Une instance de Wall

---

### Wall( horizontal)
Constructeur de la classe Wall.

**Paramètres** :
- *bool*  horizontal : Booléen indiquant si le mur est horizontal

**Renvoie** :  *Wall*  Une instance de Wall

---

### ~Wall()
Destructeur de la classe Wall.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### getIsHorizontal()
Retourne si le mur est horizontal.

**Paramètres** : Aucun

**Renvoie** :  *bool*  Booléen indiquant si le mur est horizontal

---

### getNeighbors()
Retourne les voisins du mur.

**Paramètres** : Aucun

**Renvoie** :  *Wall***  Tableau de pointeurs sur les voisins du mur

---

### getNeighbor( i)
Retourne un voisin du mur.

**Paramètres** :
- *int*  i : Voisin à retourner

**Renvoie** :  *Wall*  Pointeur sur le voisin demandé

---

### isAlreadyVisited()
Retourne si le mur a déjà été visité.

**Paramètres** : Aucun

**Renvoie** :  *bool*  Booléen indiquant si le mur a déjà été visité

---

### isBorder()
Retourne si le mur est une bordure.

**Paramètres** : Aucun

**Renvoie** :  *bool*  Booléen indiquant si le mur est une bordure

---

### setIsHorizontal( horizontal)
Définit si le mur est horizontal.

**Paramètres** :
- *bool*  horizontal : Booléen indiquant si le mur est horizontal

**Renvoie** :  *void*  Aucune valeur de retour

---

### setNeighbors( neighbors)
Définit les voisins du mur.

**Paramètres** :
- *Wall***  neighbors : Tableau de pointeurs sur les voisins du mur

**Renvoie** :  *void*  Aucune valeur de retour
