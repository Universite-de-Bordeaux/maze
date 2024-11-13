#ifndef WALL_HPP
#define WALL_HPP

/**
@class Wall
@brief Classe représentant un mur du labyrinthe
*/
class Wall {
    public:
        /**
        @enum NeighborsEnum
        @brief Enumération des voisins possibles d'un mur
        */

        /**
        @brief Constructeur par défaut
        */
        Wall();
        /**
        @brief Constructeur
        @param isHorizontal booléen indiquant si le mur est horizontal
        */
        Wall(bool);
        /**
        @brief Destructeur
        */
        ~Wall();

        /**
        @brief Retourne si le mur est horizontal
        @return booléen indiquant si le mur est horizontal
        */
        bool getIsHorizontal() const;
        /**
        @brief Retourne les voisins du mur
        @return tableau de pointeurs sur les voisins du mur
        */
        Wall** getNeighbors();
        /**
        @brief Retourne un voisin du mur
        @param NeighborsEnum voisin à retourner
        @return pointeur sur le voisin demandé
        */
        Wall* getNeighbor(int);
        bool isAlreadyVisited();
        bool isBorder();

        /**
        @brief Définit si le mur est horizontal
        @param booléen indiquant si le mur est horizontal
        */
        void setIsHorizontal(bool);
        /**
        @brief Définit les voisins du mur
        @param tableau de pointeurs sur les voisins du mur
        */
        void setNeighbors(Wall*[6]);
        /**
        @brief Définit un voisin du mur
        @param NeighborsEnum voisin à définir
        @param pointeur sur le voisin à définir
        */
        void setNeighbor(int, Wall*);
        void setAlreadyVisited(bool);
        void setBorder(bool);

    private:
        bool isHorizontal_; ///< Booléen indiquant si le mur est horizontal
        Wall* neighbors_[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}; ///< Tableau de pointeurs sur les voisins du mur
        bool alreadyVisited_ = false;
        bool isBorder_ = false;
};

#endif
