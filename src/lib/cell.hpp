#ifndef CELL_HPP
#define CELL_HPP

#include "wall.hpp"

class Cell {
    public:
        enum NeighborsEnum {
            TOP = 0,
            RIGHT = 1,
            BOTTOM = 2,
            LEFT = 3
        };

        Cell();
        Cell(int x, int y);
        ~Cell();

        int getX() const;
        int getY() const;
        Cell** getNeighbors();
        Cell* getNeighbor(NeighborsEnum);
        Wall** getWalls();
        Wall* getWall(NeighborsEnum);

        void setX(int x);
        void setY(int y);
        void setXY(int x, int y);
        void setNeighbors(Cell*[4]);
        void setNeighbor(NeighborsEnum, Cell*);
        void setWalls(Wall*[4]);
        void setWall(NeighborsEnum, Wall*);

    private:
        int x, y;
        Wall *walls[4];
        Cell *neighbors[4];
};

#endif // CELL_H
