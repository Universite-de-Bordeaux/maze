#include "walk.hpp"

#include <iostream>

#include "../show.hpp"
#include "../var.hpp"

int game_walk(const Maze *maze, Show *show, const bool ghost) {
    if (show == nullptr) {
        std::cerr << "Show is needed to play the game, use -gs or --game-show"
                  << std::endl;
        exit(MAZE_COMMAND_ERROR);
    }
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    if (!ghost)
        refreshShow(show);
    else {
        refreshShow(show, 1, &cell);
    }
    int steps = 0;
    while (cell->getX() != maze->getEndX() || cell->getY() != maze->getEndY()) {
        const int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            refreshShow(show, 1, &cell);
            return -1;
        }
        sf::Event event{};
        bool move = false;
        Cell *neighbor = nullptr;
        while (show->isOpen() && !move && show->pollEvent(event)) {
            show->eventHandler();
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape) {
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
            refreshShow(show, 2, showCell);
            cell = neighbor;
            steps++;
        }
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    return steps;
}
