#include "maze.hpp"
#include "stdlib.h"
#include <cstdlib>

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
        free(this->cells);
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
    if (x < 0 || x >= this->width-1 || y < 0 || y >= this->height-1) {
        return false;
    }
    Cell *cell = this->cells[y*this->width+x];
    Wall wall = (Wall*)malloc(sizeof(Wall));
    wall = new Wall(isHorizontal);
    if (isHorizontal) {
        cell->setWall(cell->NeighborsEnum::BOTTOM, &wall);
        cell->getNeighbor(cell->NeighborsEnum::BOTTOM)->setWall(cell->NeighborsEnum::TOP, &wall);
        cell->getNeighbor(cell->NeighborsEnum::BOTTOM)->setNeighbor(cell->NeighborsEnum::TOP, nullptr);
        cell->setNeighbor(cell->NeighborsEnum::BOTTOM, nullptr);
    } else {
        cell->setWall(cell->NeighborsEnum::RIGHT, &wall);
        cell->getNeighbor(cell->NeighborsEnum::RIGHT)->setWall(cell->NeighborsEnum::LEFT, &wall);
        cell->getNeighbor(cell->NeighborsEnum::RIGHT)->setNeighbor(cell->NeighborsEnum::LEFT, nullptr);
        cell->setNeighbor(cell->NeighborsEnum::RIGHT, nullptr);
    }
    return true;
}

void Maze::initNeighborsCells() {
    for(int x = 0; x < this->width; x++) {
        for(int y = 0; y < this->height; y++) {
            Cell *cell = this->cells[y*this->width+x];
            Cell **cellNeighbors = cell->getNeighbors();
            if (x > 0) {
                cellNeighbors[cell->NeighborsEnum::LEFT] = this->cells[y*this->width+x-1];
            }
            if (x < this->width-1) {
                cellNeighbors[cell->NeighborsEnum::RIGHT] = this->cells[y*this->width+x+1];
            }
            if (y > 0) {
                cellNeighbors[cell->NeighborsEnum::TOP] = this->cells[(y-1)*this->width+x];
            }
            if (y < this->height-1) {
                cellNeighbors[cell->NeighborsEnum::BOTTOM] = this->cells[(y+1)*this->width+x];
            }
        }
    }
}
