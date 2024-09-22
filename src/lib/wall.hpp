#ifndef WALL_HPP
#define WALL_HPP

struct Wall {
    bool top = false;
    bool bottom = false;
    bool left = false;
    bool right = false;
};

enum WallType {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

#endif
