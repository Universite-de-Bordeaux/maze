#include "wall.hpp"
#include <iostream>

Wall::Wall() {
    Wall(true);
}

Wall::Wall(bool isHorizontal) {
    isHorizontal_ = isHorizontal;
    alreadyVisited_ = false;
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

bool Wall::isAlreadyVisited() {
    return alreadyVisited_;
}

bool Wall::isBorder() {
    return isBorder_;
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

void Wall::setAlreadyVisited(bool alreadyVisited) {
    std::cout << "setAlreadyVisited : " << alreadyVisited << std::endl;
    alreadyVisited_ = alreadyVisited;
}

void Wall::setBorder(bool isBorder) {
    isBorder_ = isBorder;
}