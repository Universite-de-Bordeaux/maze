#ifndef CELL_HPP
#define CELL_HPP

#include "var.hpp"
#include "wall.hpp"

/**
 * @class Cell
 * @brief Classe représentant une cellule de la grille
 */
class Cell {
   public:
    /**
     * @brief Constructeur par défaut
     */
    Cell();
    /**
     * @brief Constructeur
     * @param x Coordonnée x de la cellule
     * @param y Coordonnée y de la cellule
     */
    Cell(int x, int y);
    /**
     * @brief Constructeur
     * @param x Coordonnée x de la cellule
     * @param y Coordonnée y de la cellule
     * @param width Largeur du labyrinthe
     * @param height Hauteur du labyrinthe
     */
    Cell(int x, int y, int width, int height);
    /**
     * @brief Destructeur
     */
    ~Cell();

    /**
     * @brief Récupère la coordonnée x de la cellule
     * @return La coordonnée x de la cellule
     */
    int getX() const;
    /**
     * @brief Récupère la coordonnée y de la cellule
     * @return La coordonnée y de la cellule
     */
    int getY() const;
    /**
     * @brief Récupère les voisins de la cellule
     * @return Les voisins de la cellule
     */
    Cell **getNeighbors();
    /**
     * @brief Récupère un voisin de la cellule
     * @param i Voisin à récupérer
     * @return Le voisin de la cellule
     */
    Cell *getNeighbor(int i) const;
    /**
     * @brief Récupère un voisin relatif de la cellule
     * @param i Voisin relatif à récupérer
     * @return Le voisin relatif de la cellule
     */
    Cell *getRelativeNeighbor(int i) const;
    /**
     * @brief Récupère les murs de la cellule
     * @return Les murs de la cellule
     */
    Wall **getWalls();
    /**
     * @brief Récupère un mur de la cellule
     * @param i Mur à récupérer
     * @return Le mur de la cellule
     */
    Wall *getWall(int i) const;
    /**
     * @brief Récupère si la cellule a un mur
     * @param i Emplacement du mur à vérifier
     * @return Vrai si la cellule a un mur à l'emplacement donné
     */
    bool isWall(int i) const;
    /**
     * @brief Récupère si la cellule a déjà été visitée
     * @return Vrai si la cellule a déjà été visitée
     */
    bool isAlreadyVisited() const;
    /**
     * @brief Récupère le nombre de voisins de la cellule
     * @return Le nombre de voisins de la cellule
     */
    int getAbsoluteNumberOfNeighbors() const;
    /**
     * @brief Récupère les voisins de la cellule qui n'ont pas encore été
     * visités
     * @param neighbors Tableau de cellules dans lesquelles stocker les voisins
     */
    void getAbsoluteNeighbors(Cell **neighbors) const;
    /**
     * @brief Récupère le nombre de voisins de la cellule qui n'ont pas encore
     * été visités
     * @return Le nombre de voisins de la cellule qui n'ont pas encore été
     * visités
     */
    int getAbsoluteNumberOfNeighborsNotVisited() const;
    /**
     * @brief Récupère les voisins de la cellule qui n'ont pas encore été
     * visités
     * @param neighbors Tableau de cellules dans lesquelles stocker les voisins
     */
    void getAbsoluteNeighborsNotVisited(Cell **neighbors) const;
    /**
     * @brief Récupère le nombre de voisins relatifs de la cellule qui n'ont pas
     * encore été visités
     * @return Le nombre de voisins de la cellule relatif qui n'ont pas encore
     * été visités
     */
    int getRelativeNumberOfNeighborsNotVisited() const;
    /**
     * @brief Récupère les voisins relatifs de la cellule qui n'ont pas encore
     * été visités
     * @param neighbors Tableau de cellules relatives dans lequel stocker les
     * voisins
     */
    void getRelativeNeighborsNotVisited(Cell **neighbors) const;
    /**
     * @brief Récupère le statut de la cellule
     * @return Le statut de la cellule
     */
    int getStatus() const;
    /**
     * @brief Récupère si la cellule est un voisin
     * @param i Voisin à vérifier
     * @return Vrai si la cellule est un voisin
     */
    bool isNeighbor(int i) const;
    /**
     * @brief Récupère si la cellule est un voisin relatif
     * @param i Voisin relatif à vérifier
     * @return Vrai si la cellule est un voisin relatif
     */
    bool isRelativeNeighbor(int i) const;

    /**
     * @brief Définit la coordonnée x de la cellule
     * @param x Nouvelle coordonnée x de la cellule
     */
    void setX(int x);
    /**
     * @brief Définit la coordonnée y de la cellule
     * @param y Nouvelle coordonnée y de la cellule
     */
    void setY(int y);
    /**
     * @brief Définit les coordonnées de la cellule
     * @param x Nouvelle coordonnée x de la cellule
     * @param y Nouvelle coordonnée y de la cellule
     */
    void setXY(int x, int y);
    /**
     * @brief Définit les voisins de la cellule
     * @param neighbors Nouveaux voisins de la cellule
     */
    void setNeighbors(Cell *neighbors[4]);
    /**
     * @brief Définit un voisin de la cellule
     * @param i Voisin à définir
     * @param neighbor Nouveau voisin de la cellule
     */
    void setNeighbor(int i, Cell *neighbor);
    /**
     * @brief Définit les murs de la cellule
     * @param walls Nouveaux murs de la cellule
     */
    void setWalls(Wall *walls[4]);
    /**
     * @brief Définit un mur de la cellule
     * @param i Mur à définir
     * @param wall Nouveau mur de la cellule
     */
    void setWall(int i, Wall *wall);
    /**
     * @brief Définit si la cellule a déjà été visitée
     * @param alreadyVisited Vrai si la cellule a déjà été visitée
     */
    void setAlreadyVisited(bool alreadyVisited);
    /**
     * @brief Définit le statut de la cellule
     * @param status Nouveau statut de la cellule
     */
    void setStatus(int status);

    /**
     * @brief Supprime un mur de la cellule
     * @param i Mur à supprimer
     */
    void freeWall(int i) const;
    /**
     * @brief Supprime les murs de la cellule
     */
    void freeWalls() const;

   private:
    int x_{}, y_{};                   ///< Coordonnées de la cellule
    int width_{}, height_{};          ///< Largeur et hauteur du labyrinthe
    Wall *walls_[4] = {nullptr};      ///< Murs de la cellule
    Cell *neighbors_[4] = {nullptr};  ///< Voisins de la cellule
    Cell *relativeNeighbors_[4] = {
        nullptr};                  ///< Voisins relatifs de la cellule
    bool alreadyVisited_ = false;  ///< Vrai si la cellule a déjà été visitée
    int status_ = MAZE_STATUS_IDLE;  ///< Statut de la cellule
};

#endif  // CELL_HPP
