#include "maze.hpp"
#include "cell.hpp"
#include "stdlib.h"
#include <cstdio>
#include <cstdlib>
#include "var.hpp"
#include <iostream>

static int defaultStartX = 0;
static int defaultStartY = 0;
static int defaultEndX(int width) {
    return width - 1;
}
static int defaultEndY(int height) {
    return height - 1;
}

Maze::Maze() {
    Maze(0, 0, 0, 0, 0, 0);
}

Maze::Maze(int width, int height) {
    Maze(width, height, defaultStartX, defaultStartY, defaultEndX(width), defaultEndY(height));
}

Maze::Maze(int width, int height, int startX, int startY, int endX, int endY) {
    width_ = width, height_ = height;
    generate();
    start_[0] = startX, start_[1] = startY;
    end_[0] = endX, end_[1] = endY;
}

Maze::~Maze() {
    this->freeMaze();
}

int Maze::getWidth() const {
    return width_;
}

int Maze::getHeight() const {
    return height_;
}

int Maze::getSize() const {
    return width_*height_;
}

Cell **Maze::getCells() const {
    return cells_;
}

Cell *Maze::getCell(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return nullptr;
    }
    return cells_[y*width_+x];
}

Wall *Maze::getWall(int x, int y, bool isHorizontal) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return nullptr;
    }
    Cell *cell = this->getCell(x, y);
    if (isHorizontal) {
        return cell->getWall(MAZE_CELL_BOTTOM);
    } else {
        return cell->getWall(MAZE_CELL_RIGHT);
    }
}

int Maze::getStartX() {
    return start_[0];
}

int Maze::getStartY() {
    return start_[1];
}

int Maze::getEndX() {
    return end_[0];
}

int Maze::getEndY() {
    return end_[1];
}

Cell* Maze::getStartCell() {
    return getCell(start_[0], start_[1]);
}

Cell* Maze::getEndCell() {
    return getCell(end_[0], end_[1]);
}

void Maze::setWidthHeight(int width, int height) {
    setWidthHeight(width, height, defaultStartX, defaultStartY, defaultEndX(width), defaultEndY(height));
}

void Maze::setWidthHeight(int width, int height, int startX, int startY, int endX, int endY) {
    width_ = width, height_ = height;
    generate();
    start_[0] = startX, start_[1] = startY;
    end_[0] = endX, end_[1] = endY;
}

void Maze::setCells(Cell **cells) {
    cells_ = cells;
}

void Maze::setCell(int x, int y, Cell *cell) {
    cells_[y*width_+x] = cell;
}

void Maze::generate() {
    if (cells_ != nullptr) {
        this->freeMaze();
    }
    cells_ = new Cell*[width_*height_];
    for(int x = 0; x < width_; x++) {
        for(int y = 0; y < height_; y++) {
            Cell *cell = new Cell(x, y, width_, height_);
            cells_[y*width_+x] = cell;
        }
    }
    initNeighborsCells();
}

void Maze::setStart(int x, int y) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        start_[0] = defaultStartX, start_[1] = defaultStartY;
    } else {
        start_[0] = x, start_[1] = y;
    }
}

void Maze::setEnd(int x, int y) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        end_[0] = x, end_[1] = y;
    } else {
        end_[0] = defaultEndX(width_), end_[1] = defaultEndY(height_);
    }
}

bool Maze::addWall(int x, int y, bool isHorizontal) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return false;
    }
    Cell *cell = cells_[y*width_+x];
    Wall *wall = new Wall(isHorizontal);
    if (isHorizontal) {
        cell->setWall(MAZE_CELL_BOTTOM, wall);
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setWall(MAZE_CELL_TOP, wall);
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_CELL_TOP, nullptr);
        cell->setNeighbor(MAZE_CELL_BOTTOM, nullptr);
    } else {
        cell->setWall(MAZE_CELL_RIGHT, wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setNeighbor(MAZE_CELL_LEFT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT, nullptr);
    }
    return true;
}

bool Maze::removeWall(int x, int y, bool isHorizontal) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return false;
    }
    Cell *cell = cells_[y*width_+x];
    Wall *wall;
    if (isHorizontal) {
        wall = cell->getWall(MAZE_CELL_BOTTOM);
        cell->setWall(MAZE_CELL_BOTTOM, nullptr);
        cell->setNeighbor(MAZE_CELL_BOTTOM, cell->getRelativeNeighbor(MAZE_CELL_BOTTOM));
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setWall(MAZE_CELL_TOP, nullptr);
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_CELL_TOP, cell);
        cell->setNeighbor(MAZE_CELL_BOTTOM, cell->getNeighbor(MAZE_CELL_BOTTOM));
    } else {
        wall = cell->getWall(MAZE_CELL_RIGHT);
        cell->setWall(MAZE_CELL_RIGHT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT, cell->getRelativeNeighbor(MAZE_CELL_RIGHT));
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, nullptr);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setNeighbor(MAZE_CELL_LEFT, cell);
        cell->setNeighbor(MAZE_CELL_RIGHT, cell->getNeighbor(MAZE_CELL_RIGHT));
    }
    delete wall;
    return true;
}

void Maze::initNeighborsCells() {
    for(int x = 0; x < width_; x++) {
        for(int y = 0; y < height_; y++) {
            Cell *cell = cells_[y*width_+x];
            Cell **cellNeighbors = cell->getNeighbors();
            if (x > 0) {
                cell -> setNeighbor(MAZE_CELL_LEFT, cells_[y*width_+x-1], true);
            } else {
                cell -> setNeighbor(MAZE_CELL_LEFT, nullptr, true);
            }
            if (x < width_-1) {
                cell -> setNeighbor(MAZE_CELL_RIGHT, cells_[y*width_+x+1], true);
            } else {
                cell -> setNeighbor(MAZE_CELL_RIGHT, nullptr, true);
            }
            if (y > 0) {
                cell -> setNeighbor(MAZE_CELL_TOP, cells_[(y-1)*width_+x], true);
            } else {
                cell -> setNeighbor(MAZE_CELL_TOP, nullptr, true);
            }
            if (y < height_-1) {
                cell -> setNeighbor(MAZE_CELL_BOTTOM, cells_[(y+1)*width_+x], true);
            } else {
                cell -> setNeighbor(MAZE_CELL_BOTTOM, nullptr, true);
            }
            cell->setWall(MAZE_CELL_RIGHT, nullptr);
            cell->setWall(MAZE_CELL_BOTTOM, nullptr);
        }
    }
}

void Maze::freeMaze() {
    if (cells_ != nullptr) {
        for(int x = 0; x < width_; x++) {
            for(int y = 0; y < height_; y++) {
                Cell *cell = cells_[y*width_+x];
                // if (cell->getWall(MAZE_CELL_RIGHT) != nullptr) {
                //     delete (cell->getWall(MAZE_CELL_RIGHT));
                // }
                // if (cell->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                //     delete (cell->getWall(MAZE_CELL_BOTTOM));
                // }
            }
        }
        delete[] cells_;
    }
    start_[0] = defaultStartX, start_[1] = defaultStartY;
    end_[0] = defaultEndX(width_), end_[1] = defaultEndY(height_);
}

void Maze::clearMaze() {
    for(int x = 0; x < width_; x++) {
        for(int y = 0; y < height_; y++) {
            Cell *cell = cells_[y*width_+x];
            cell->setAlreadyVisited(false);
            cell->setStatus(MAZE_STATUS_IDLE);
        }
    }
}
