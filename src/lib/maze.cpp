#include "maze.hpp"

#include <random>

#include "cell.hpp"
#include "var.hpp"

static int defaultStartX(const int width) {
    if (width <= 0) return 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, width - 1);
    return dis(gen);
}
static int defaultStartY(const int height) {
    if (height <= 0) return 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, height - 1);
    return dis(gen);
}
static int defaultEndX(const int width) {
    if (width <= 0) return 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, width - 1);
    return dis(gen);
}
static int defaultEndY(const int height) {
    if (height <= 0) return 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, height - 1);
    return dis(gen);
}

Maze::Maze() : Maze(0, 0, 0, 0, 0, 0){};

Maze::Maze(const int width, const int height)
    : Maze(width, height, defaultStartX(width), defaultStartY(height),
           defaultEndX(width), defaultEndY(height)){};

Maze::Maze(const int width, const int height, const int startX,
           const int startY, const int endX, const int endY) {
    width_ = width, height_ = height;
    generate();
    start_[0] = startX, start_[1] = startY;
    end_[0] = endX, end_[1] = endY;
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
    setWidthHeight(width, height, defaultStartX(width), defaultStartY(height),
                   defaultEndX(width), defaultEndY(height));
}

void Maze::setWidthHeight(const int width, const int height, const int startX,
                          const int startY, const int endX, const int endY) {
    width_ = width, height_ = height;
    generate();
    start_[0] = startX, start_[1] = startY;
    end_[0] = endX, end_[1] = endY;
}

void Maze::setCells(Cell ***cells) { cells_ = cells; }

void Maze::setCell(const int x, const int y, Cell *cell) const {
    cells_[x][y] = cell;
}

void Maze::generate() {
    if (cells_ != nullptr) {
        freeMaze();
    }
    cells_ = new Cell **[width_];
    for (int i = 0; i < width_; i++) {
        cells_[i] = new Cell *[height_];
    }

    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            const auto cell = new Cell(x, y, width_, height_);
            cells_[x][y] = cell;
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

bool Maze::addWall(const int x, const int y, const bool horizontal) const {
    return addWall(x, y, horizontal, false);
}

bool Maze::addWall(const int x, const int y, const bool horizontal,
                   const bool neighborsConnection) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return false;
    }
    Cell *cell = cells_[x][y];
    const auto wall = new Wall(horizontal);
    if (horizontal) {
        cell->setWall(MAZE_CELL_BOTTOM, wall);
        cell->getNeighbor(MAZE_CELL_BOTTOM)->setWall(MAZE_CELL_TOP, wall);
        cell->getNeighbor(MAZE_CELL_BOTTOM)
            ->setNeighbor(MAZE_CELL_TOP, nullptr);
        cell->setNeighbor(MAZE_CELL_BOTTOM, nullptr);
        if (neighborsConnection) {
            if (x > 0) {
                // std::cout << "horizontal wall: " << x << ", " << y
                //           << " with x > 0" << std::endl;
                if (getWall(x - 1, y, MAZE_CELL_RIGHT) != nullptr) {
                    // std::cout << "horizontal wall: " << x << ", " << y
                    //           << " to vertical wall: " << x - 1 << ", " << y
                    //           << std::endl;
                    wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP,
                                      getWall(x - 1, y, MAZE_CELL_RIGHT));
                    getWall(x - 1, y, MAZE_CELL_RIGHT)
                        ->setNeighbor(MAZE_WALL_END_RIGHT_TOP, wall);
                }
                if (y < height_ - 1) {
                    // std::cout << "horizontal wall: " << x << ", " << y
                    //           << " with y < height_-1" << std::endl;
                    if (getWall(x - 1, y + 1, MAZE_CELL_RIGHT) != nullptr) {
                        // std::cout << "horizontal wall: " << x << ", " << y
                        //           << " to vertical wall: " << x - 1 << ", "
                        //           << y + 1 << std::endl;
                        wall->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM,
                                          getWall(x, y + 1, MAZE_CELL_RIGHT));
                        getWall(x - 1, y + 1, MAZE_CELL_RIGHT)
                            ->setNeighbor(MAZE_WALL_START_RIGHT_TOP, wall);
                    }
                    if (getWall(x - 1, y, MAZE_CELL_BOTTOM) != nullptr) {
                        // std::cout << "horizontal wall: " << x << ", " << y
                        //           << " to horizontal wall: " << x << ", "
                        //           << y + 1 << std::endl;
                        wall->setNeighbor(MAZE_WALL_START,
                                          getWall(x, y + 1, MAZE_CELL_BOTTOM));
                        getWall(x - 1, y, MAZE_CELL_BOTTOM)
                            ->setNeighbor(MAZE_WALL_END, wall);
                    }
                }
            }
            if (x < width_ - 1) {
                // std::cout << "horizontal wall: " << x << ", " << y
                //           << " with x < width_-1" << std::endl;
                if (getWall(x, y, MAZE_CELL_RIGHT) != nullptr) {
                    // std::cout << "horizontal wall: " << x << ", " << y
                    //           << " to vertical wall: " << x + 1 << ", " << y
                    //           + 1
                    //           << std::endl;
                    wall->setNeighbor(MAZE_WALL_END_RIGHT_TOP,
                                      getWall(x, y, MAZE_CELL_RIGHT));
                    getWall(x, y, MAZE_CELL_RIGHT)
                        ->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, wall);
                }
                if (y < height_ - 1) {
                    // std::cout << "horizontal wall: " << x << ", " << y
                    //           << " with y < height_-1" << std::endl;
                    if (getWall(x, y + 1, MAZE_CELL_RIGHT) != nullptr) {
                        // std::cout << "horizontal wall: " << x << ", " << y
                        //           << " to vertical wall: " << x + 1 << ", "
                        //           << y
                        //           << std::endl;
                        wall->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM,
                                          getWall(x, y + 1, MAZE_CELL_RIGHT));
                        getWall(x, y + 1, MAZE_CELL_RIGHT)
                            ->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, wall);
                    }
                    if (getWall(x + 1, y, MAZE_CELL_BOTTOM) != nullptr) {
                        // std::cout << "horizontal wall: " << x << ", " << y
                        //           << " to horizontal wall: " << x << ", "
                        //           << y + 1 << std::endl;
                        wall->setNeighbor(MAZE_WALL_END,
                                          getWall(x, y + 1, MAZE_CELL_BOTTOM));
                        getWall(x + 1, y, MAZE_CELL_BOTTOM)
                            ->setNeighbor(MAZE_WALL_START, wall);
                    }
                }
            }
            if (x == 0 || x == width_ - 1) {
                wall->setBorder(true);
            }
        }
    } else {
        cell->setWall(MAZE_CELL_RIGHT, wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, wall);
        cell->getNeighbor(MAZE_CELL_RIGHT)
            ->setNeighbor(MAZE_CELL_LEFT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT, nullptr);
        if (neighborsConnection) {
            if (y > 0) {
                // std::cout << "vertical wall: " << x << ", " << y
                //           << " with y > 0" << std::endl;
                if (getWall(x, y - 1, MAZE_CELL_BOTTOM) != nullptr) {
                    // std::cout << "vertical wall: " << x << ", " << y
                    //           << " to horizontal wall: " << x << ", " << y
                    //           << std::endl;
                    wall->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM,
                                      getWall(x, y - 1, MAZE_CELL_BOTTOM));
                    getWall(x, y - 1, MAZE_CELL_BOTTOM)
                        ->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, wall);
                }
                if (x < width_ - 1) {
                    // std::cout << "vertical wall: " << x << ", " << y
                    //           << " with x < width_-1" << std::endl;
                    if (getWall(x + 1, y - 1, MAZE_CELL_BOTTOM) != nullptr) {
                        // std::cout << "vertical wall: " << x << ", " << y
                        //           << " to horizontal wall: " << x + 1 << ", "
                        //           << y << std::endl;
                        wall->setNeighbor(
                            MAZE_WALL_START_RIGHT_TOP,
                            getWall(x + 1, y - 1, MAZE_CELL_BOTTOM));
                        getWall(x + 1, y - 1, MAZE_CELL_BOTTOM)
                            ->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, wall);
                    }
                    if (getWall(x, y - 1, MAZE_CELL_RIGHT) != nullptr) {
                        // std::cout << "vertical wall: " << x << ", " << y
                        //           << " to vertical wall: " << x + 1 << ", "
                        //           << y
                        //           << std::endl;
                        wall->setNeighbor(MAZE_WALL_START,
                                          getWall(x + 1, y, MAZE_CELL_RIGHT));
                        getWall(x, y - 1, MAZE_CELL_RIGHT)
                            ->setNeighbor(MAZE_WALL_END, wall);
                    }
                }
            }
            if (y < height_ - 1) {
                // std::cout << "vertical wall: " << x << ", " << y
                //           << " with y < height_-1" << std::endl;
                if (getWall(x, y, MAZE_CELL_BOTTOM) != nullptr) {
                    // std::cout << "vertical wall: " << x << ", " << y
                    //           << " to horizontal wall: " << x << ", " << y +
                    //           1
                    //           << std::endl;
                    wall->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM,
                                      getWall(x, y, MAZE_CELL_BOTTOM));
                    getWall(x, y, MAZE_CELL_BOTTOM)
                        ->setNeighbor(MAZE_WALL_END_RIGHT_TOP, wall);
                }
                if (x < width_ - 1) {
                    // std::cout << "vertical wall: " << x << ", " << y
                    //           << " with x < width_-1" << std::endl;
                    if (getWall(x + 1, y, MAZE_CELL_BOTTOM) != nullptr) {
                        // std::cout << "vertical wall: " << x << ", " << y
                        //           << " to horizontal wall: " << x + 1 << ", "
                        //           << y + 1 << std::endl;
                        wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP,
                                          getWall(x + 1, y, MAZE_CELL_BOTTOM));
                        getWall(x + 1, y, MAZE_CELL_BOTTOM)
                            ->setNeighbor(MAZE_WALL_START_RIGHT_TOP, wall);
                    }
                    if (getWall(x, y + 1, MAZE_CELL_RIGHT) != nullptr) {
                        // std::cout << "vertical wall: " << x << ", " << y
                        //           << " to vertical wall: " << x + 1 << ", "
                        //           << y
                        //           << std::endl;
                        wall->setNeighbor(MAZE_WALL_END,
                                          getWall(x, y, MAZE_CELL_RIGHT));
                        getWall(x, y + 1, MAZE_CELL_RIGHT)
                            ->setNeighbor(MAZE_WALL_START, wall);
                    }
                }
            }
            if (y == 0 || y == height_ - 1) {
                wall->setBorder(true);
            }
        }
    }
    return true;
}

bool Maze::addWall(const Cell *cell1, const Cell *cell2) const {
    if (cell1 == nullptr || cell2 == nullptr) {
        return false;
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
    return false;
}

bool Maze::removeWall(const int x, const int y, const bool horizontal) const {
    return removeWall(x, y, horizontal, false);
}

bool Maze::removeWall(const int x, const int y, const bool horizontal,
                      const bool neighborsConnection) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return false;
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
        if (neighborsConnection) {
            if (x > 0) {
                if (getCell(x - 1, y)->getWall(MAZE_CELL_RIGHT) != nullptr) {
                    wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                    getCell(x - 1, y)
                        ->getWall(MAZE_CELL_RIGHT)
                        ->setNeighbor(MAZE_WALL_END_RIGHT_TOP, nullptr);
                }
                if (y < height_ - 1) {
                    if (getCell(x - 1, y + 1)->getWall(MAZE_CELL_RIGHT) !=
                        nullptr) {
                        wall->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, nullptr);
                        getCell(x - 1, y + 1)
                            ->getWall(MAZE_CELL_RIGHT)
                            ->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                    }
                    if (getCell(x - 1, y)->getWall(MAZE_CELL_BOTTOM) !=
                        nullptr) {
                        wall->setNeighbor(MAZE_WALL_START, nullptr);
                        getCell(x - 1, y)
                            ->getWall(MAZE_CELL_BOTTOM)
                            ->setNeighbor(MAZE_WALL_END, nullptr);
                    }
                }
            }
            if (x < width_ - 1) {
                if (cell->getWall(MAZE_CELL_RIGHT) != nullptr) {
                    wall->setNeighbor(MAZE_WALL_END_RIGHT_TOP, nullptr);
                    getCell(x, y)
                        ->getWall(MAZE_CELL_RIGHT)
                        ->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, nullptr);
                }
                if (y < height_ - 1) {
                    if (getCell(x, y + 1)->getWall(MAZE_CELL_RIGHT) !=
                        nullptr) {
                        wall->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, nullptr);
                        getCell(x, y + 1)
                            ->getWall(MAZE_CELL_RIGHT)
                            ->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, nullptr);
                    }
                    if (getCell(x + 1, y)->getWall(MAZE_CELL_BOTTOM) !=
                        nullptr) {
                        wall->setNeighbor(MAZE_WALL_END, nullptr);
                        getCell(x + 1, y)
                            ->getWall(MAZE_CELL_BOTTOM)
                            ->setNeighbor(MAZE_WALL_START, nullptr);
                    }
                }
            }
        }
    } else {
        wall = cell->getWall(MAZE_CELL_RIGHT);
        cell->setWall(MAZE_CELL_RIGHT, nullptr);
        cell->setNeighbor(MAZE_CELL_RIGHT,
                          cell->getRelativeNeighbor(MAZE_CELL_RIGHT));
        cell->getNeighbor(MAZE_CELL_RIGHT)->setWall(MAZE_CELL_LEFT, nullptr);
        cell->getNeighbor(MAZE_CELL_RIGHT)->setNeighbor(MAZE_CELL_LEFT, cell);
        cell->setNeighbor(MAZE_CELL_RIGHT, cell->getNeighbor(MAZE_CELL_RIGHT));
        if (neighborsConnection) {
            if (y > 0) {
                if (getCell(x, y - 1)->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                    wall->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, nullptr);
                    getCell(x, y - 1)
                        ->getWall(MAZE_CELL_BOTTOM)
                        ->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, nullptr);
                }
                if (x < width_ - 1) {
                    if (getCell(x + 1, y - 1)->getWall(MAZE_CELL_BOTTOM) !=
                        nullptr) {
                        wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                        getCell(x + 1, y - 1)
                            ->getWall(MAZE_CELL_BOTTOM)
                            ->setNeighbor(MAZE_WALL_START_LEFT_BOTTOM, nullptr);
                    }
                    if (getCell(x, y - 1)->getWall(MAZE_CELL_RIGHT) !=
                        nullptr) {
                        wall->setNeighbor(MAZE_WALL_START, nullptr);
                        getCell(x, y - 1)
                            ->getWall(MAZE_CELL_RIGHT)
                            ->setNeighbor(MAZE_WALL_END, nullptr);
                    }
                }
            }
            if (y < height_ - 1) {
                if (cell->getWall(MAZE_CELL_BOTTOM) != nullptr) {
                    wall->setNeighbor(MAZE_WALL_END_LEFT_BOTTOM, nullptr);
                    getCell(x, y)
                        ->getWall(MAZE_CELL_BOTTOM)
                        ->setNeighbor(MAZE_WALL_END_RIGHT_TOP, nullptr);
                }
                if (x < width_ - 1) {
                    if (getCell(x + 1, y)->getWall(MAZE_CELL_BOTTOM) !=
                        nullptr) {
                        wall->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                        getCell(x + 1, y)
                            ->getWall(MAZE_CELL_BOTTOM)
                            ->setNeighbor(MAZE_WALL_START_RIGHT_TOP, nullptr);
                    }
                    if (getCell(x, y + 1)->getWall(MAZE_CELL_RIGHT) !=
                        nullptr) {
                        wall->setNeighbor(MAZE_WALL_END, nullptr);
                        getCell(x, y + 1)
                            ->getWall(MAZE_CELL_RIGHT)
                            ->setNeighbor(MAZE_WALL_START, nullptr);
                    }
                }
            }
        }
    }
    delete wall;
    return true;
}

bool Maze::removeWall(const Cell *cell1, const Cell *cell2) const {
    if (cell1 == nullptr || cell2 == nullptr) {
        return false;
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
    return false;
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
        // for (int i = 0; i < width_; ++i) {
        //     for (int j = 0; j < height_; ++j) {
        //         delete cells_[i][j];
        //         cells_[i][j] = nullptr;
        //     }
        //     delete[] cells_[i];
        //     cells_[i] = nullptr;
        // }
        // delete[] cells_;
        cells_ = nullptr;
    }
    start_[0] = defaultStartX(width_), start_[1] = defaultStartY(height_);
    end_[0] = defaultEndX(width_), end_[1] = defaultEndY(height_);
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
