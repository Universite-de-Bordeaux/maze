#include "cell.hpp"
#include "var.hpp"
#include "wall.hpp"
#include <stdlib.h>

Cell::Cell() {
    Cell(0, 0);
}

Cell::Cell(int x, int y) {
    Cell(x, y, -1, -1);
}

Cell::Cell(int x, int y, int width, int height) {
    x_ = x, y_ = y;
    width_ = width, height_ = height;
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
        if (isNeighbor(i)) {
            Cell* neighbor = neighbors_[i];
            if (!(neighbor->isAlreadyVisited())) {
                count++;
            }
        }
    }
    return count;
}

void Cell::getAbsoluteNeighborsNotVisited(Cell** neighbors) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (isNeighbor(i)) {
            if (!neighbors_[i]->isAlreadyVisited()) {
                neighbors[count] = neighbors_[i];
                count++;
            }
        }
    }
}

int Cell::getStatus() {
    return status_;
}

bool Cell::isNeighbor(int i) {
    return !((getX() <= 0 && i == MAZE_CELL_LEFT) || (getY() <= 0 && i == MAZE_CELL_TOP) ||
            (getX() >= width_ - 1 && i == MAZE_CELL_RIGHT) || (getY() >= height_ - 1 && i == MAZE_CELL_BOTTOM)
    ) && neighbors_[i] != nullptr;
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

void Cell::setStatus(int status) {
    status_ = status;
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
