#include "maze.hpp"
#include "cell.hpp"
#include "stdlib.h"
#include <cstdlib>
#include "var.hpp"

Maze::Maze() {
    Maze(0, 0);
}

Maze::Maze(int width, int height) {
    this->width = width, this->height = height;
    generate();
}

Maze::~Maze() {
    if (this->cells != nullptr) {
        for(int x = 0; x < this->width; x++) {
            for(int y = 0; y < this->height; y++) {
                delete this->cells[y*this->width+x];
            }
        }
        free(this->cells);
    }
}

int Maze::getWidth() const {
    return this->width;
}

int Maze::getHeight() const {
    return this->height;
}

Cell **Maze::getCells() const {
    return this->cells;
}

Cell *Maze::getCell(int x, int y) const {
    return this->cells[y*this->width+x];
}

Wall *Maze::getWall(int x, int y, bool isHorizontal) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return nullptr;
    }
    Cell *cell = this->getCell(x, y);
    if (isHorizontal) {
        return cell->getWall(MAZE_CELL_BOTTOM);
    } else {
        return cell->getWall(MAZE_CELL_RIGHT);
    }
}

void Maze::setWidthHeight(int width, int height) {
    this->width = width, this->height = height;
    generate();
}

void Maze::setCells(Cell **cells) {
    this->cells = cells;
}

void Maze::setCell(int x, int y, Cell *cell) {
    this->cells[y*this->width+x] = cell;
}

void Maze::generate() {
    if (this->cells != nullptr) {
        this->freeMaze();
    }
    this->cells = (Cell**)malloc(this->width*this->height*sizeof(Cell*));
    for(int x = 0; x < this->width; x++) {
        for(int y = 0; y < this->height; y++) {
            this->cells[y*this->width+x] = new Cell(x, y);
        }
    }
    initNeighborsCells();
}

bool Maze::addWall(int x, int y, bool isHorizontal) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return false;
    }
    Cell *cell = this->cells[y*this->width+x];
    Wall wall = (Wall*)malloc(sizeof(Wall));
    wall = new Wall(isHorizontal);
    if (isHorizontal) {
        cell->setWall(MAZE_CELL_BOTTOM, &wall);
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setWall(MAZE_CELL_TOP, &wall);
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_CELL_TOP, nullptr);
        cell->setNeighbor(MAZE_CELL_BOTTOM, nullptr);
    } else {
        cell->setWall(MAZE_CELL_RIGHT, &wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, &wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setNeighbor(MAZE_CELL_LEFT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT, nullptr);
    }
    return true;
}

void Maze::initNeighborsCells() {
    for(int x = 0; x < this->width; x++) {
        for(int y = 0; y < this->height; y++) {
            Cell *cell = this->cells[y*this->width+x];
            Cell **cellNeighbors = cell->getNeighbors();
            if (x > 0) {
                cellNeighbors[MAZE_CELL_LEFT] = this->cells[y*this->width+x-1];
            }
            if (x < this->width-1) {
                cellNeighbors[MAZE_CELL_RIGHT] = this->cells[y*this->width+x+1];
            }
            if (y > 0) {
                cellNeighbors[MAZE_CELL_TOP] = this->cells[(y-1)*this->width+x];
            }
            if (y < this->height-1) {
                cellNeighbors[MAZE_CELL_BOTTOM] = this->cells[(y+1)*this->width+x];
            }
            cell->setWall(MAZE_CELL_RIGHT, nullptr);
            cell->setWall(MAZE_CELL_BOTTOM, nullptr);
        }
    }
}

int Maze::getSize() const {
    return this->width*this->height;
}

void Maze::freeMaze() {
    if (this->cells != nullptr) {
        for(int x = 0; x < this->width; x++) {
            for(int y = 0; y < this->height; y++) {
                Cell *cell = this->cells[y*this->width+x];
                if (cell->getWall(MAZE_CELL_RIGHT) != nullptr) {
                    free (cell->getWall(MAZE_CELL_RIGHT));
                }
                if (cell->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                    free (cell->getWall(MAZE_CELL_BOTTOM));
                }
                delete cell;
            }
        }
        free(this->cells);
    }
}
