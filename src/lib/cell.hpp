#ifndef CELL_HPP
#define CELL_HPP

#include "var.hpp"
#include "wall.hpp"

/**
@class Cell
@brief Classe représentant une cellule de la grille
*/
class Cell {
   public:
    /**
    @brief Constructeur par défaut
    */
    Cell();
    /**
    @brief Constructeur
    @param x Coordonnée x de la cellule
    @param y Coordonnée y de la cellule
    */
    Cell(int, int);
    Cell(int, int, int, int);
    /**
    @brief Destructeur
    */
    ~Cell();

    /**
    @brief Récupère la coordonnée x de la cellule
    @return La coordonnée x de la cellule
    */
    int getX() const;
    /**
    @brief Récupère la coordonnée y de la cellule
    @return La coordonnée y de la cellule
    */
    int getY() const;
    /**
    @brief Récupère les voisins de la cellule
    @return Les voisins de la cellule
    */
    Cell **getNeighbors();
    /**
    @brief Récupère un voisin de la cellule
    @param int Voisin à récupérer
    @return Le voisin de la cellule
    */
    Cell *getNeighbor(int);
    Cell *getRelativeNeighbor(int);
    /**
    @brief Récupère les murs de la cellule
    @return Les murs de la cellule
    */
    Wall **getWalls();
    /**
    @brief Récupère un mur de la cellule
    @param int Mur à récupérer
    @return Le mur de la cellule
    */
    Wall *getWall(int);
    /**
     * @brief Récupère si la cellule a un mur
     * @param int Emplacement du mur à vérifier
     * @return Vrai si la cellule a un mur à l'emplacement donné
     */
    bool isWall(int);
    /**
    @brief Récupère si la cellule a déjà été visitée
    @return Vrai si la cellule a déjà été visitée
    */
    bool isAlreadyVisited();
    /**
    @brief Récupère le nombre de voisins de la cellule
    @return Le nombre de voisins de la cellule
    */
    int getAbsoluteNumberOfNeighbors();
    /**
    @brief Récupère les voisins de la cellule qui n'ont pas encore été visités
    @param neighbors Tableau de cellules dans lequel stocker les voisins
    */
    void getAbsoluteNeighbors(Cell **);
    /**
    @brief Récupère le nombre de voisins de la cellule qui n'ont pas encore été
    visités
    @return Le nombre de voisins de la cellule qui n'ont pas encore été visités
    */
    int getAbsoluteNumberOfNeighborsNotVisited();
    /**
    @brief Récupère les voisins de la cellule qui n'ont pas encore été visités
    @param neighbors Tableau de cellules dans lequel stocker les voisins
    */
    void getAbsoluteNeighborsNotVisited(Cell **);
    /**
    @brief Récupère le nombre de voisins relatifs de la cellule qui n'ont pas
    encore été visités
    @return Le nombre de voisins de la cellule relativess qui n'ont pas encore
    été visités
    */
    int getRelativeNumberOfNeighborsNotVisited();
    /**
    @brief Récupère les voisins relatifs de la cellule qui n'ont pas encore été
    visités
    @param neighbors Tableau de cellules relatives dans lequel stocker les
    voisins
    */
    void getRelativeNeighborsNotVisited(Cell **);
    /**
    @brief Récupère le statut de la cellule
    @return Le statut de la cellule
    */
    int getStatus();
    bool isNeighbor(int);
    bool isRelativeNeighbor(int);

    /**
    @brief Définit la coordonnée x de la cellule
    @param x Nouvelle coordonnée x de la cellule
    */
    void setX(int);
    /**
    @brief Définit la coordonnée y de la cellule
    @param y Nouvelle coordonnée y de la cellule
    */
    void setY(int);
    /**
    @brief Définit les voisins de la cellule
    @param neighbors Nouveaux voisins de la cellule
    */
    void setXY(int, int);
    /**
    @brief Définit un voisin de la cellule
    @param int Voisin à définir
    @param neighbor Nouveau voisin de la cellule
    */
    void setNeighbors(Cell *[4]);
    /**
    @brief Définit un voisin de la cellule
    @param int Voisin à définir
    @param neighbor Nouveau voisin de la cellule
    */
    void setNeighbor(int, Cell *);
    void setNeighbor(int, Cell *, bool);
    /**
    @brief Définit les murs de la cellule
    @param walls Nouveaux murs de la cellule
    */
    void setWalls(Wall *[4]);
    /**
    @brief Définit un mur de la cellule
    @param int Mur à définir
    @param wall Nouveau mur de la cellule
    */
    void setWall(int, Wall *);
    /**
    @brief Définit si la cellule a déjà été visitée
    @param bool Vrai si la cellule a déjà été visitée
    */
    void setAlreadyVisited(bool);
    /**
    @brief Définit le statut de la cellule
    @param int Nouveau statut de la cellule
    */
    void setStatus(int);

    /**
    @brief Supprime un mur de la cellule
    @param int Mur à supprimer
    */
    void freeWall(int);
    /**
    @brief Supprime les murs de la cellule
    */
    void freeWalls();

   private:
    int x_, y_;           ///< Coordonnées de la cellule
    int width_, height_;  ///< Largeur et hauteur du labirynthe
    Wall *walls_[4] = {nullptr, nullptr, nullptr,
                       nullptr};  ///< Murs de la cellule
    Cell *neighbors_[4] = {nullptr, nullptr, nullptr,
                           nullptr};  ///< Voisins de la cellule
    Cell *relativeNeighbors_[4] = {
        nullptr, nullptr, nullptr,
        nullptr};  ///< Voisins relatifs de la cellule
    bool alreadyVisited_ = false;
    int status_ = MAZE_STATUS_IDLE;
};

#endif  // CELL_H
