#include "cell.hpp"

// Cell::Cell() {
//     this->x = 0;
//     this->y = 0;
//     this->walls = WallStruct();
// }

// Cell::Cell(int x, int y) {
//     this->x = x;
//     this->y = y;
//     this->walls = WallStruct();
// }

// Cell::Cell(int x, int y, struct WallStruct walls) {
//     this->x = x;
//     this->y = y;
//     this->walls = WallStruct();
//     setWalls(walls);
// }

// Cell::Cell(const Cell &cell) {
//     Cell(cell.x, cell.y, cell.walls);
// }

// Cell::~Cell() {
// }

// int Cell::getX() const {
//     return this->x;
// }

// int Cell::getY() const {
//     return this->y;
// }

// bool Cell::getWall(enum WallType type) const {
//     switch (type) {
//         case WallType::TOP:
//             return this->walls.top;
//         case WallType::RIGHT:
//             return this->walls.right;
//         case WallType::BOTTOM:
//             return this->walls.bottom;
//         case WallType::LEFT:
//             return this->walls.left;
//     }
//     return false;
// }

// struct WallStruct Cell::getWalls() const {
//     return walls;
// }

// void Cell::setX(int x) {
//     this->x = x;
// }

// void Cell::setY(int y) {
//     this->y = y;
// }

// bool Cell::setWall(enum WallType type, bool value) {
//     switch (type) {
//         case WallType::TOP:
//             walls.top = value;
//             break;
//         case WallType::RIGHT:
//             walls.right = value;
//             break;
//         case WallType::BOTTOM:
//             walls.bottom = value;
//             break;
//         case WallType::LEFT:
//             walls.left = value;
//             break;
//     }
//     // verifie que cette cellule n'est pas prisonnière
//     // si elle l'est, on ne peut pas la modifier
//     if (isPrisoner()) {
//         setWall(type, !value);
//         return false;
//     }
//     return true;
// }

// bool Cell::setWalls(struct WallStruct walls) {
//     struct WallStruct oldWalls = this->walls;
//     this->walls = walls;
//     // verifie que cette cellule n'est pas prisonnière
//     // si elle l'est, on ne peut pas la modifier
//     if (isPrisoner()) {
//         this->walls = oldWalls;
//         return false;
//     }
//     return true;
// }

// bool Cell::isPrisoner() const {
//     return walls.top && walls.right && walls.bottom && walls.left;
// }

Cell::Cell() {
    Cell(0, 0);
}

Cell::Cell(int x, int y) {
    this->x = x;
    this->y = y;
}
