#include "breadth_first.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "../queue.hpp"
#include "../show.hpp"
#include "../var.hpp"

bool checker_breadthfirst(Maze *maze, Show *show) {
    refreshShow(show);
    std::cout << "Résolution du labyrinthe en largeur" << std::endl;
    Queue queue;
    int cont = 0;
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }
    queue.push(maze->getStartX(), maze->getStartY());
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    maze->getStartCell()->setAlreadyVisited(true);
    while (!queue.empty()) {
        Position current = queue.front();
        queue.pop();
        int x = current.x;
        int y = current.y;
        Cell *cell = maze->getCell(x, y);
        refreshShow(show);
        bool parfaite = true;
        for (int i = 0; i < 4; i++) {
            Cell *neighbor = cell->getNeighbor(i);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                queue.push(neighbor->getX(), neighbor->getY());
                neighbor->setStatus(MAZE_STATUS_VISITED);
                neighbor->setAlreadyVisited(true);
                cont++;
            }
            if (neighbor != nullptr && neighbor->isAlreadyVisited()) {
                parfaite = false;
            }
        }
        if (parfaite) {
            std::cout << "Le labirynthe n'est pas parfait" << std::endl;
        } else {
            std::cout << "Le labirynthe n'est parfait" << std::endl;
        }
        if (cont == maze->getSize()) {
            std::cout << "Le labirynthe est valide" << std::endl;
        } else {
            std::cout << "Le labirynthe n'est pas valide" << std::endl;
        }
    }