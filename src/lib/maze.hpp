#ifndef MAZE_HPP
#define MAZE_HPP

#include "cell.hpp"
#include "wall.hpp"
#include <string>

class Maze {
    public:
        Maze();
        Maze(int n);
        Maze(std::string filename);
        ~Maze();

        int getWidth() const;
        int getHeight() const;
        Cell ** getMat() const;

        // void setCell(int, int, enum WallType);
        void setMat(Cell **, Cell **);
        // void removeWall(int, int, enum WallType);
        void setWidth(int);
        void setHeight(int);

    private:
        int width;
        int height;
        Cell **mat;
};

#endif // MAZE_HPP
