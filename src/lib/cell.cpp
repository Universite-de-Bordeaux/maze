#include "cell.hpp"
#include "wall.hpp"
#include <stdlib.h>

Cell::Cell() {
    Cell(0, 0);
}

Cell::Cell(int x, int y) {
    x_ = x, y_ = y;
}

Cell::~Cell() {
    this->freeWalls();
}

int Cell::getX() const {
    return x_;
}

int Cell::getY() const {
    return y_;
}

Cell** Cell::getNeighbors() {
    return neighbors_;
}

Cell* Cell::getNeighbor(int i) {
    return neighbors_[i];
}

Wall** Cell::getWalls() {
    return walls_;
}

Wall* Cell::getWall(int i) {
    return walls_[i];
}

bool Cell::isAlreadyVisited() {
    return alreadyVisited_;
}

int Cell::getAbsoluteNumberOfNeighbors() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (neighbors_[i] != nullptr) {
            count++;
        }
    }
    return count;
}

void Cell::getAbsoluteNeighbors(Cell** neighbors) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (neighbors_[i] != nullptr) {
            neighbors[count] = neighbors_[i];
            count++;
        }
    }
}

int Cell::getAbsoluteNumberOfNeighborsNotVisited() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (neighbors_[i] != nullptr && !neighbors_[i]->isAlreadyVisited()) {
            count++;
        }
    }
    return count;
}

void Cell::getAbsoluteNeighborsNotVisited(Cell** neighbors) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (neighbors_[i] != nullptr && !neighbors_[i]->isAlreadyVisited()) {
            neighbors[count] = neighbors_[i];
            count++;
        }
    }
}

void Cell::setX(int x) {
    x_ = x;
}

void Cell::setY(int y) {
    y_ = y;
}

void Cell::setXY(int x, int y) {
    x_ = x;
    y_ = y;
}

void Cell::setNeighbors(Cell* neighbors[4]) {
    for (int i = 0; i < 4; i++) {
        neighbors_[i] = neighbors[i];
    }
}

void Cell::setNeighbor(int i, Cell* cell) {
    neighbors_[i] = cell;
}

void Cell::setWalls(Wall* walls[4]) {
    for (int i = 0; i < 4; i++) {
        walls_[i] = walls[i];
    }
}

void Cell::setWall(int i, Wall* wall) {
    walls_[i] = wall;
}

void Cell::setAlreadyVisited(bool alreadyVisited) {
    alreadyVisited_ = alreadyVisited;
}

void Cell::freeWall(int i) {
    if (i < 0 || i > 3) {
        return;
    }
    if (this->getWall(i) != nullptr) {
        delete (walls_[i]);
    }
}

void Cell::freeWalls() {
    for (int i = 0; i < 4; i++) {
        this->freeWall(i);
    }
}
