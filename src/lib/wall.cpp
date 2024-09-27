#include "wall.hpp"

Wall::Wall() {
    Wall(true);
}

Wall::Wall(bool isHorizontal) {
    this->isHorizontal = isHorizontal;
}

Wall::~Wall() {
    //dtor
}

bool Wall::getIsHorizontal() const {
    return this->isHorizontal;
}

Wall** Wall::getNeighbors() {
    return this->neighbors;
}

Wall* Wall::getNeighbor(NeighborsEnum neighbor) {
    return this->neighbors[neighbor];
}

void Wall::setIsHorizontal(bool isHorizontal) {
    this->isHorizontal = isHorizontal;
}

void Wall::setNeighbors(Wall* neighbors[6]) {
    for(int i = 0; i < 6; i++) {
        this->neighbors[i] = neighbors[i];
    }
}

void Wall::setNeighbor(NeighborsEnum neighbor, Wall* wall) {
    this->neighbors[neighbor] = wall;
}
