#include <queue>
#include <iostream>
#include <thread>
#include <chrono>

#include "solver_breadthfirst.hpp"
#include "../show.hpp"
#include "../var.hpp"

struct Position {
    int x;
    int y;
    int parentX;
    int parentY;
};
Position *position;

class QueuePosition {
    private:
        int size_;
        int capacity_;
    public:
        QueuePosition() {
            size_ = 0;
            capacity_ = 1;
            position = new Position[1];
        }
        ~QueuePosition() {
            delete[] position;
        }
        void push(int x, int y, int parentX, int parentY) {
            if (size_ == capacity_) {
                Position *newPosition = new Position[capacity_*2];
                for (int i = 0; i < size_; i++) {
                    newPosition[i] = position[i];
                }
                delete[] position;
                position = newPosition;
                capacity_ *= 2;
            }
            position[size_].x = x;
            position[size_].y = y;
            position[size_].parentX = parentX;
            position[size_].parentY = parentY;
            size_++;
        }
        void pop() {
            if (size_ < capacity_/4) {
                Position *newPosition = new Position[capacity_/2];
                for (int i = 0; i < size_; i++) {
                    newPosition[i] = position[i];
                }
                delete[] position;
                position = newPosition;
                capacity_ /= 2;
            }
            if (size_ > 0) {
                for (int i = 0; i < size_-1; i++) {
                    position[i] = position[i+1];
                }
                size_--;
            }
        }
        Position front() {
            return position[0];
        }
        bool empty() {
            return size_ == 0;
        }
};

bool solver_bfs(Maze *maze, Show *show, QueuePosition &queue) {
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }
    queue.push(maze->getStartX(), maze->getStartY(), -1, -1);
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    while (!queue.empty()) {
        Position current = queue.front();
        queue.pop();
        int x = current.x;
        int y = current.y;
        Cell *cell = maze->getCell(x, y);
        if (cell->getX() == maze->getEndX() && cell->getY() == maze->getEndY()) {
            cell->setStatus(MAZE_STATUS_WAY_OUT);
            updateShowLive(show, maze);
            return true;
        }
        updateShowLive(show, maze);
        for (int i = 0; i < 4; i++) {
            Cell *neighbor = cell->getNeighbor(i);
            if (neighbor != nullptr && neighbor->getStatus() == MAZE_STATUS_IDLE) {
                queue.push(neighbor->getX(), neighbor->getY(), x, y);
                neighbor->setStatus(MAZE_STATUS_VISITED);
            }
        }
    }
    return false;
}

bool solver_breadthfirst(Maze *maze, Show *show) {
    updateShowLive(show, maze);
    std::cout << "Résolution du labyrinthe en largeur" << std::endl;
    QueuePosition queue;
    return solver_bfs(maze, show, queue);
}
