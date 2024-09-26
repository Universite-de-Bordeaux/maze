#ifndef CELL_HPP
#define CELL_HPP

#include "wall.hpp"

// class Cell {
//     public:
//         Cell();
//         Cell(int x, int y);
//         Cell(int x, int y, struct WallStruct walls);
//         Cell(const Cell& cell);
//         ~Cell();

//         int getX() const;
//         int getY() const;
//         bool getWall(enum WallType) const;
//         struct WallStruct getWalls() const;

//         void setX(int x);
//         void setY(int y);
//         bool setWall(enum WallType, bool);
//         bool setWalls(struct WallStruct walls);

//     private:
//         int x;
//         int y;
//         struct WallStruct walls;

//         bool isPrisoner() const;
// };

enum indexClockwise {
    TOP = 0,
    RIGHT = 1,
    BOTTOM = 2,
    LEFT = 3
};

class Cell {
    Cell();
    Cell(int x, int y);

    public:
        int x, y;
        Wall *walls[4];
        Cell *neighbors[4];
};

#endif // CELL_H
