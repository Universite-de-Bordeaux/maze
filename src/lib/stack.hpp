#ifndef STACK_H
#define STACK_H

class Stack {
   private:
    int size_;
    int capacity_;
    void **data;

   public:
    Stack();   // Constructeur par défaut
    ~Stack();  // Destructeur

    void push(void *data);  // Ajoute un élément à la pile
    void pop();               // Retire un élément de la pile
    void *top();              // Retourne le premier élément de la pile
    bool empty();             // Retourne vrai si la pile est vide
};

#endif  // STACK_H