#include "maze.hpp"

#include <iostream>

#include "cell.hpp"
#include "var.hpp"

static int defaultStartX(const int width, Rand *rand) {
    if (width <= 0) return 0;
    return rand->get(0, width - 1);
}
static int defaultStartY(const int height, Rand *rand) {
    if (height <= 0) return 0;
    return rand->get(0, height - 1);
}
static int defaultEndX(const int width, Rand *rand) {
    if (width <= 0) return 0;
    return rand->get(0, width - 1);
}
static int defaultEndY(const int height, Rand *rand) {
    if (height <= 0) return 0;
    return rand->get(0, height - 1);
}

Maze::Maze() : Maze(0, 0, 0, 0, 0, 0) {
    start_[0] = start_[1] = end_[0] = end_[1] = 0;
}

Maze::Maze(const int width, const int height)
    : Maze(width, height, defaultStartX(width, &rand_),
           defaultStartY(height, &rand_), defaultEndX(width, &rand_),
           defaultEndY(height, &rand_)) {};

Maze::Maze(const int width, const int height, const int startX,
           const int startY, const int endX, const int endY) {
    setWidthHeight(width, height, startX, startY, endX, endY);
}

Maze::~Maze() { freeMaze(); }

int Maze::getWidth() const { return width_; }

int Maze::getHeight() const { return height_; }

int Maze::getSize() const { return width_ * height_; }

Cell ***Maze::getCells() const { return cells_; }

Cell *Maze::getCell(const int x, const int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return nullptr;
    }
    return cells_[x][y];
}

Wall *Maze::getWall(const int x, const int y, const bool horizontal) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return nullptr;
    }
    const Cell *cell = getCell(x, y);
    if (cell == nullptr) return nullptr;
    if (horizontal) {
        return cell->getWall(MAZE_CELL_BOTTOM);
    }
    return cell->getWall(MAZE_CELL_RIGHT);
}

int Maze::getStartX() const { return start_[0]; }

int Maze::getStartY() const { return start_[1]; }

int Maze::getEndX() const { return end_[0]; }

int Maze::getEndY() const { return end_[1]; }

Cell *Maze::getStartCell() const { return getCell(start_[0], start_[1]); }

Cell *Maze::getEndCell() const { return getCell(end_[0], end_[1]); }

void Maze::setWidthHeight(const int width, const int height) {
    setWidthHeight(width, height, defaultStartX(width, &rand_),
                   defaultStartY(height, &rand_), defaultEndX(width, &rand_),
                   defaultEndY(height, &rand_));
}

void Maze::setWidthHeight(const int width, const int height, const int startX,
                          const int startY, const int endX, const int endY) {
    width_ = width, height_ = height;
    start_[0] = startX, start_[1] = startY;
    end_[0] = endX, end_[1] = endY;
    generate();
}

void Maze::setCells(Cell ***cells) { cells_ = cells; }

void Maze::setCell(const int x, const int y, Cell *cell) const {
    cells_[x][y] = cell;
}

void Maze::generate() {
    freeMaze();
    if (width_ <= 0 || height_ <= 0) {
        return;
    }
    cells_ = new Cell **[width_];
    for (int i = 0; i < width_; i++) {
        cells_[i] = new Cell *[height_];
        for (int j = 0; j < height_; j++) {
            cells_[i][j] = new Cell(i, j, width_, height_);
        }
    }
    initNeighborsCells_();
}

void Maze::setStart(const int x, const int y) {
    start_[0] = x, start_[1] = y;
    if (x < 0) start_[0] = 0;
    if (y < 0) start_[1] = 0;
    if (x >= width_) start_[0] = width_ - 1;
    if (y >= height_) start_[1] = height_ - 1;
}

void Maze::setEnd(const int x, const int y) {
    end_[0] = x, end_[1] = y;
    if (x < 0) end_[0] = 0;
    if (y < 0) end_[1] = 0;
    if (x >= width_) end_[0] = width_ - 1;
    if (y >= height_) end_[1] = height_ - 1;
}

void Maze::addWall(const int x, const int y, const bool horizontal) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }
    Cell *cell = getCell(x, y);
    const auto wall = new Wall(horizontal);
    if (horizontal) {
        cell->setWall(MAZE_CELL_BOTTOM, wall);
        if (cell->getNeighbor(MAZE_CELL_BOTTOM) == nullptr) return;
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setWall(MAZE_CELL_TOP, wall);
        cell->getNeighbor(MAZE_CELL_BOTTOM)
            ->setNeighbor(MAZE_CELL_TOP, nullptr);
        cell->setNeighbor(MAZE_CELL_BOTTOM, nullptr);
    } else {
        cell->setWall(MAZE_CELL_RIGHT, wall);
        if (cell->getNeighbor(MAZE_CELL_RIGHT) == nullptr) return;
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)
            ->setNeighbor(MAZE_CELL_LEFT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT, nullptr);
    }
}

void Maze::addWall(const Cell *cell1, const Cell *cell2) const {
    if (cell1 == nullptr || cell2 == nullptr) {
        return;
    }
    if (cell1->getX() == cell2->getX()) {
        if (cell1->getY() == cell2->getY() + 1) {
            return addWall(cell2->getX(), cell2->getY(), true);
        }
        if (cell1->getY() == cell2->getY() - 1) {
            return addWall(cell1->getX(), cell1->getY(), true);
        }
    } else if (cell1->getY() == cell2->getY()) {
        if (cell1->getX() == cell2->getX() + 1) {
            return addWall(cell2->getX(), cell2->getY(), false);
        }
        if (cell1->getX() == cell2->getX() - 1) {
            return addWall(cell1->getX(), cell1->getY(), false);
        }
    }
}

void Maze::removeWall(int x, int y, bool horizontal) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }
    Cell *cell = cells_[x][y];
    Wall *wall;
    if (horizontal) {
        wall = cell->getWall(MAZE_CELL_BOTTOM);
        cell->setWall(MAZE_CELL_BOTTOM, nullptr);
        cell->setNeighbor(MAZE_CELL_BOTTOM,
                          cell->getRelativeNeighbor(MAZE_CELL_BOTTOM));
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setWall(MAZE_CELL_TOP, nullptr);
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setNeighbor(MAZE_CELL_TOP, cell);
        cell->setNeighbor(MAZE_CELL_BOTTOM,
                          cell->getNeighbor(MAZE_CELL_BOTTOM));
    } else {
        wall = cell->getWall(MAZE_CELL_RIGHT);
        cell->setWall(MAZE_CELL_RIGHT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT,
                          cell->getRelativeNeighbor(MAZE_CELL_RIGHT));
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, nullptr);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setNeighbor(MAZE_CELL_LEFT, cell);
        cell->setNeighbor(MAZE_CELL_RIGHT, cell->getNeighbor(MAZE_CELL_RIGHT));
    }
    delete wall;
}

void Maze::removeWall(const Cell *cell1, const Cell *cell2) const {
    if (cell1 == nullptr || cell2 == nullptr) {
        return;
    }
    if (cell1->getX() == cell2->getX()) {
        if (cell1->getY() == cell2->getY() + 1) {
            return removeWall(cell2->getX(), cell2->getY(), true);
        }
        if (cell1->getY() == cell2->getY() - 1) {
            return removeWall(cell1->getX(), cell1->getY(), true);
        }
    } else if (cell1->getY() == cell2->getY()) {
        if (cell1->getX() == cell2->getX() + 1) {
            return removeWall(cell2->getX(), cell2->getY(), false);
        }
        if (cell1->getX() == cell2->getX() - 1) {
            return removeWall(cell1->getX(), cell1->getY(), false);
        }
    }
}

void Maze::initNeighborsCells_() const {
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            Cell *cell = cells_[x][y];
            if (x > 0) {
                cell->setNeighbor(MAZE_CELL_LEFT, cells_[x - 1][y]);
            } else {
                cell->setNeighbor(MAZE_CELL_LEFT, nullptr);
            }
            if (x < width_ - 1) {
                cell->setNeighbor(MAZE_CELL_RIGHT, cells_[x + 1][y]);
            } else {
                cell->setNeighbor(MAZE_CELL_RIGHT, nullptr);
            }
            if (y > 0) {
                cell->setNeighbor(MAZE_CELL_TOP, cells_[x][y - 1]);
            } else {
                cell->setNeighbor(MAZE_CELL_TOP, nullptr);
            }
            if (y < height_ - 1) {
                cell->setNeighbor(MAZE_CELL_BOTTOM, cells_[x][y + 1]);
            } else {
                cell->setNeighbor(MAZE_CELL_BOTTOM, nullptr);
            }
            cell->setWall(MAZE_CELL_RIGHT, nullptr);
            cell->setWall(MAZE_CELL_BOTTOM, nullptr);
        }
    }
}

void Maze::freeMaze() {
    if (cells_ != nullptr) {
        for (int i = 0; i < width_; ++i) {
            if (cells_[i] != nullptr) {
                for (int j = 0; j < height_; ++j) {
                    if (cells_[i][j] != nullptr) {
                        delete cells_[i][j];
                        cells_[i][j] = nullptr;
                    }
                }
                delete[] cells_[i];
                cells_[i] = nullptr;
            }
        }
        delete[] cells_;
        cells_ = nullptr;
    }
    start_[0] = start_[1] = end_[0] = end_[1] = 0;
}

void Maze::clearMaze() const {
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            Cell *cell = cells_[x][y];
            cell->setAlreadyVisited(false);
            cell->setStatus(MAZE_STATUS_IDLE);
        }
    }
}

void Maze::resetStartEnd() {
    resetStart();
    resetEnd();
}

void Maze::resetStart() {
    start_[0] = defaultStartX(width_, &rand_);
    start_[1] = defaultStartY(height_, &rand_);
}

void Maze::resetEnd() {
    end_[0] = defaultEndX(width_, &rand_);
    end_[1] = defaultEndY(height_, &rand_);
}