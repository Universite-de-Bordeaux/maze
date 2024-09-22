#ifndef MAZE_HPP
#define MAZE_HPP

#include <string>

class Maze {
    public:
        Maze(std::string filename);
        void print();
        void solve();
        void printSolution();
};

#endif // MAZE_HPP
