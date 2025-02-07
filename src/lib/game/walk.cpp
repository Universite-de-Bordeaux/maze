#include <iostream>

#include "../show.hpp"
#include "../var.hpp"
#include "fog.hpp"

int game_walk(Maze *maze, Show *show, bool ghost) {
    if (show == nullptr) {
        std::cout << "No show" << std::endl;
        return -1;
    }
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    if (!ghost)
        refreshShow(show);
    else {
        updateShowLive(show, maze, 1, &cell);
    }
    int steps = 0;
    while (cell->getX() != maze->getEndX() || cell->getY() != maze->getEndY()) {
        int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            updateShowLive(show, maze, 1, &cell);
            return -1;
        }
        sf::Event event;
        bool move = false;
        Cell *neighbor = nullptr;
        while (show->isOpen() && !move && show->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                show->close();
                return -1;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    if (cell->getNeighbor(MAZE_CELL_TOP) != nullptr) {
                        neighbor = cell->getNeighbor(MAZE_CELL_TOP);
                        move = true;
                    }
                } else if (event.key.code == sf::Keyboard::Down) {
                    if (cell->getNeighbor(MAZE_CELL_BOTTOM) != nullptr) {
                        neighbor = cell->getNeighbor(MAZE_CELL_BOTTOM);
                        move = true;
                    }
                } else if (event.key.code == sf::Keyboard::Left) {
                    if (cell->getNeighbor(MAZE_CELL_LEFT) != nullptr) {
                        neighbor = cell->getNeighbor(MAZE_CELL_LEFT);
                        move = true;
                    }
                } else if (event.key.code == sf::Keyboard::Right) {
                    if (cell->getNeighbor(MAZE_CELL_RIGHT) != nullptr) {
                        neighbor = cell->getNeighbor(MAZE_CELL_RIGHT);
                        move = true;
                    }
                }
            }
        }
        if (neighbor != nullptr) {
            cell->setStatus(MAZE_STATUS_VISITED);
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            Cell *showCell[2] = {cell, neighbor};
            updateShowLive(show, maze, 2, showCell);
            cell = neighbor;
            steps++;
        }
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    return steps;
}
