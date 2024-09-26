#include "maze.hpp"
#include <cstdlib>
#include <iostream>


Maze::Maze() {
    Maze(0, 0);
}

Maze::Maze(int n, int m) {
    this->width = n;
    this->height = m;
    this->regenerateMat();
}

// Maze::~Maze() {
//     setMat(getMat(), NULL);
// }

// int Maze::getWidth() const {
//     return this->width;
// }

// int Maze::getHeight() const {
//     return this->height;
// }

// Cell **Maze::getMat() const {
//     return this->mat;
// }

// void Maze::setCell(int i, int j, enum WallType wall) {
//     switch (wall) {
//         case WallType::RIGHT:
//             (*(*(this->mat+i)+j)).setWall(wall, 1);
//             std::cout << "test2" << std::endl;
//             (*(*(this->mat+i)+j+1)).setWall(LEFT, 1);
//         case WallType::BOTTOM:
//             (*(*(this->mat+i)+j)).setWall(wall, 1);
//             std::cout << "test2" << std::endl;
//             (*(*(this->mat+i+1)+j)).setWall(TOP, 1);
//         case WallType::LEFT:
//             std::cerr << "Direction invalide" << std::endl;
//         case WallType::TOP:
//             std::cerr << "Direction invalide" << std::endl;
//     }
// }

// void Maze::removeWall(int i, int j, enum WallType wall) {
//     switch (wall) {
//         case WallType::RIGHT:
//             (*(*(this->mat+i)+j)).setWall(wall, 0);
//             (*(*(this->mat+i)+j+1)).setWall(LEFT, 0);
//         case WallType::BOTTOM:
//             (*(*(this->mat+i)+j)).setWall(wall, 0);
//             (*(*(this->mat+i+1)+j)).setWall(TOP, 0);
//         case WallType::LEFT:
//             std::cerr << "Direction invalide" << std::endl;
//         case WallType::TOP:
//             std::cerr << "Direction invalide" << std::endl;
//     }
// }


void Maze::setWidth(int width) {
    this->width = width;
    this->regenerateMat();
}

void Maze::setHeight(int height) {
    this->height = height;
    this->regenerateMat();
}

void Maze::setWidthHeight(int width, int height) {
    this->width = width;
    this->height = height;
    this->regenerateMat();
}

void Maze::setMat(Cell **mat, Cell **new_mat) {
    mat = new_mat;
}

void Maze::regenerateMat() {
    if(this->mat != nullptr) {
        free(this->mat);
    }
    this->mat = (Cell**)malloc(this->height*this->width*sizeof(Cell*));
}
