#ifndef QUEUE_H
#define QUEUE_H

#include "cell.hpp"   // Inclure la classe Cell

class Queue {
private:
    Cell** array;          // Tableau de pointeurs vers des Cellules
    int size_array;        // Taille du tableau
    int left;              // Indice de la tête de la file
    int right;             // Indice de la queue de la file
    bool empty;            // Indicateur de file vide

    void grow_queue();     // Augmente la taille du tableau si nécessaire
    void shrink_queue();   // Réduit la taille du tableau si nécessaire

public:
    Queue();                // Constructeur par défaut
    ~Queue();               // Destructeur

    bool is_empty() const;  // Vérifie si la file est vide
    int get_size() const;   // Renvoie la taille de la file
    void enqueue(Cell* val); // Ajoute un élément à la file
    Cell* dequeue();         // Retire et renvoie un élément de la file
};

#endif // QUEUE_H
