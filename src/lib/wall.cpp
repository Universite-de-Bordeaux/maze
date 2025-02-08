#include "wall.hpp"

Wall::Wall() : Wall(true){};

Wall::Wall(const bool horizontal) {
    isHorizontal_ = horizontal;
    alreadyVisited_ = false;
}

Wall::~Wall() = default;

bool Wall::getIsHorizontal() const { return isHorizontal_; }

Wall **Wall::getNeighbors() { return neighbors_; }

Wall *Wall::getNeighbor(int i) const {
    if (i < 0 || i > 5) return nullptr;
    return neighbors_[i];
}

bool Wall::isAlreadyVisited() const { return alreadyVisited_; }

bool Wall::isBorder() const { return isBorder_; }

void Wall::setIsHorizontal(const bool horizontal) {
    isHorizontal_ = horizontal;
}

void Wall::setNeighbors(Wall *neighbors[6]) {
    for (int i = 0; i < 6; i++) {
        neighbors_[i] = neighbors[i];
    }
}

void Wall::setNeighbor(const int i, Wall *wall) {
    if (i < 0 || i > 5) return;
    neighbors_[i] = wall;
}

void Wall::setAlreadyVisited(const bool visited) { alreadyVisited_ = visited; }

void Wall::setBorder(const bool isBorder) { isBorder_ = isBorder; }