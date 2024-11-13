#ifndef QUEUE_H
#define QUEUE_H


struct Position {
    int x;
    int y;
};
Position *position;

class Queue {
private:
    int size_;
    int capacity_;

public:
    Queue();                // Constructeur par défaut
    ~Queue();               // Destructeur

    void push(int x, int y);  // Ajoute un élément à la file
    void pop();               // Retire un élément de la file
    Position front();         // Retourne le premier élément de la file
    bool empty();             // Retourne vrai si la file est vide
};

#endif // QUEUE_H
