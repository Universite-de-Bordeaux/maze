#include "cell.hpp"

Cell::Cell() {
    Cell(0, 0);
}

Cell::Cell(int x, int y) {
    this->x = x, this->y = y;
}

Cell::~Cell() {
    //dtor
}

int Cell::getX() const {
    return this->x;
}

int Cell::getY() const {
    return this->y;
}

Cell** Cell::getNeighbors() {
    return this->neighbors;
}

Cell* Cell::getNeighbor(int i) {
    return this->neighbors[i];
}

Wall** Cell::getWalls() {
    return this->walls;
}

Wall* Cell::getWall(int i) {
    return this->walls[i];
}

void Cell::setX(int x) {
    this->x = x;
}

void Cell::setY(int y) {
    this->y = y;
}

void Cell::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}

void Cell::setNeighbors(Cell* neighbors[4]) {
    for (int i = 0; i < 4; i++) {
        this->neighbors[i] = neighbors[i];
    }
}

void Cell::setNeighbor(int i, Cell* cell) {
    this->neighbors[i] = cell;
}

void Cell::setWalls(Wall* walls[4]) {
    for (int i = 0; i < 4; i++) {
        this->walls[i] = walls[i];
    }
}

void Cell::setWall(int i, Wall* wall) {
    this->walls[i] = wall;
}
