#ifndef WALL_HPP
#define WALL_HPP

/**
@class Wall
@brief Classe représentant un mur du labyrinthe
*/
class Wall {
   public:
    /**
    @brief Constructeur par défaut
    */
    Wall();
    /**
     * @brief Constructeur
     * @param horizontal Booléen indiquant si le mur est horizontal
     */
    explicit Wall(bool horizontal);
    /**
     * @brief Destructeur
     */
    ~Wall();

    /**
     * @brief Retourne si le mur est horizontal
     * @return Booléen indiquant si le mur est horizontal
     */
    bool getIsHorizontal() const;
    /**
     * @brief Retourne si le mur a déjà été visité
     * @return Booléen indiquant si le mur a déjà été visité
     */
    bool isAlreadyVisited() const;

    /**
     * @brief Définit si le mur est horizontal
     * @param horizontal Booléen indiquant si le mur est horizontal
     */
    void setIsHorizontal(bool horizontal);
    /**
     * @brief Définit si le mur a déjà été visité
     * @param visited  Booléen indiquant si le mur a déjà été visité
     */
    void setAlreadyVisited(bool visited);

   private:
    bool isHorizontal_{};  ///< Booléen indiquant si le mur est horizontal
    bool alreadyVisited_ =
        false;  ///< Booléen indiquant si le mur a déjà été visité
};

#endif  // WALL_HPP
