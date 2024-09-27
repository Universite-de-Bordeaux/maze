#include "cell.hpp"

Cell::Cell() {
    Cell(0, 0);
}

Cell::Cell(int x, int y) {
    this->x = x;
    this->y = y;
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

Cell* Cell::getNeighbor(NeighborsEnum neighbor) {
    return this->neighbors[neighbor];
}

Wall** Cell::getWalls() {
    return this->walls;
}

Wall* Cell::getWall(NeighborsEnum neighbor) {
    return this->walls[neighbor];
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

void Cell::setNeighbor(NeighborsEnum neighbor, Cell* cell) {
    this->neighbors[neighbor] = cell;
}

void Cell::setWalls(Wall* walls[4]) {
    for (int i = 0; i < 4; i++) {
        this->walls[i] = walls[i];
    }
}

void Cell::setWall(NeighborsEnum neighbor, Wall* wall) {
    this->walls[neighbor] = wall;
}
