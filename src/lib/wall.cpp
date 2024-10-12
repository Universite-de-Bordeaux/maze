#include "wall.hpp"

Wall::Wall() {
    Wall(true);
}

Wall::Wall(bool isHorizontal) {
    isHorizontal_ = isHorizontal;
}

Wall::~Wall() {
    //dtor
}

bool Wall::getIsHorizontal() const {
    return isHorizontal_;
}

Wall** Wall::getNeighbors() {
    return neighbors_;
}

Wall* Wall::getNeighbor(int i) {
    return neighbors_[i];
}

void Wall::setIsHorizontal(bool isHorizontal) {
    isHorizontal_ = isHorizontal;
}

void Wall::setNeighbors(Wall* neighbors[6]) {
    for(int i = 0; i < 6; i++) {
        neighbors_[i] = neighbors[i];
    }
}

void Wall::setNeighbor(int i, Wall* wall) {
    neighbors_[i] = wall;
}
