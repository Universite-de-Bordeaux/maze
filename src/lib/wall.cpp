#include "wall.hpp"

Wall::Wall() : Wall(true) {};

Wall::Wall(const bool horizontal) {
    isHorizontal_ = horizontal;
    alreadyVisited_ = false;
}

Wall::~Wall() = default;

bool Wall::getIsHorizontal() const { return isHorizontal_; }

bool Wall::isAlreadyVisited() const { return alreadyVisited_; }

void Wall::setIsHorizontal(const bool horizontal) {
    isHorizontal_ = horizontal;
}

void Wall::setAlreadyVisited(const bool visited) { alreadyVisited_ = visited; }