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
        enum NeighborsEnum {
            START_RIGHT_TOP = 0 ,
            START = 1,
            START_LEFT_BOTTOM = 2,
            END_RIGHT_TOP = 3,
            END = 4,
            END_LEFT_BOTTOM = 5
        };

        /**
        @brief Constructeur par défaut
        */
        Wall();
        /**
        @brief Constructeur
        @param isHorizontal booléen indiquant si le mur est horizontal
        */
        Wall(bool isHorizontal);
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
        Wall* getNeighbor(NeighborsEnum);

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
        void setNeighbor(NeighborsEnum, Wall*);

    private:
        bool isHorizontal; ///< Booléen indiquant si le mur est horizontal
        Wall* neighbors[6]; ///< Tableau de pointeurs sur les voisins du mur
};

#endif
