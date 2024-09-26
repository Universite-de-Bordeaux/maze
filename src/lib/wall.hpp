#ifndef WALL_HPP
#define WALL_HPP

// struct WallStruct {
//     bool top = false;
//     bool bottom = false;
//     bool left = false;
//     bool right = false;
// };

// enum WallType {
//     TOP,
//     BOTTOM,
//     LEFT,
//     RIGHT
// };

class Wall {
    public:
        Wall();
        Wall(bool isHorizontal);

    private:
        bool isHorizontal;
        struct neighbors {
            Wall* startRightTop;
            Wall* start;
            Wall* startLeftBottom;
            Wall* endRightTop;
            Wall* end;
            Wall* endLeftBottom;
        } neighbors;

};

#endif
