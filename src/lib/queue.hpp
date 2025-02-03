#ifndef QUEUE_H
#define QUEUE_H

class Queue {
   private:
    int size_;
    int capacity_;
    void **data;

   public:
    Queue();   // Constructeur par défaut
    ~Queue();  // Destructeur

    void push(void *data);  // Ajoute un élément à la file
    void pop();               // Retire un élément de la file
    void *front();            // Retourne le premier élément de la file
    bool empty();             // Retourne vrai si la file est vide
};

#endif  // QUEUE_H
