# Classe [`Rand`](../../src/lib/rand.hpp)

## Description

La classe `Rand` sert à générer des nombres aléatoires en utilisant l'algorithme Mersenne Twister via `std::mt19937`.
Cela permet de créer un générateur de nombres aléatoires fiable et performant pour une variété d'applications, allant
des sélections aléatoires simples aux simulations probabilistes complexes.

## Constructeurs

### `Rand()`

**Description** :

Constructeur par défaut. Initialise le générateur de nombres aléatoires `rng_` avec une semence générée par
`std::random_device`, garantissant une séquence différente à chaque exécution du programme.

---

## Méthodes

### **Générateurs de nombres aléatoires**

#### `int get(int min, int max)`

- **Description** : Génère un nombre entier aléatoire dans la plage [min, max].
- **Paramètres** :
    - `min` : Valeur minimale du nombre généré.
    - `max` : Valeur maximale du nombre généré.
- **Retour** : Un nombre entier dans la plage [min, max].

#### `double get(double min, double max)`

- **Description** : Génère un nombre à virgule fixe aléatoire dans la plage [min, max].
- **Paramètres** :
    - `min` : Valeur minimale du nombre généré.
    - `max` : Valeur maximale du nombre généré.
- **Retour** : Un nombre flottant dans la plage [min, max].

#### `bool get(double probability)`

- **Description** : Retourne `true` avec la probabilité spécifiée.
- **Paramètres** :
    - `probability` : Probabilité (de 0.0 à 1.0) de retourner `true`.
- **Retour** : `true` si le nombre aléatoire est inférieur à la probabilité donnée, sinon `false`.

#### `int get()`

- **Description** : Génère un nombre entier aléatoire dans la plage [0, RAND_MAX], où RAND_MAX est une constante définie
  dans `<cstdlib>`.
- **Paramètres** : Aucun.
- **Retour** : Un nombre entier dans la plage [0, RAND_MAX].

---

## Membres Privés

### `std::mt19937 rng_`

- **Description** : Un générateur de nombres aléatoires de type Mersenne Twister, connu pour ses bonnes propriétés
  statistiques et sa performance.