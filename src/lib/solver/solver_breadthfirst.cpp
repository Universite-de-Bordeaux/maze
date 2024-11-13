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
};
Position *position;

struct PositionHistory {
    int x;
    int y;
    int parent_x;
    int parent_y;
};
PositionHistory *positionHistory;

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
        void push(int x, int y) {
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

class stackPosition {
    private:
        int size_;
        int capacity_;
    public:
        stackPosition() {
            size_ = 0;
            capacity_ = 1;
            positionHistory = new PositionHistory[1];
        }
        ~stackPosition() {
            delete[] positionHistory;
        }
        void push(int x, int y, int parent_x, int parent_y) {
            if (size_ == capacity_) {
                PositionHistory *newPositionHistory = new PositionHistory[capacity_*2];
                for (int i = 0; i < size_; i++) {
                    newPositionHistory[i] = positionHistory[i];
                }
                delete[] positionHistory;
                positionHistory = newPositionHistory;
                capacity_ *= 2;
            }
            positionHistory[size_].x = x;
            positionHistory[size_].y = y;
            positionHistory[size_].parent_x = parent_x;
            positionHistory[size_].parent_y = parent_y;
            size_++;
        }
        void pop() {
            if (size_ < capacity_/4) {
                PositionHistory *newPositionHistory = new PositionHistory[capacity_/2];
                for (int i = 0; i < size_; i++) {
                    newPositionHistory[i] = positionHistory[i];
                }
                delete[] positionHistory;
                positionHistory = newPositionHistory;
                capacity_ /= 2;
            }
            if (size_ > 0) {
                size_--;
            }
        }
        PositionHistory top() {
            return positionHistory[size_-1];
        }
        bool empty() {
            return size_ == 0;
        }
};

bool solver_breadthfirst(Maze *maze, Show *show) {
    updateShowLive(show, maze);
    std::cout << "Résolution du labyrinthe en largeur" << std::endl;
    QueuePosition queue;
    stackPosition stack;
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }
    queue.push(maze->getStartX(), maze->getStartY());
    stack.push(maze->getStartX(), maze->getStartY(), -1, -1);
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    while (!queue.empty()) {
        Position current = queue.front();
        queue.pop();
        int x = current.x;
        int y = current.y;
        Cell *cell = maze->getCell(x, y);
        updateShowLive(show, maze);
        for (int i = 0; i < 4; i++) {
            Cell *neighbor = cell->getNeighbor(i);
            if (neighbor != nullptr && neighbor->getStatus() == MAZE_STATUS_IDLE) {
                queue.push(neighbor->getX(), neighbor->getY());
                stack.push(neighbor->getX(), neighbor->getY(), x, y);
                neighbor->setStatus(MAZE_STATUS_VISITED);
                if (neighbor->getX() == maze->getEndX() && neighbor->getY() == maze->getEndY()) {
                    neighbor->setStatus(MAZE_STATUS_WAY_OUT);
                    updateShowLive(show, maze);
                    while (!stack.empty()) {
                        PositionHistory currentCell = stack.top();
                        PositionHistory cellTop = stack.top();
                        while (!stack.empty() && (cellTop.x != currentCell.parent_x || cellTop.y != currentCell.parent_y)) {
                            stack.pop();
                            cellTop = stack.top();
                        }
                        if (stack.empty()) {
                            break;
                        }
                        cell = maze->getCell(cellTop.x, cellTop.y);
                        if (cell != nullptr) {
                            cell->setStatus(MAZE_STATUS_WAY_OUT);
                            updateShowLive(show, maze);
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
