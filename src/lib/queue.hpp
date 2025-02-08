#ifndef QUEUE_H
#define QUEUE_H

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
     * @brief Retire un élément de la file
     */
    void pop();
    /**
     * @brief Retourne le premier élément de la file
     * @return Le premier élément de la file
     */
    void *front() const;
    /**
     * @brief Retourne vrai si la file est vide
     * @return Vrai si la file est vide
     */
    bool empty() const;

   private:
    void **data;    ///< Tableau contenant les éléments de la file
    int size_;      ///< Nombre d'éléments dans la file
    int capacity_;  ///< Capacité de la file
};

#endif  // QUEUE_H
