#include <string>

class Maze {
public:
    Maze(std::string filename);
    void print();
    void solve();
    void printSolution();
};
