#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "maze.hpp"
#include "cell.hpp"
#include "stdlib.h"
#include "var.hpp"

static int defaultStartX(int width) {
    return 0;
}
static int defaultStartY(int height) {
    return 0;
}
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
    Maze(width, height, defaultStartX(width), defaultStartY(height), defaultEndX(width), defaultEndY(height));
}

Maze::Maze(int width, int height, int startX, int startY, int endX, int endY) {
    width_ = width, height_ = height;
    generate();
    start_[0] = startX, start_[1] = startY;
    end_[0] = endX, end_[1] = endY;
}

Maze::~Maze() {
    freeMaze();
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
    Cell *cell = getCell(x, y);
    if (cell == nullptr) return nullptr;
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
    setWidthHeight(width, height, defaultStartX(width), defaultStartY(height), defaultEndX(width), defaultEndY(height));
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
        freeMaze();
    }
    cells_ = new Cell*[width_*height_];
    for(int x = 0; x < width_; x++) {
        for(int y = 0; y < height_; y++) {
            Cell *cell = new Cell(x, y, width_, height_);
            cells_[y*width_+x] = cell;
        }
    }
    initNeighborsCells_();
}

void Maze::setStart(int x, int y) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        start_[0] = defaultStartX(width_), start_[1] = defaultStartY(height_);
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
    return addWall(x, y, isHorizontal, false);
}

bool Maze::addWall(int x, int y, bool isHorizontal, bool neighborsConnection) {
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
        if (neighborsConnection) {
            if (x > 0) {
                std::cout << "horizontal wall: " << x << ", " << y << " with x > 0" << std::endl;
                if (getWall(x-1, y, MAZE_CELL_RIGHT) != nullptr) {
                    std::cout << "horizontal wall: " << x << ", " << y << " to vertical wall: " << x-1 << ", " << y << std::endl;
                    wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, getWall(x-1, y, MAZE_CELL_RIGHT));
                    getWall(x-1, y, MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_END_RIGHT_TOP, wall);
                }
                if (y < height_-1) {
                    std::cout << "horizontal wall: " << x << ", " << y << " with y < height_-1" << std::endl;
                    if (getWall(x-1, y+1, MAZE_CELL_RIGHT) != nullptr) {
                        std::cout << "horizontal wall: " << x << ", " << y << " to vertical wall: " << x-1 << ", " << y+1 << std::endl;
                        wall->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, getWall(x, y+1, MAZE_CELL_RIGHT));
                        getWall(x-1, y+1, MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_START_RIGHT_TOP, wall);
                    }
                    if (getWall(x-1, y, MAZE_CELL_BOTTOM) != nullptr) {
                        std::cout << "horizontal wall: " << x << ", " << y << " to horizontal wall: " << x << ", " << y+1 << std::endl;
                        wall->setNeighbor(MAZE_WALL_START, getWall(x, y+1, MAZE_CELL_BOTTOM));
                        getWall(x-1, y, MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_END, wall);
                    }
                }
            }
            if (x < width_-1) {
                std::cout << "horizontal wall: " << x << ", " << y << " with x < width_-1" << std::endl;
                if (getWall(x, y, MAZE_CELL_RIGHT) != nullptr) {
                    std::cout << "horizontal wall: " << x << ", " << y << " to vertical wall: " << x+1 << ", " << y+1 << std::endl;
                    wall->setNeighbor(MAZE_WALL_END_RIGHT_TOP, getWall(x, y, MAZE_CELL_RIGHT));
                    getWall(x, y, MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, wall);
                }
                if (y < height_-1) {
                    std::cout << "horizontal wall: " << x << ", " << y << " with y < height_-1" << std::endl;
                    if (getWall(x, y+1, MAZE_CELL_RIGHT) != nullptr) {
                        std::cout << "horizontal wall: " << x << ", " << y << " to vertical wall: " << x+1 << ", " << y << std::endl;
                        wall->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, getWall(x, y+1, MAZE_CELL_RIGHT));
                        getWall(x, y+1, MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, wall);
                    }
                    if (getWall(x+1, y, MAZE_CELL_BOTTOM) != nullptr) {
                        std::cout << "horizontal wall: " << x << ", " << y << " to horizontal wall: " << x << ", " << y+1 << std::endl;
                        wall->setNeighbor(MAZE_WALL_END, getWall(x, y+1, MAZE_CELL_BOTTOM));
                        getWall(x+1, y, MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_START, wall);
                    }
                }
            }
            if (x == 0 || x == width_-1) {
                wall->setBorder(true);
            }
        }
    } else {
        cell->setWall(MAZE_CELL_RIGHT, wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setNeighbor(MAZE_CELL_LEFT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT, nullptr);
        if (neighborsConnection) {
            if (y > 0) {
                std::cout << "vertical wall: " << x << ", " << y << " with y > 0" << std::endl;
                if (getWall(x, y-1, MAZE_CELL_BOTTOM) != nullptr) {
                    std::cout << "vertical wall: " << x << ", " << y << " to horizontal wall: " << x << ", " << y << std::endl;
                    wall->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, getWall(x, y-1, MAZE_CELL_BOTTOM));
                    getWall(x, y-1, MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, wall);
                }
                if (x < width_-1) {
                    std::cout << "vertical wall: " << x << ", " << y << " with x < width_-1" << std::endl;
                    if (getWall(x+1, y-1, MAZE_CELL_BOTTOM) != nullptr) {
                        std::cout << "vertical wall: " << x << ", " << y << " to horizontal wall: " << x+1 << ", " << y << std::endl;
                        wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, getWall(x+1, y-1, MAZE_CELL_BOTTOM));
                        getWall(x+1, y-1, MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, wall);
                    }
                    if (getWall(x, y-1, MAZE_CELL_RIGHT) != nullptr) {
                        std::cout << "vertical wall: " << x << ", " << y << " to vertical wall: " << x+1 << ", " << y << std::endl;
                        wall->setNeighbor(MAZE_WALL_START, getWall(x+1, y, MAZE_CELL_RIGHT));
                        getWall(x, y-1, MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_END, wall);
                    }
                }
            }
            if (y < height_-1) {
                std::cout << "vertical wall: " << x << ", " << y << " with y < height_-1" << std::endl;
                if (getWall(x, y, MAZE_CELL_BOTTOM) != nullptr) {
                    std::cout << "vertical wall: " << x << ", " << y << " to horizontal wall: " << x << ", " << y+1 << std::endl;
                    wall->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, getWall(x, y, MAZE_CELL_BOTTOM));
                    getWall(x, y, MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_END_RIGHT_TOP, wall);
                }
                if (x < width_-1) {
                    std::cout << "vertical wall: " << x << ", " << y << " with x < width_-1" << std::endl;
                    if (getWall(x+1, y, MAZE_CELL_BOTTOM) != nullptr) {
                        std::cout << "vertical wall: " << x << ", " << y << " to horizontal wall: " << x+1 << ", " << y+1 << std::endl;
                        wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, getWall(x+1, y, MAZE_CELL_BOTTOM));
                        getWall(x+1, y, MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_START_RIGHT_TOP, wall);
                    }
                    if (getWall(x, y+1, MAZE_CELL_RIGHT) != nullptr) {
                        std::cout << "vertical wall: " << x << ", " << y << " to vertical wall: " << x+1 << ", " << y << std::endl;
                        wall->setNeighbor(MAZE_WALL_END, getWall(x, y, MAZE_CELL_RIGHT));
                        getWall(x, y+1, MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_START, wall);
                    }
                }
            }
            if (y == 0 || y == height_-1) {
                wall->setBorder(true);
            }
        }
    }
    return true;
}

bool Maze::addWall(Cell *cell1, Cell *cell2) {
    if (cell1 == nullptr || cell2 == nullptr) {
        return false;
    }
    if (cell1->getX() == cell2->getX()) {
        if (cell1->getY() == cell2->getY() + 1) {
            return addWall(cell2->getX(), cell2->getY(), true);
        } else if (cell1->getY() == cell2->getY() - 1) {
            return addWall(cell1->getX(), cell1->getY(), true);
        }
    } else if (cell1->getY() == cell2->getY()) {
        if (cell1->getX() == cell2->getX() + 1) {
            return addWall(cell2->getX(), cell2->getY(), false);
        } else if (cell1->getX() == cell2->getX() - 1) {
            return addWall(cell1->getX(), cell1->getY(), false);
        }
    }
    return false;
}

bool Maze::removeWall(int x, int y, bool isHorizontal) {
    return removeWall(x, y, isHorizontal, false);
}

bool Maze::removeWall(int x, int y, bool isHorizontal, bool neighborsConnection) {
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
        if (neighborsConnection) {
            if (x > 0) {
                if (getCell(x-1, y)->getWall(MAZE_CELL_RIGHT) != nullptr) {
                    wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                    getCell(x-1, y)->getWall(MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_END_RIGHT_TOP, nullptr);
                }
                if (y < height_-1) {
                    if (getCell(x-1, y+1)->getWall(MAZE_CELL_RIGHT) != nullptr) {
                        wall->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, nullptr);
                        getCell(x-1, y+1)->getWall(MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                    }
                    if (getCell(x-1, y)->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                        wall->setNeighbor(MAZE_WALL_START, nullptr);
                        getCell(x-1, y)->getWall(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_END, nullptr);
                    }
                }
            }
            if (x < width_-1) {
                if (cell->getWall(MAZE_CELL_RIGHT) != nullptr) {
                    wall->setNeighbor(MAZE_WALL_END_RIGHT_TOP, nullptr);
                    getCell(x, y)->getWall(MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, nullptr);
                }
                if (y < height_-1) {
                    if (getCell(x, y+1)->getWall(MAZE_CELL_RIGHT) != nullptr) {
                        wall->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, nullptr);
                        getCell(x, y+1)->getWall(MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, nullptr);
                    }
                    if (getCell(x+1, y)->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                        wall->setNeighbor(MAZE_WALL_END, nullptr);
                        getCell(x+1, y)->getWall(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_START, nullptr);
                    }
                }
            }
        }
    } else {
        wall = cell->getWall(MAZE_CELL_RIGHT);
        cell->setWall(MAZE_CELL_RIGHT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT, cell->getRelativeNeighbor(MAZE_CELL_RIGHT));
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, nullptr);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setNeighbor(MAZE_CELL_LEFT, cell);
        cell->setNeighbor(MAZE_CELL_RIGHT, cell->getNeighbor(MAZE_CELL_RIGHT));
        if (neighborsConnection) {
            if (y > 0) {
                if (getCell(x, y-1)->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                    wall->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, nullptr);
                    getCell(x, y-1)->getWall(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, nullptr);
                }
                if (x < width_-1) {
                    if (getCell(x+1, y-1)->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                        wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                        getCell(x+1, y-1)->getWall(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, nullptr);
                    }
                    if (getCell(x, y-1)->getWall(MAZE_CELL_RIGHT) != nullptr) {
                        wall->setNeighbor(MAZE_WALL_START, nullptr);
                        getCell(x, y-1)->getWall(MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_END, nullptr);
                    }
                }
            }
            if (y < height_-1) {
                if (cell->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                    wall->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, nullptr);
                    getCell(x, y)->getWall(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_END_RIGHT_TOP, nullptr);
                }
                if (x < width_-1) {
                    if (getCell(x+1, y)->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                        wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                        getCell(x+1, y)->getWall(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                    }
                    if (getCell(x, y+1)->getWall(MAZE_CELL_RIGHT) != nullptr) {
                        wall->setNeighbor(MAZE_WALL_END, nullptr);
                        getCell(x, y+1)->getWall(MAZE_CELL_RIGHT)->setNeighbor(MAZE_WALL_START, nullptr);
                    }
                }
            }
        }
    }
    delete wall;
    return true;
}

bool Maze::removeWall(Cell *cell1, Cell *cell2) {
    if (cell1 == nullptr || cell2 == nullptr) {
        return false;
    }
    if (cell1->getX() == cell2->getX()) {
        if (cell1->getY() == cell2->getY() + 1) {
            return removeWall(cell2->getX(), cell2->getY(), true);
        } else if (cell1->getY() == cell2->getY() - 1) {
            return removeWall(cell1->getX(), cell1->getY(), true);
        }
    } else if (cell1->getY() == cell2->getY()) {
        if (cell1->getX() == cell2->getX() + 1) {
            return removeWall(cell2->getX(), cell2->getY(), false);
        } else if (cell1->getX() == cell2->getX() - 1) {
            return removeWall(cell1->getX(), cell1->getY(), false);
        }
    }
    return false;
}

void Maze::initNeighborsCells_() {
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
    start_[0] = defaultStartX(width_), start_[1] = defaultStartY(height_);
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
