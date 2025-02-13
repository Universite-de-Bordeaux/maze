# Classe [`Show`](../../src/lib/show.hpp)

## Description

La classe `Show` gere l'affichage d'un labyrinthe à l'aide de la bibliothèque SFML. Elle permet de créer une fenêtre de
rendu, de dessiner les cellules et les murs, et de gérer les événements utilisateur tels que le déplacement et le zoom.

## Constructeurs

### `explicit Show(Maze *maze)`

**Description** :  
Constructeur de la classe `Show`. Initialise un pointeur vers un labyrinthe et configure les couleurs par défaut.

**Paramètres** :

- `maze`: Pointeur vers un objet `Maze` contenant le labyrinthe à afficher.

**Remarques** :  
Charge les couleurs depuis le fichier .env si disponible, sinon utilise les valeurs par défaut.

---

## Méthodes

### **Accesseurs**

#### `bool isOpen() const`

- **Description** : Vérifie si la fenêtre de rendu est ouverte.
- **Retour** : `true` si la fenêtre est ouverte, `false` sinon.

#### `bool mazeIsEmpty() const`

- **Description** : Vérifie si le labyrinthe est vide.
- **Retour** : `true` si le labyrinthe est vide, `false` sinon.

#### `sf::Event::KeyEvent getLastKeyPressed() const`

- **Description** : Récupère la dernière touche pressée par l'utilisateur.
- **Retour** : Objet `sf::Event::KeyEvent` contenant les informations sur la dernière touche pressée.

#### `bool getLowFreq() const`

- **Description** : Récupère l'état de la fréquence basse de rafraîchissement.
- **Retour** : `true` si le rafraîchissement est en mode basse fréquence, `false` sinon.

---

### **Modificateurs**

#### `void create()`

- **Description** : Crée une fenêtre de rendu SFML. Calcule la taille de la fenêtre en fonction des dimensions du
  labyrinthe et du ratio maximal autorisé.
- **Retour** : Aucun.

#### `void destroy()`

- **Description** : Détruit la fenêtre de rendu SFML.
- **Retour** : Aucun.

#### `void close() const`

- **Description** : Ferme la fenêtre de rendu SFML.
- **Retour** : Aucun.

#### `void eventHandler()`

- **Description** : Gère les événements de la fenêtre (fermeture, déplacement de la souris, clics, événements clavier,
  etc.).
- **Retour** : Aucun.

#### `void clearBlack() const`

- **Description** : Efface le contenu de la fenêtre de rendu en noir.
- **Retour** : Aucun.

#### `void refreshDisplay()`

- **Description** : Affiche le contenu de la fenêtre de rendu. Prend en compte le délai et le taux de rafraîchissement
  configurés.
- **Retour** : Aucun.

#### `void refreshMaze()`

- **Description** : Rafraîchit entièrement le labyrinthe (toutes les cellules).
- **Retour** : Aucun.

#### `void drawCell(const Cell *cell) const`

- **Description** : Dessine une cellule spécifique, y compris ses murs et son statut.
- **Paramètres** :
    - `cell`: Pointeur vers la cellule à dessiner.
- **Retour** : Aucun.

#### `void setRefreshRate(unsigned int rate)`

- **Description** : Met à jour le taux de rafraîchissement (en_hz).
- **Paramètres** :
    - `rate`: Taux de rafraîchissement souhaité.
- **Retour** : Aucun.

#### `void setLowFreq(const bool lowFreq)`

- **Description** : active/désactive le mode basse fréquence de rafraîchissement.
- **Paramètres** :
    - `lowFreq`: `true` pour activer le mode basse fréquence, `false` sinon.
- **Retour** : Aucun.

#### `void setDelay(float delay)`

- **Description** : Met à jour le délai de rafraîchissement (en millisecondes).
- **Paramètres** :
    - `delay`: Délai souhaité.
- **Retour** : Aucun.

---

## Membres Privés

### `Maze *maze_`

- **Description** : Pointeur vers le labyrinthe à afficher.

### `sf::RenderWindow *renderWindow_`

- **Description** : Pointeur vers la fenêtre de rendu SFML. `nullptr` si la fenêtre n'a pas été créée.

### `float cellSize_`

- **Description** : Taille d'une cellule du labyrinthe en pixels.

### `bool lowFreq_`

- **Description** : État du mode basse fréquence de rafraîchissement.

### `sf::Font font_`

- **Description** : Police d'écriture utilisée pour les éléments textuels.

### `sf::Event::KeyEvent lastKeyPressed_`

- **Description** : Dernière touche pressée par l'utilisateur.

### `std::chrono::milliseconds refreshRate_`

- **Description** : Taux de rafraîchissement de la fenêtre (en millisecondes).

### `std::chrono::microseconds delay_`

- **Description** : Délai de rafraîchissement (en microsecondes).

### `std::chrono::high_resolution_clock::time_point lastDisplay_`

- **Description** : Horodatage de la dernière mise à jour de l'affichage.

### `float zoomLevel_`

- **Description** : Niveau de zoom appliqué à la vue.

### `bool isDragging_`

- **Description** : Indique si l'utilisateur est en train de déplacer la vue avec la souris.

### `sf::Vector2i lastMousePosition_`

- **Description** : Dernière position de la souris dans la fenêtre.

### `sf::Vector2f lastViewCenter_`

- **Description** : Centre de la vue dans la fenêtre.

### `struct colorConfig_`

- **Description** : Structure contenant les couleurs utilisées pour afficher entraîneurs de cellules et murs. Les champs
  incluent :
    - `wall`: Couleur des murs normaux.
    - `wallStart`: Couleur du mur de départ.
    - `wallEnd`: Couleur du mur d'arrivée.
    - `idle`: Couleur des cellules non visitées.
    - `visited`: Couleur des cellules visitées.
    - `hopeless`: Couleur des cellules sans solution.
    - `tooManyNeighbors`: Couleur des cellules avec trop de voisins.
    - `wayOut`: Couleur du chemin de sortie.
    - `current`: Couleur de la cellule courante.

---

## Fonctions statiques

### `void refreshShow(Show *show, int argc, Cell *argv[])`

- **Description** : Rafraîchit la fenêtre de rendu avec les cellules modifiées. Si `lowFreq` est actif, ne rafraîchit
  que les cellules spécifiées, sinon rafraîchit toutes les cellules.
- **Paramètres** :
    - `show`: Pointeur vers un objet `Show`.
    - `argc`: Nombre de cellules à rafraîchir.
    - `argv[]`: Tableau de pointeurs vers les cellules à rafraîchir.

---

### `void refreshShow(Show *show, int argc, Cell *argv[], bool lowFreq)`

- **Description** : Rafraîchit la fenêtre de rendu avec les cellules modifiées. Si `lowFreq` est `true`, ne rafraîchit
  que les cellules spécifiées, sinon rafraîchit toutes les cellules.
- **Paramètres** :
    - `show`: Pointeur vers un objet `Show`.
    - `argc`: Nombre de cellules à rafraîchir.
    - `argv[]`: Tableau de pointeurs vers les cellules à rafraîchir.
    - `lowFreq`: Indique si le rafraîchissement doit être limité aux cellules spécifiées.

---

## Gestion des Événements

La classe `Show` gère les événements suivants :

- Fermeture de la fenêtre.
- Déplacement de la souris pour le déplacement de la vue.
- Clics de souris pour le début et la fin du déplacement.
- Événements clavier pour contrôler le zoom, le déplacement et le rafraîchissement.

---

## Configuration

La configuration par défaut peut être modifiée via le fichier .env dans le répertoire de travail. Les paramètres
incluent :

- `FRAMERATE`: Taux de rafraîchissement de la fenêtre (en Hz).
- `DELAY_SHOW`: Délai de rafraîchissement (en secondes).
- `LOW_FREQUENCY`: Activer/désactiver le mode basse fréquence (`true` ou `false`).

Les couleurs peuvent également être configurées dans le fichier .env en spécifiant les valeurs RGB pour différentes
parties du labyrinthe.

---

## Erreurs

La classe `Show` peut retourner le code d'erreur suivant :

- `MAZE_GRAPHIC_ERROR`: En cas d'erreur lors de la configuration du taux de rafraîchissement ou du délai.

---

## Initialisation et Nettoyage

La méthode `create()` initialise la fenêtre de rendu et configure les paramètres par défaut. La méthode `destroy()`
libère les ressources associées à la fenêtre.

---

## Affichage

### Dessin des Cellules

La méthode `drawCell()` dessine une cellule en fonction de son statut (non visitée, visitée, chemin, etc.) et de ses
murs. Les murs sont dessinés en fonction de leur orientation (horizontal ou vertical).

### Dessin des Murs

Les murs sont dessinés avec des couleurs spécifiques s'ils marquent le début ou la fin du labyrinthe. Les frontières du
labyrinthe sont également dessinées en fonction de l'orientation.

### Zoom et Déplacement

L'utilisateur peut zoomer/dézoomer sur le labyrinthe avec la roulette de la souris et déplacer la vue en tenant clic
gauche et en déplaçant la souris.