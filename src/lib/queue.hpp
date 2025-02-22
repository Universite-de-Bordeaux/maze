#ifndef QUEUE_H
#define QUEUE_H

#include "rand.hpp"

class Queue {
   public:
    /**
     * Constructeur par défaut
     */
    Queue();
    /**
     * Destructeur
     */
    ~Queue();

    /**
     * @brief Ajoute un élément à la file
     * @param data L'élément à ajouter
     */
    void push(void *data);
    /**
     * @brief Retourne un élément de la file
     * @param index Index de l'élément
     * @return Un élément de la file
     */
    void *get(int index) const;
    /**
     * @brief Retire un élément de la file
     */
    void pop();
    /**
     * @brief Retourne le premier élément de la file
     * @return Le premier élément de la file
     */
    void *front() const;
    /**
     * @brief Retourne un élément aléatoire de la file et le retire
     * @param rand Générateur de nombre aléatoire
     * @return Un élément aléatoire de la file
     */
    void *pop(Rand *rand);
    /**
     * @brief Retourne vrai si la file est vide
     * @return Vrai si la file est vide
     */
    bool empty() const;
    /**
     * @brief Retourne la taille de la file
     * @return La taille de la file
     */
    int size() const { return size_; }

   private:
    void **data;    ///< Tableau contenant les éléments de la file
    int size_;      ///< Nombre d'éléments dans la file
    int capacity_;  ///< Capacité de la file
};

#endif  // QUEUE_H
