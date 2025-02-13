# Classe [`Queue`](../../src/lib/queue.hpp)

## Description

La classe `Queue` représente une file qui permet d'ajouter et de retirer des éléments de manière efficace.
Elle utilise un tableau dynamique pour stocker les éléments et gère automatiquement le redimensionnement du tableau
lorsque nécessaire.

## Constructeurs

### `Queue()`

**Description**:

Constructeur par défaut. Initialise une file vide avec une taille de 0 et une capacité initiale de 1.

### `~Queue()`

**Description**:

Destructeur. Libère la mémoire allouée pour le tableau des éléments.

---

## Méthodes

### **Accesseurs**

#### `void *front() const`

- **Description** : Récupère le premier élément de la file.
- **Retour** : Un pointeur vers le premier élément de la file ou `nullptr` si la file est vide.

#### `bool empty() const`

- **Description** : Vérifie si la file est vide.
- **Retour** : `true` si la file est vide, `false` sinon.

---

### **Modificateurs**

#### `void push(void *data)`

- **Description** : Ajoute un élément à la fin de la file.
- **Paramètres** :
    - `data`: Pointeur vers l'objet à ajouter à la file.

#### `void pop()`

- **Description** : Retire le premier élément de la file.
- **Retour** : Aucun retour, mais libère l'espace mémoire si nécessaire.

---

## Membres Privés

### `void **data`

- **Description** : Tableau dynamique contenant les éléments de la file.

### `int size_`

- **Description** : Nombre d'éléments actuellement présents dans la file.

### `int capacity_`

- **Description** : Capacité actuelle du tableau (nombre d'éléments pouvant être stockés sans redimensionnement).

---

## Gestion de la File

La file gère dynamiquement sa taille en doublant sa capacité lorsque l'espace est épuisé et en réduisant sa capacité de
moitié lorsque la taille est inférieure à un quart de la capacité actuelle. Cela permet de maintenir un bon équilibre
entre l'espace mémoire utilisé et les performances.