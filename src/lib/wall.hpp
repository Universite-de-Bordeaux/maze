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
     * @brief Retourne les voisins du mur
     * @return Tableau de pointeurs sur les voisins du mur
     */
    Wall **getNeighbors();
    /**
     * @brief Retourne un voisin du mur
     * @param i Voisin à retourner
     * @return Pointeur sur le voisin demandé
     */
    Wall *getNeighbor(int i) const;
    /**
     * @brief Retourne si le mur a déjà été visité
     * @return Booléen indiquant si le mur a déjà été visité
     */
    bool isAlreadyVisited() const;
    /**
     * @brief Retourne si le mur est une bordure
     * @return Booléen indiquant si le mur est une bordure
     */
    bool isBorder() const;

    /**
     * @brief Définit si le mur est horizontal
     * @param horizontal Booléen indiquant si le mur est horizontal
     */
    void setIsHorizontal(bool horizontal);
    /**
     * @brief Définit les voisins du mur
     * @param neighbors Tableau de pointeurs sur les voisins du mur
     */
    void setNeighbors(Wall *neighbors[6]);
    /**
     * @brief Définit un voisin du mur
     * @param i Voisin à définir
     * @param wall Pointeur sur le voisin à définir
     */
    void setNeighbor(int i, Wall *wall);
    /**
     * @brief Définit si le mur a déjà été visité
     * @param visited  Booléen indiquant si le mur a déjà été visité
     */
    void setAlreadyVisited(bool visited);
    /**
     * @brief Définit si le mur est une bordure
     * @param isBorder Booléen indiquant si le mur est une bordure
     */
    void setBorder(bool isBorder);

   private:
    bool isHorizontal_{};  ///< Booléen indiquant si le mur est horizontal
    Wall *neighbors_[6] = {
        nullptr};  ///< Tableau de pointeurs sur les voisins du mur
    bool alreadyVisited_ =
        false;  ///< Booléen indiquant si le mur a déjà été visité
    bool isBorder_ = false;  ///< Booléen indiquant si le mur est une bordure
};

#endif  // WALL_HPP
