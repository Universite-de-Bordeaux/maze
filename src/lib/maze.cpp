#include "maze.hpp"
#include "wall.hpp"
#include <iostream>

Maze::Maze() {
    Maze(0);
}

Maze::Maze(int n) {
    this->width = n;
    this->height = n;
}

Maze::~Maze() {
    setMat(getMat(), NULL);
}

int Maze::getWidth() const {
    return this->width;
}

int Maze::getHeight() const {
    return this->height;
}

Cell **Maze::getMat() const {
    return this->mat;
}

void Maze::setCell(int i, int j, enum WallType wall) {
    switch (wall) {
        case WallType::RIGHT:
            (*(*(this->mat+i)+j)).setWall(wall, 1);
            (*(*(this->mat+i)+j+1)).setWall(LEFT, 1);
        case WallType::BOTTOM:
            (*(*(this->mat+i)+j)).setWall(wall, 1);
            (*(*(this->mat+i+1)+j)).setWall(TOP, 1);
        case WallType::LEFT:
            std::cerr << "Direction invalide" << std::endl;
        case WallType::TOP:
            std::cerr << "Direction invalide" << std::endl;
    }
}

void Maze::removeWall(int i, int j, enum WallType wall) {
    switch (wall) {
        case WallType::RIGHT:
            (*(*(this->mat+i)+j)).setWall(wall, 0);
            (*(*(this->mat+i)+j+1)).setWall(LEFT, 0);
        case WallType::BOTTOM:
            (*(*(this->mat+i)+j)).setWall(wall, 0);
            (*(*(this->mat+i+1)+j)).setWall(TOP, 0);
        case WallType::LEFT:
            std::cerr << "Direction invalide" << std::endl;
        case WallType::TOP:
            std::cerr << "Direction invalide" << std::endl;
    }
}

void Maze::setWidth(int width) {
    this->width = width;
}

void Maze::setHeight(int height) {
    this->height = height;
}

void Maze::setMat(Cell **mat, Cell **new_mat) {
    mat = new_mat;
}
