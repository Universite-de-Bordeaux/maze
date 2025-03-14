#ifndef MAZE_HPP
#define MAZE_HPP

#include "cell.hpp"
#include "rand.hpp"

/**
@class Maze
@brief Classe représentant un labyrinthe
*/
class Maze {
   public:
    /**
    @brief Constructeur par défaut
    */
    Maze();
    /**
     * @brief Constructeur
     * @param width Largeur du labyrinthe
     * @param height Hauteur du labyrinthe
     */
    Maze(int width, int height);
    /**
     * @brief Constructeur
     * @param width Largeur du labyrinthe
     * @param height Hauteur du labyrinthe
     * @param startX Coordonnée x de la cellule de départ
     * @param startY Coordonnée y de la cellule de départ
     * @param endX Coordonnée x de la cellule d'arrivée
     * @param endY Coordonnée y de la cellule d'arrivée
     */
    Maze(int width, int height, int startX, int startY, int endX, int endY);
    /**
     * @brief Destructeur
     */
    ~Maze();

    /**
     * @brief Retourne la largeur du labyrinthe
     * @return La largeur du labyrinthe
     */
    int getWidth() const;
    /**
     * @brief Retourne la hauteur du labyrinthe
     * @return La hauteur du labyrinthe
     */
    int getHeight() const;
    /**
     * @brief Retourne la taille du labyrinthe
     * @return La taille du labyrinthe
     */
    int getSize() const;
    /**
     * @brief Retourne les cellules du labyrinthe
     * @return Les cellules du labyrinthe
     */
    Cell ***getCells() const;
    /**
     * @brief Retourne une cellule du labyrinthe
     * @param x Coordonnée x de la cellule
     * @param y Coordonnée y de la cellule
     * @return La cellule du labyrinthe
     */
    Cell *getCell(int x, int y) const;
    /**
     * @brief Retourne un mur
     * @param x Coordonnée x du mur
     * @param y Coordonnée y du mur
     * @param horizontal Vrai si le mur est horizontal, faux sinon
     * @return Le mur
     */
    Wall *getWall(int x, int y, bool horizontal) const;
    /**
     * @brief Retourne la coordonnée x de la cellule de départ
     * @return La coordonnée x de la cellule de départ
     */
    int getStartX() const;
    /**
     * @brief Retourne la coordonnée y de la cellule de départ
     * @return La coordonnée y de la cellule de départ
     */
    int getStartY() const;
    /**
     * @brief Retourne la coordonnée x de la cellule d'arrivée
     * @return La coordonnée x de la cellule d'arrivée
     */
    int getEndX() const;
    /**
     * @brief Retourne la coordonnée y de la cellule d'arrivée
     * @return La coordonnée y de la cellule d'arrivée
     */
    int getEndY() const;
    /**
     * @brief Retourne la cellule de départ
     * @return La cellule de départ
     */
    Cell *getStartCell() const;
    /**
     * @brief Retourne la cellule d'arrivée
     * @return La cellule d'arrivée
     */
    Cell *getEndCell() const;

    /**
     * @brief Modifie la largeur et la hauteur du labyrinthe
     * @param width Nouvelle largeur du labyrinthe
     * @param height Nouvelle hauteur du labyrinthe
     */
    void setWidthHeight(int width, int height);
    /**
     * @brief Modifie la largeur et la hauteur du labyrinthe
     * @param width Nouvelle largeur du labyrinthe
     * @param height Nouvelle hauteur du labyrinthe
     * @param startX Coordonnées de la cellule de départ en largeur
     * @param startY Coordonnées de la cellule de départ en hauteur
     * @param endX Coordonnées de la cellule d'arrivée en largeur
     * @param endY Coordonnées de la cellule d'arrivée en hauteur
     */
    void setWidthHeight(int width, int height, int startX, int startY, int endX,
                        int endY);
    /**
     * @brief Modifie les cellules du labyrinthe
     * @param cells Nouvelles cellules du labyrinthe
     */
    void setCells(Cell ***cells);
    /**
     * @brief Modifie une cellule du labyrinthe
     * @param x Coordonnée x de la cellule
     * @param y Coordonnée y de la cellule
     * @param cell Nouvelle cellule du labyrinthe
     */
    void setCell(int x, int y, Cell *cell) const;
    /**
     * @brief Ajoute un mur
     * @param x Coordonnée x du mur
     * @param y Coordonnée y du mur
     * @param horizontal Vrai si le mur est horizontal, faux sinon
     * @return Vrai si le mur a été ajouté ou supprimé, faux sinon
     */
    void addWall(int x, int y, bool horizontal) const;
    /**
     * @brief Ajoute un mur entre deux cellules
     * @param cell1 Cellule 1
     * @param cell2 Cellule 2
     * @return Vrai si le mur a été ajouté ou supprimé, faux sinon
     */
    void addWall(const Cell *cell1, const Cell *cell2) const;
    /**
     * @brief Supprime un mur
     * @param x Coordonnée x du mur
     * @param y Coordonnée y du mur
     * @param horizontal Vrai si le mur est horizontal, faux sinon
     * @return Vrai si le mur a été supprimé, faux sinon
     */
    void removeWall(int x, int y, bool horizontal) const;
    /**
     * @brief Supprime un mur entre deux cellules
     * @param cell1 Cellule 1
     * @param cell2 Cellule 2
     * @return Vrai si le mur a été supprimé, faux sinon
     */
    void removeWall(const Cell *cell1, const Cell *cell2) const;
    /**
     * @brief Génère un labyrinthe
     */
    void generate();
    /**
     * @brief Détermine les coordonnées de la cellule de départ
     * @param x Coordonnée x de la cellule de départ
     * @param y Coordonnée y de la cellule de départ
     */
    void setStart(int x, int y);
    /**
     * @brief Détermine les coordonnées de la cellule d'arrivée
     * @param x Coordonnée x de la cellule d'arrivée
     * @param y Coordonnée y de la cellule d'arrivée
     */
    void setEnd(int x, int y);

    /**
     * @brief Libère la mémoire allouée pour les cellules du labyrinthe
     */
    void freeMaze();
    /**
     * @brief Nettoie le labyrinthe
     */
    void clearMaze() const;
    /**
     * @brief Retourne le générateur de nombres aléatoires
     * @return Le générateur de nombres aléatoires
     */
    Rand *getRand() { return &rand_; }
    /**
     * @brief Réinitialise l'emplacement de départ du labyrinthe
     */
    void resetStart();
    /**
     * @brief Réinitialise l'emplacement d'arrivée du labyrinthe
     */
    void resetEnd();
    /**
     * @brief Réinitialise l'emplacement de départ et d'arrivée du labyrinthe
     */
    void resetStartEnd();
    /**
     * @brief Définit le mode de test
     * @param testingMode Vrai si le mode de test est activé, faux sinon
     */
    void setTestingMode(const bool testingMode) { testingMode_ = testingMode; }
    /**
     * @brief Retourne le mode de test
     * @return Vrai si le mode de test est activé, faux sinon
     */
    bool getTestingMode() const { return testingMode_; }

   private:
    int width_{};               ///< Largeur du labyrinthe
    int height_{};              ///< Hauteur du labyrinthe
    Cell ***cells_ = nullptr;   ///< Cellules du labyrinthe
    int start_[2] = {0, 0};     ///< Coordonnées de la cellule de départ
    int end_[2] = {0, 0};       ///< Coordonnées de la cellule d'arrivée
    Rand rand_;                 ///< Générateur de nombres aléatoires
    bool testingMode_ = false;  ///< Mode de test

    /**
     * @brief Initialise les cellules du labyrinthe
     */
    void initNeighborsCells_() const;
};

#endif  // MAZE_HPP
