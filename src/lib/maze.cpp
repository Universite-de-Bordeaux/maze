#include "maze.hpp"
#include "stdlib.h"

Maze::Maze() {
    Maze(0, 0);
}

Maze::Maze(int width, int height) {
    this->width = width, this->height = height;
    generate();
}

Maze::~Maze() {
    //dtor
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
}
