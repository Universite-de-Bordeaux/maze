#ifndef CELL_HPP
#define CELL_HPP

#include "wall.hpp"

class Cell {
    public:
        Cell();
        Cell(int x, int y);
        Cell(int x, int y, struct Wall walls);
        Cell(const Cell& cell);
        ~Cell();

        int getX() const;
        int getY() const;
        bool getWall(enum WallType) const;
        struct Wall getWalls() const;

        void setX(int x);
        void setY(int y);
        bool setWall(enum WallType, bool);
        bool setWalls(struct Wall walls);

    private:
        int x;
        int y;
        struct Wall walls;

        bool isPrisoner() const;
};

#endif // CELL_H
