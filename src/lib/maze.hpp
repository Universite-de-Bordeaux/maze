#ifndef MAZE_HPP
#define MAZE_HPP

#include "cell.hpp"

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
        @brief Constructeur
        @param width Largeur du labyrinthe
        @param height Hauteur du labyrinthe
        */
        Maze(int, int);
        /**
        @brief Destructeur
        */
        ~Maze();

        /**
        @brief Retourne la largeur du labyrinthe
        @return La largeur du labyrinthe
        */
        int getWidth() const;
        /**
        @brief Retourne la hauteur du labyrinthe
        @return La hauteur du labyrinthe
        */
        int getHeight() const;
        /**
        @brief Retourne les cellules du labyrinthe
        @return Les cellules du labyrinthe
        */
        Cell ** getCells() const;
        /**
        @brief Retourne une cellule du labyrinthe
        @param x Coordonnée x de la cellule
        @param y Coordonnée y de la cellule
        @return La cellule du labyrinthe
        */
        Cell * getCell(int, int) const;

        /**
        @brief Modifie la largeur et la hauteur du labyrinthe
        @param width Nouvelle largeur du labyrinthe
        @param height Nouvelle hauteur du labyrinthe
        */
        void setWidthHeight(int, int);
        /**
        @brief Modifie les cellules du labyrinthe
        @param cells Nouvelles cellules du labyrinthe
        */
        void setCells(Cell **);
        /**
        @brief Modifie une cellule du labyrinthe
        @param x Coordonnée x de la cellule
        @param y Coordonnée y de la cellule
        @param cell Nouvelle cellule du labyrinthe
        */
        void setCell(int, int, Cell *);
        /**
        @brief Génère un labyrinthe
        */
        void generate();

    private:
        int width; ///< Largeur du labyrinthe
        int height; ///< Hauteur du labyrinthe
        Cell **cells = nullptr; ///< Cellules du labyrinthe
};

#endif // MAZE_HPP
