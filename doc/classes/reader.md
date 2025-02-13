## Classe [`Reader`](../../src/lib/reader.hpp)

### Description

La classe `Reader` est responsable de lire un fichier de configuration de labyrinthe et de remplir un objet `Maze` avec
les données du fichier. Elle gère l'ouverture du fichier, la lecture des données, la vérification des formats, et la
création des murs dans le labyrinthe.

### Fonction principale

#### `void read(const std::string& filename, Maze* maze)`

**Description** :

Lit un fichier de configuration de labyrinthe et remplit un objet `Maze`.

- **Paramètres** :
    - `filename`: Le nom du fichier à lire.
    - `maze`: L'objet `Maze` à remplir.

---

### Détails de la Lecture

La fonction `read` effectue les opérations suivantes :

1. **Ouverture du fichier** :
    - Tente d'ouvrir le fichier spécifié en mode lecture.
    - Si l'ouverture échoue, la fonction sort avec un code d'erreur (`MAZE_FILE_ERROR`).

2. **Lecture des dimensions du labyrinthe** :
    - La première ligne contient la largeur (`width`) et la hauteur (`height`) du labyrinthe.
    - Ces valeurs sont utilisées pour initialiser le labyrinthe via la méthode `setWidhtHeight()`.

3. **Lecture des murs** :
    - Chaque ligne suivante contient une description d'un mur avec :
        - `x`, `y`: Coordonnées du mur.
        - `orientation`: Orientation du mur (`'H'` pour horizontal, `'V'` pour vertical).
    - Pour chaque mur, la fonction vérifie l'orientation. Si l'orientation est invalide, la fonction sort avec
      `MAZE_FILE_ERROR`.
    - Le mur est ajouté au labyrinthe via la méthode `addWall()`. Si l'ajout échoue, la fonction sort avec
      `MAZE_FILE_ERROR`.

---

### Gestion des erreurs

La fonction `read` peut sortir avec le code d'erreur `MAZE_FILE_ERROR` dans les cas suivants :

- Impossible d'ouvrir le fichier.
- Format incorrect de la première ligne (largeur/hauteur).
- Orientation de mur non valide (`'H'` ou `'V'`).
- Erreur lors de l'ajout d'un mur.

---

### Remarques

La fonction `read` ne gère pas l'allocation ou la libération de la mémoire pour la `Maze`. Il est de la responsabilité
de l'utilisateur de s'assurer que le pointeur `maze` pointe vers un objet `Maze` valide avant d'appeler `read`.

La fonction suppose que le fichier est bien formaté et que les coordonnées des murs sont valides. Toute erreur lors de
la lecture ou de la mise en place des murs entraine une sortie immédiate avec `MAZE_FILE_ERROR`.