#include "wall.hpp"

Wall::Wall() {
    Wall(true);
}

Wall::Wall(bool isHorizontal) {
    this->isHorizontal = isHorizontal;
}
