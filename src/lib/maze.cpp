#include "maze.hpp"
#include "cell.hpp"
#include "stdlib.h"
#include <cstdlib>
#include "var.hpp"

Maze::Maze() {
    Maze(0, 0);
}

Maze::Maze(int width, int height) {
    width_ = width, height_ = height;
    generate();
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

Cell **Maze::getCells() const {
    return cells_;
}

Cell *Maze::getCell(int x, int y) const {
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

void Maze::setWidthHeight(int width, int height) {
    width_ = width, height_ = height;
    generate();
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
            Cell *cell = new Cell(x, y);
            cells_[y*width_+x] = cell;
        }
    }
    initNeighborsCells();
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

void Maze::initNeighborsCells() {
    for(int x = 0; x < width_; x++) {
        for(int y = 0; y < height_; y++) {
            Cell *cell = cells_[y*width_+x];
            Cell **cellNeighbors = cell->getNeighbors();
            if (x > 0) {
                cellNeighbors[MAZE_CELL_LEFT] = cells_[y*width_+x-1];
            }
            if (x < width_-1) {
                cellNeighbors[MAZE_CELL_RIGHT] = cells_[y*width_+x+1];
            }
            if (y > 0) {
                cellNeighbors[MAZE_CELL_TOP] = cells_[(y-1)*width_+x];
            }
            if (y < height_-1) {
                cellNeighbors[MAZE_CELL_BOTTOM] = cells_[(y+1)*width_+x];
            }
            cell->setWall(MAZE_CELL_RIGHT, nullptr);
            cell->setWall(MAZE_CELL_BOTTOM, nullptr);
        }
    }
}

int Maze::getSize() const {
    return width_*height_;
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
}
