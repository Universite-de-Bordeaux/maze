#ifndef SHOW_HPP
#define SHOW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <chrono>

#include "maze.hpp"
#include "queue.hpp"

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
    void eventHandler();
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
    void setDelay(float delay);
    /**
     * @brief Met à jour lowFreq_ qui détermine si le rafraîchissement doit se
     * faire à basse fréquence ou non
     * @param lowFreq Précise si le rafraîchissement doit se faire à basse
     * fréquence
     */
    void setLowFreq(const bool lowFreq) { lowFreq_ = lowFreq; }
    /**
     * @brief Récupère lowFreq_
     * @return lowFreq_
     */
    bool getLowFreq() const { return lowFreq_; }

   private:
    Maze *maze_;  //> Pointeur vers un objet de type Maze
    sf::RenderWindow *renderWindow_ =
        nullptr;       //> Pointeur vers un objet de type sf::RenderWindow
    float cellSize_;   //> Taille d'une cellule
    bool lowFreq_{};   //> Fréquence basse
    sf::Font font_{};  //> Police d'écriture
    sf::Event::KeyEvent lastKeyPressed_{};     //> Dernière touche pressée
    std::chrono::milliseconds refreshRate_{};  //> Taux de rafraîchissement
    std::chrono::microseconds delay_{};        //> Délai
    std::chrono::high_resolution_clock::time_point
        lastDisplay_;    //> Dernier affichage
    float zoomLevel_{};  //> Niveau de zoom
    bool
        isDragging_{};  //> Précise si l'utilisateur est en train de drag la vue
    sf::Vector2i lastMousePosition_{};  //> Dernière position de la souris
    sf::Vector2f lastViewCenter_{};     //> Dernier centre de la vue
    struct colorConfig_ {
        sf::Color wall{};
        sf::Color wallStart{};
        sf::Color wallEnd{};
        sf::Color idle{};
        sf::Color visited{};
        sf::Color hopeless{};
        sf::Color tooManyNeighbors{};
        sf::Color wayOut{};
        sf::Color current{};
    } colorConfig_{};  //> Configuration des couleurs

    /**
     * @brief Dessine une cellule
     * @param cell Pointeur vers un objet de type Cell
     */
    void drawCell_(const Cell *cell) const;
    /**
     * @brief Dessine toutes les cellules du labyrinthe
     */
    void drawCells_() const;
    /**
     * @brief Dessine une frontière
     * @param cell Pointeur vers un objet de type Cell
     * @param orientation Orientation de la frontière
     */
    void drawFrontier_(const Cell *cell, int orientation) const;
    /**
     * @brief Dessine un mur
     * @param cell Pointeur vers un objet de type Cell
     * @param orientation Orientation du mur
     */
    void drawWall_(const Cell *cell, int orientation) const;
    /**
     * @brief Réinitialise les valeurs en utilisant les valeurs par défaut
     */
    void resetValues();
    /**
     * @brief Charge les couleurs à partir du fichier .env
     * @param key Clé
     * @param color Couleur
     */
    void loadColorsFromEnv_(const std::string &key, sf::Color &color);
    /**
     * @brief Divise une chaîne de caractères en tokens
     * @param str Chaîne de caractères
     * @param delimiter Délimiteur
     * @return Queue de tokens
     */
    Queue splitString_(const std::string &str, char delimiter);
};

/**
 * @brief Rafraîchit la fenêtre de rendu avec seulement les cellules
 * modifiées
 * @param show Pointeur vers un objet de type Show
 * @param argc Nombre d'arguments
 * @param argv Tableau de pointeurs vers des objets de type Cell
 * @return void
 */
void refreshShow(Show *show, int argc, Cell *argv[]);
/**
 * @brief Rafraîchit la fenêtre de rendu avec seulement les cellules
 * modifiées à haute fréquence et toutes les cellules à basse fréquence
 * @param show Pointeur vers un objet de type Show
 * @param argc Nombre d'arguments
 * @param argv Tableau de pointeurs vers des objets de type Cell
 * @param lowFreq Précise si le rafraîchissement doit se faire à basse
 * fréquence
 * @return void
 */
void refreshShow(Show *show, int argc, Cell *argv[], bool lowFreq);
/**
 * @brief Rafraîchit la fenêtre de rendu avec toutes les cellules
 * @param show Pointeur vers un objet de type Show
 * @return void
 */
void refreshShow(Show *show);

#endif  // SHOW_HPP
