#ifndef SHOW_HPP
#define SHOW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <chrono>

#include "maze.hpp"

class Show {
   public:
    /**
     * @brief Constructeur de la classe Show
     * @param maze Pointeur vers un objet de type Maze
     */
    explicit Show(Maze *maze);
    /**
     * @brief Crée une fenêtre de rendu
     */
    void create();
    /**
     * @brief Détruit la fenêtre de rendu
     */
    void destroy();
    /**
     * @brief Vérifie si la fenêtre de rendu est ouverte
     * @return True si la fenêtre de rendu est ouverte, false sinon
     */
    bool isOpen() const;
    /**
     * @brief Gère les événements de la fenêtre de rendu
     */
    void eventHandler() const;
    /**
     * @brief Récupère un événement
     * @param event Référence vers un event
     * @return True si un événement a été récupéré, false sinon
     */
    bool pollEvent(sf::Event &event) const;
    /**
     * @brief Efface le contenu de la fenêtre de rendu
     */
    void clearBlack() const;
    /**
     * @brief Affiche le contenu de la fenêtre de rendu
     */
    void refreshDisplay();
    /**
     * @brief Rafraîchit l'ensemble du labyrinthe
     */
    void refreshMaze();
    /**
     * @brief Met à jour une cellule
     * @param cell Pointeur vers un objet de type Cell
     */
    void drawCell(const Cell *cell) const;

    /**
     * @brief Gère les événements de la fenêtre de rendu
     * @return True si une touche a été pressée, false sinon
     */
    bool keyPress();
    /**
     * @brief Récupère la dernière touche pressée
     * @return Dernière touche pressée
     */
    sf::Event::KeyEvent getLastKeyPressed() const;

    /**
     * @brief Ferme la fenêtre de rendu
     */
    void close() const;
    /**
     * @brief Vérifie si le labyrinthe est vide
     * @return True si le labyrinthe est vide, false sinon
     */
    bool mazeIsEmpty() const;
    /**
     * @brief Met à jour le taux de rafraîchissement
     * @param rate Taux de rafraîchissement
     */
    void setRefreshRate(unsigned int rate);
    /**
     * @brief Met à jour le délai
     * @param delay Délai en millisecondes
     */
    void setDelay(unsigned int delay);

   private:
    Maze *maze_;  //> Pointeur vers un objet de type Maze
    sf::RenderWindow *renderWindow_ =
        nullptr;      //> Pointeur vers un objet de type sf::RenderWindow
    float cellSize_;  //> Taille d'une cellule
    sf::Font font_;   //> Police d'écriture
    sf::Event::KeyEvent lastKeyPressed_{};   //> Dernière touche pressée
    std::chrono::milliseconds refreshRate_;  //> Taux de rafraîchissement
    std::chrono::milliseconds delay_;        //> Délai
    std::chrono::high_resolution_clock::time_point
        lastDisplay_;  //> Dernier affichage

    /**
     * @brief Dessine toutes les cellules du labyrinthe
     */
    void drawCells_() const;
    /**
     * @brief Dessine une cellule
     * @param cell Pointeur vers un objet de type Cell
     */
    void drawCell_(const Cell *cell) const;
    /**
     * @brief Dessine un mur
     * @param cell Pointeur vers un objet de type Cell
     * @param orientation Orientation du mur
     */
    void drawWall_(const Cell *cell, int orientation) const;
    /**
     * @brief Dessine une frontière
     * @param cell Pointeur vers un objet de type Cell
     * @param orientation Orientation de la frontière
     */
    void drawFrontier_(const Cell *cell, int orientation) const;
};

// /**
//  * @brief Met à jour la fenêtre de rendu
//  * @param show Pointeur vers un objet de type Show
//  * @param maze Pointeur vers un objet de type Maze
//  * @param fastCooling Refroidissement rapide
//  * @return void
//  */
// void updateShowLive(const Show *show, const Maze *maze, bool fastCooling);
// /**
//  * @brief Met à jour la fenêtre de rendu
//  * @param show Pointeur vers un objet de type Show
//  * @param maze Pointeur vers un objet de type Maze
//  * @return void
//  */
// void updateShowLive(const Show *show, const Maze *maze);
/**
 * @brief Rafraîchit la fenêtre de rendu avec seulement les cellules modifiées
 * @param show Pointeur vers un objet de type Show
 * @param argc Nombre d'arguments
 * @param argv Tableau de pointeurs vers des objets de type Cell
 * @return void
 */
void refreshShow(Show *show, int argc, Cell *argv[]);
/**
 * @brief Rafraîchit la fenêtre de rendu avec toutes les cellules
 * @param show Pointeur vers un objet de type Show
 * @return void
 */
void refreshShow(Show *show);

#endif  // SHOW_HPP
