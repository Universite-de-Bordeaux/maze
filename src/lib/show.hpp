#ifndef SHOW_HPP
#define SHOW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "maze.hpp"

class Show {
public:
    /**
     * @brief Constructeur de la classe Show
     * @param maze Pointeur vers un objet de type Maze
     */
    Show(Maze* maze);
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
     * @return true si la fenêtre est ouverte, false sinon
     */
    bool isOpen();
    /**
     * @brief Dessine la fenêtre de rendu
     */
    void draw();
    /**
     * @brief Récupère un événement
     * @param event Référence vers un objet de type sf::Event
     * @return true si un événement a été récupéré, false sinon
     */
    bool pollEvent(sf::Event&);
    /**
     * @brief Récupère l'événement de fermeture de la fenêtre
     * @return true si l'événement de fermeture a été récupéré, false sinon
     */
    void eventHandler();
    /**
     * @brief Efface le contenu de la fenêtre de rendu
     */
    void clear();
    /**
     * @brief Affiche le contenu de la fenêtre de rendu
     */
    void display();
    /**
     * @brief Met à jour la fenêtre de rendu
     */
    void update();
    void updateCell(Cell*);

private:
    Maze* maze_; //> Pointeur vers un objet de type Maze
    sf::RenderWindow* renderWindow_ = nullptr; //> Pointeur vers un objet de type sf::RenderWindow
    int cellSize_; //> Taille d'une cellule
    sf::Font font_; //> Police d'écriture

    /**
     * @brief Gère les événements de la fenêtre de rendu
     * @param event Référence vers un objet de type sf::Event
     */
    void eventHandler_(sf::Event&);
};

void updateShowLive(Show*, Maze*, bool);
void updateShowLive(Show*, Maze*);
void updateShowLive(Show*, Maze*, int, Cell**);

#endif  // SHOW_HPP
