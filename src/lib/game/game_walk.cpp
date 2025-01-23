#include "game_fog.hpp"

#include "../show.hpp"
#include "../var.hpp"

#include <iostream>

bool game_walk(Maze *maze, Show *show) {
    updateShowLive(show, maze);
    refreshShow(show);
    Cell *cell = maze->getCell(maze->getStartX(), maze->getStartY());
    cell->setStatus(MAZE_STATUS_CURRENT);
    updateShowLive(show, maze, 1, &cell);
    refreshShow(show);
    while (cell->getX() != maze->getEndX() || cell->getY() != maze->getEndY()){
        int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
        if (nbNeighbors == 0) {
            cell->setStatus(MAZE_STATUS_HOPELESS);
            updateShowLive(show, maze, 1, &cell);
            return false;
        }
        sf::Event event;
        bool move = false;
        Cell *neighbor = nullptr;
        while (show->isOpen() && !move && show->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                show->close();
                return false;
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
            neighbor->setStatus(MAZE_STATUS_CURRENT);
            updateShowLive(show, maze, 1, &neighbor);
            cell->setStatus(MAZE_STATUS_VISITED);
            updateShowLive(show, maze, 1, &cell);
            cell = neighbor;
        }
        refreshShow(show);
    }
    cell->setStatus(MAZE_STATUS_WAY_OUT);
    return true;
}
