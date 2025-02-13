# Classe [`Stack`](../../src/lib/stack.hpp)

## Description

La classe `Stack` représente une pile dynamique qui utilise un tableau pour stocker et gérer les éléments. Elle supporte
les opérations de push (ajout d'un élément), pop (retirer le dernier élément ajouté), top (accès au dernier élément
ajouté), et vérifie si la pile est vide. Cette classe est implémentée avec un tableau dynamique qui s'agrandit ou
rétrécit selon les besoins, pour maintenir un bon équilibre entre l'espace mémoire utilisé et les performances.

## Constructeurs

### `Stack()`

**Description**:

Constructeur par défaut. Initialise une pile vide avec une taille de 0 et une capacité initiale de 1.

### `~Stack()`

**Description**:

Destructeur. Libère la mémoire allouée pour le tableau des éléments.

---

## Méthodes

### **Accesseurs**

#### `void *top() const`

- **Description** : Retourne le dernier élément ajouté à la pile (élément au sommet).
- **Retour** : Un pointeur vers le dernier élément ajouté ou `nullptr` si la pile est vide.

#### `bool empty() const`

- **Description** : Vérifie si la pile est vide.
- **Retour** : `true` si la pile est vide, `false` sinon.

---

### **Modificateurs**

#### `void push(void *data)`

- **Description** : Ajoute un élément au sommet de la pile.
- **Paramètres** :
    - `data`: Pointeur vers l'objet à ajouter à la pile.

#### `void pop()`

- **Description** : Retire le dernier élément ajouté à la pile (éléments au sommet).
- **Paramètres** : Aucun.
- **Retour** : Aucun, mais libère l'espace mémoire si nécessaire.

---

## Membres Privés

### `int size_`

- **Description** : Nombre d'éléments actuellement présents dans la pile.

### `int capacity_`

- **Description** : Capacité actuelle du tableau (nombre d'éléments pouvant être stockés sans redimensionnement).

### `void **data`

- **Description** : Tableau dynamique contenant les éléments de la pile.

---

## Gestion de la Pile

La pile gestion dynamiquement sa taille en doublant sa capacité lorsque l'espace est épuisé et en réduisant sa capacité
de moitié lorsque la taille est inférieure à un quart de la capacité actuelle. Cela permet de maintenir un bon équilibre
entre l'espace mémoire utilisé et les performances, en évitant les redimensionnements fréquents trop coûteux.