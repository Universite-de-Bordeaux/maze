#ifndef CELL_HPP
#define CELL_HPP

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
        Cell** getNeighbors();
        /**
        @brief Récupère un voisin de la cellule
        @param int Voisin à récupérer
        @return Le voisin de la cellule
        */
        Cell* getNeighbor(int);
        /**
        @brief Récupère les murs de la cellule
        @return Les murs de la cellule
        */
        Wall** getWalls();
        /**
        @brief Récupère un mur de la cellule
        @param int Mur à récupérer
        @return Le mur de la cellule
        */
        Wall* getWall(int);
        bool isAlreadyVisited();
        int getNumberOfNeighbors();
        void getAbsoluteNeighbors(Cell**);
        int getNumberOfNeighborsNotVisited();
        void getAbsoluteNeighborsNotVisited(Cell**);

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
        void setNeighbors(Cell*[4]);
        /**
        @brief Définit un voisin de la cellule
        @param int Voisin à définir
        @param neighbor Nouveau voisin de la cellule
        */
        void setNeighbor(int, Cell*);
        /**
        @brief Définit les murs de la cellule
        @param walls Nouveaux murs de la cellule
        */
        void setWalls(Wall*[4]);
        /**
        @brief Définit un mur de la cellule
        @param int Mur à définir
        @param wall Nouveau mur de la cellule
        */
        void setWall(int, Wall*);
        void setAlreadyVisited(bool);

        /**
        @brief Supprime les murs de la cellule
        */
        void freeWalls();

    private:
        int x, y; ///< Coordonnées de la cellule
        Wall *walls[4]; ///< Murs de la cellule
        Cell *neighbors[4]; ///< Voisins de la cellule
        bool alreadyVisited = false;
};

#endif // CELL_H
