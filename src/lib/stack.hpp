#ifndef STACK_H
#define STACK_H

#include "rand.hpp"

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
     * @brief Retourne un élément de la pile
     * @param index Index de l'élément
     * @return Un élément de la pile
     */
    void *get(int index) const;
    /**
     * @brief Retourne un élément aléatoire de la pile et le retire
     * @param rand Générateur de nombre aléatoire
     * @return Un élément aléatoire de la pile
     */
    void *pop(Rand *rand);
    /**
     * @brief Retourne vrai si la pile est vide
     * @return Retourne vrai si la pile est vide
     */
    bool empty() const;
    /**
     * @brief Retourne la taille de la pile
     * @return La taille de la pile
     */
    int size() const { return size_; }

   private:
    int size_;      ///< Taille de la pile
    int capacity_;  ///< Capacité de la pile
    void **data;    ///< Tableau de données
};

#endif  // STACK_H
