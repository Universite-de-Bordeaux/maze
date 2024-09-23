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

void setWidth(int width) {
    this->width = width;
}

void setHeight(int height) {
    this->height = height;
}
