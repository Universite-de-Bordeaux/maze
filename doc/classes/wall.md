# Classe [`Wall`](../../src/lib/wall.hpp)

## Description

La classe `Wall` représente un mur dans un labyrinthe. Elle contient des informations sur son orientation et son statut
de visite. Cette classe est utilisée pour définir les obstacles et les limites dans le labyrinthe.

## Constructeurs

### `Wall()`

**Description**:

Constructeur par défaut. Initialise un mur avec des valeurs par défaut (horizontal et non visité).

### `Wall(bool horizontal)`

**Description**:

Constructeur qui initialise un mur avec une orientation spécifique.

- **Paramètres**:
    - `horizontal`: Valeur booléenne indiquant si le mur est horizontal.

### `~Wall()`

**Description**:

Destructeur par défaut. Ne nécessite pas de libération de ressources, car il ne gère pas de pointeurs.

---

## Méthodes

### **Accesseurs**

#### `bool getIsHorizontal() const`

- **Description** : Retourne si le mur est horizontal.
- **Retour** : Valeur booléenne indiquant si le mur est horizontal.

#### `bool isAlreadyVisited() const`

- **Description** : Vérifie si le mur a déjà été visité.
- **Retour** : Valeur booléenne indiquant si le mur a déjà été visité.

---

### **Modificateurs**

#### `void setIsHorizontal(bool horizontal)`

- **Description** : Définit si le mur est horizontal.
- **Paramètres**:
    - `horizontal`: Valeur booléenne pour définir l'orientation du mur.

#### `void setAlreadyVisited(bool visited)`

- **Description** : Définit si le mur a déjà été visité.
- **Paramètres**:
    - `visited`: Valeur booléenne pour indiquer si le mur a été visité.