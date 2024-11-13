#include <iostream>

#include "wall.hpp"

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
    if (i < 0 || i > 5) return nullptr;
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
    if (i < 0 || i > 5) return;
    neighbors_[i] = wall;
}

void Wall::setAlreadyVisited(bool alreadyVisited) {
    alreadyVisited_ = alreadyVisited;
}

void Wall::setBorder(bool isBorder) {
    isBorder_ = isBorder;
}