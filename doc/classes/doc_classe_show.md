# Classe `Show`

---

### Show( maze)
Constructeur de la classe Show.

**Paramètres** :
- *Maze***  maze : Pointeur vers un objet de type Maze

**Renvoie** :  *Show*  Une instance de Show

---

### create()
Crée une fenêtre de rendu.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### destroy()
Détruit la fenêtre de rendu.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### isOpen()
Vérifie si la fenêtre de rendu est ouverte.

**Paramètres** : Aucun

**Renvoie** :  *bool*  true si la fenêtre est ouverte, false sinon

---

### draw()
Dessine la fenêtre de rendu.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### pollEvent( event)
Récupère un événement.

**Paramètres** :
- *sf::Event&*  event : Référence vers un objet de type sf::Event

**Renvoie** :  *bool*  true si un événement a été récupéré, false sinon

---

### eventHandler()
Récupère l'événement de fermeture de la fenêtre.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### clear()
Efface le contenu de la fenêtre de rendu.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### display()
Affiche le contenu de la fenêtre de rendu.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### update()
Met à jour la fenêtre de rendu.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### updateCell( cell)
Met à jour une cellule spécifique.

**Paramètres** :
- *Cell***  cell : Pointeur vers une cellule

**Renvoie** :  *void*  Aucune valeur de retour

---

### keyPress()
Vérifie si une touche a été pressée.

**Paramètres** : Aucun

**Renvoie** :  *bool*  true si une touche a été pressée, false sinon

---

### getLastKeyPressed()
Retourne la dernière touche pressée.

**Paramètres** : Aucun

**Renvoie** :  *sf::Event::KeyEvent*  La dernière touche pressée

---

### close()
Ferme la fenêtre de rendu.

**Paramètres** : Aucun

**Renvoie** :  *void*  Aucune valeur de retour

---

### updateShowLive( show, maze, fastCooling)
Met à jour la fenêtre de rendu avec refroidissement rapide.

**Paramètres** :
- *Show***  show : Pointeur vers un objet de type Show
- *Maze***  maze : Pointeur vers un objet de type Maze
- *bool*  fastCooling : Refroidissement rapide

**Renvoie** :  *void*  Aucune valeur de retour

---

### updateShowLive( show, maze)
Met à jour la fenêtre de rendu.

**Paramètres** :
- *Show***  show : Pointeur vers un objet de type Show
- *Maze***  maze : Pointeur vers un objet de type Maze

**Renvoie** :  *void*  Aucune valeur de retour

---

### updateShowLive( show, maze, argc, argv)
Met à jour la fenêtre de rendu avec des arguments supplémentaires.

**Paramètres** :
- *Show***  show : Pointeur vers un objet de type Show
- *Maze***  maze : Pointeur vers un objet de type Maze
- *int*  argc : Nombre d'arguments
- *Cell***  argv : Tableau de pointeurs vers des objets de type Cell

**Renvoie** :  *void*  Aucune valeur de retour

---

### refreshShow( show)
Rafraîchit la fenêtre de rendu.

**Paramètres** :
- *Show***  show : Pointeur vers un objet de type Show

**Renvoie** :  *void*  Aucune valeur de retour
