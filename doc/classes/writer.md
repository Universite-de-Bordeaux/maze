## Classe [`Writer`](../../src/lib/writer.hpp)

### Description

La classe `Writer` est une utilitaire conçue pour sauvegarder un labyrinthe dans un fichier texte. Elle enregistre les
informations du labyrinthe, y compris ses dimensions et les positions des murs, conformément à un format spécifié. Cela
permet de stocker temporairement ou permanent le labyrinthe pour une utilisation ultérieure ou pour affichage.

### Fonction Principale

#### `void write(const Maze *maze, const char *filename)`

**Description** :

Sauvegarde un labyrinthe dans un fichier.

- **Paramètres** :
    - `maze`: Pointeur vers l'objet `Maze` à sauvegarder.
    - `filename`: Chemin relatif du fichier où écrire le labyrinthe.

### Détails de l'écriture

La fonction `write` effectue les opérations suivantes :

1. **Ouverture du fichier** :
    - Tente d'ouvrir le fichier spécifié en mode écriture. Si le fichier existe, son contenu est écrasé.

2. **Écriture des dimensions** :
    - La première ligne contient la largeur (`width`) et la hauteur (`height`) du labyrinthe.

3. **Écriture des murs** :
    - Parcourt chaque cellule du labyrinthe.
    - Pour chaque cellule, si un mur droit (vertical) ou bas (horizontal) existe, il écrit une ligne dans le fichier
      avec les coordonnées `(x, y)` et l'orientation du mur (`'V'` pour vertical, `'H'` pour horizontal).

### Remarques

- **Format du Fichier** :
    - La première ligne contient `width` et `height`, représentant la taille du labyrinthe.
    - Les autres lignes contiennent `x y orientation`, oú `orientation` est `'V'` pour un mur vertical ou `'H'` pour un
      mur horizontal.

- **Troncature du Fichier** :
    - Si un fichier existe déjà sous le nom spécifié, son contenu est écrasé.

- **Manque de Validation** :
    - Assurez-vous que le pointeur `maze` pointe vers un objet `Maze` valide avant d'appeler `write`.
    - Aucune gestion d'erreur n'est implémentée pour les problèmes de lecture/écriture de fichiers.