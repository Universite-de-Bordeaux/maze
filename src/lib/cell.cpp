#include "cell.hpp"

#include "var.hpp"
#include "wall.hpp"

Cell::Cell() : Cell(0, 0) {}

Cell::Cell(const int x, const int y) : Cell(x, y, -1, -1) {}

Cell::Cell(const int x, const int y, const int width, const int height) {
    x_ = x, y_ = y;
    width_ = width, height_ = height;
}

Cell::~Cell() { freeWalls(); }

int Cell::getX() const { return x_; }

int Cell::getY() const { return y_; }

Cell **Cell::getNeighbors() { return neighbors_; }

Cell *Cell::getNeighbor(const int i) const { return neighbors_[i]; }

Cell *Cell::getRelativeNeighbor(const int i) const { return relativeNeighbors_[i]; }

Wall **Cell::getWalls() { return walls_; }

Wall *Cell::getWall(const int i) const { return walls_[i]; }

bool Cell::isWall(const int i) const {
    return walls_[i] != nullptr || (i == MAZE_CELL_TOP && y_ == 0) ||
           (i == MAZE_CELL_LEFT && x_ == 0) ||
           (i == MAZE_CELL_RIGHT && x_ == width_ - 1) ||
           (i == MAZE_CELL_BOTTOM && y_ == height_ - 1);
}

bool Cell::isAlreadyVisited() const { return alreadyVisited_; }

int Cell::getAbsoluteNumberOfNeighbors() const {
    int count = 0;
    for (const auto neighbor : neighbors_) {
        if (neighbor != nullptr) {
            count++;
        }
    }
    return count;
}

void Cell::getAbsoluteNeighbors(Cell **neighbors) const {
    if (neighbors == nullptr) return;
    int count = 0;
    for (const auto neighbor : neighbors_) {
        if (neighbor != nullptr) {
            neighbors[count] = neighbor;
            count++;
        }
    }
}

int Cell::getAbsoluteNumberOfNeighborsNotVisited() const {
    int count = 0;
    for (const auto neighbor : neighbors_) {
        if (neighbor != nullptr) {
            if (!neighbor->isAlreadyVisited()) {
                count++;
            }
        }
    }
    return count;
}

void Cell::getAbsoluteNeighborsNotVisited(Cell **neighbors) const {
    int count = 0;
    for (const auto neighbor : neighbors_) {
        if (neighbor != nullptr) {
            if (!neighbor->isAlreadyVisited()) {
                neighbors[count] = neighbor;
                count++;
            }
        }
    }
}

int Cell::getRelativeNumberOfNeighborsNotVisited() const {
    int count = 4;
    if (getX() <= 0) {
        count--;
    }
    if (getY() <= 0) {
        count--;
    }
    if (getX() >= width_ - 1) {
        count--;
    }
    if (getY() >= height_ - 1) {
        count--;
    }
    return count;
}

void Cell::getRelativeNeighborsNotVisited(Cell **neighbors) const {
    int count = 0;
    if (getX() > 0) {
        neighbors[count] = relativeNeighbors_[MAZE_CELL_LEFT];
        count++;
    }
    if (getY() > 0) {
        neighbors[count] = relativeNeighbors_[MAZE_CELL_TOP];
        count++;
    }
    if (getX() < width_ - 1) {
        neighbors[count] = relativeNeighbors_[MAZE_CELL_RIGHT];
        count++;
    }
    if (getY() < height_ - 1) {
        neighbors[count] = relativeNeighbors_[MAZE_CELL_BOTTOM];
    }
}

int Cell::getStatus() const { return status_; }

bool Cell::isNeighbor(const int i) const {
    return !((getX() <= 0 && i == MAZE_CELL_LEFT) ||
             (getY() <= 0 && i == MAZE_CELL_TOP) ||
             (getX() >= width_ - 1 && i == MAZE_CELL_RIGHT) ||
             (getY() >= height_ - 1 && i == MAZE_CELL_BOTTOM)) &&
           neighbors_[i] != nullptr;
}

bool Cell::isRelativeNeighbor(const int i) const {
    return !((getX() <= 0 && i == MAZE_CELL_LEFT) ||
             (getY() <= 0 && i == MAZE_CELL_TOP) ||
             (getX() >= width_ - 1 && i == MAZE_CELL_RIGHT) ||
             (getY() >= height_ - 1 && i == MAZE_CELL_BOTTOM)) &&
           relativeNeighbors_[i] != nullptr;
}

void Cell::setX(const int x) { x_ = x; }

void Cell::setY(const int y) { y_ = y; }

void Cell::setXY(const int x, const int y) {
    x_ = x;
    y_ = y;
}

void Cell::setNeighbors(Cell *neighbors[4]) {
    for (int i = 0; i < 4; i++) {
        neighbors_[i] = neighbors[i];
        if (neighbors[i] != nullptr) {
            relativeNeighbors_[i] = neighbors[i];
        }
    }
}

void Cell::setNeighbor(const int i, Cell *neighbor) { 
    neighbors_[i] = neighbor;
    if (neighbor != nullptr) {
        relativeNeighbors_[i] = neighbor;
    }
}

void Cell::setWalls(Wall *walls[4]) {
    for (int i = 0; i < 4; i++) {
        walls_[i] = walls[i];
    }
}

void Cell::setWall(const int i, Wall *wall) { walls_[i] = wall; }

void Cell::setAlreadyVisited(const bool alreadyVisited) {
    alreadyVisited_ = alreadyVisited;
}

void Cell::setStatus(const int status) { status_ = status; }

void Cell::freeWall(const int i) const {
    if (i < 0 || i > 3) {
        return;
    }
    if (getWall(i) != nullptr) {
        delete walls_[i];
    }
}

void Cell::freeWalls() const {
    for (int i = 0; i < 4; i++) {
        freeWall(i);
    }
}
