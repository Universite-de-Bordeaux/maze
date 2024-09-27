#ifndef WALL_HPP
#define WALL_HPP

class Wall {
    public:
        enum NeighborsEnum {
            START_RIGHT_TOP = 0 ,
            START = 1,
            START_LEFT_BOTTOM = 2,
            END_RIGHT_TOP = 3,
            END = 4,
            END_LEFT_BOTTOM = 5
        };

        Wall();
        Wall(bool isHorizontal);
        ~Wall();

        bool getIsHorizontal() const;
        Wall** getNeighbors();
        Wall* getNeighbor(NeighborsEnum);

        void setIsHorizontal(bool);
        void setNeighbors(Wall*[6]);
        void setNeighbor(NeighborsEnum, Wall*);

    private:
        bool isHorizontal;
        Wall* neighbors[6];

};

#endif
