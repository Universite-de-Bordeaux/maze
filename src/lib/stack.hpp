#ifndef STACK_H
#define STACK_H

class Stack {
   public:
    /**
     * Constructeur par défaut
     */
    Stack();
    /**
     * Destructeur
     */
    ~Stack();

    /**
     * @brief Ajoute un élément à la pile
     * @param data L'élément à ajouter
     */
    void push(void *data);
    /**
     * @brief Retire un élément de la pile
     */
    void pop();
    /**
     * @brief Retourne le premier élément de la pile
     * @return Le premier élément de la pile
     */
    void *top() const;
    /**
     * @brief Retourne vrai si la pile est vide
     * @return Retourne vrai si la pile est vide
     */
    bool empty() const;

   private:
    int size_;      ///< Taille de la pile
    int capacity_;  ///< Capacité de la pile
    void **data;    ///< Tableau de données
};

#endif  // STACK_H