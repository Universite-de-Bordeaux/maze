#include "breadth_first.hpp"

#include <chrono>
#include <iostream>
#include <queue>
#include <thread>

#include "../show.hpp"
#include "../var.hpp"
#include "../queue.hpp"
#include "../stack.hpp"

bool solver_breadth_first(Maze *maze, Show *show) {
    std::cout << "Résolution du labyrinthe en largeur" << std::endl;
    Queue queue;
    Stack stack;
    if (maze->getStartCell() == nullptr || maze->getEndCell() == nullptr) {
        return false;
    }
    refreshShow(show);
    position start = {maze->getStartX(), maze->getStartY()};
    queue.push(&start);
    positionHistory startHistory = {maze->getStartX(), maze->getStartY(), -1, -1};
    stack.push(&startHistory);
    maze->getStartCell()->setStatus(MAZE_STATUS_VISITED);
    maze->getStartCell()->setAlreadyVisited(true);
    while (!queue.empty()) {
        position *current = (position *)queue.front();
        queue.pop();
        int x = current->x;
        int y = current->y;
        Cell *cell = maze->getCell(x, y);
        refreshShow(show, 1, &cell);
        for (int i = 0; i < 4; i++) {
            Cell *neighbor = cell->getNeighbor(i);
            if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                position *neighborPosition = new position;
                neighborPosition->x = neighbor->getX();
                neighborPosition->y = neighbor->getY();
                queue.push(neighborPosition);
                positionHistory *neighborHistory = new positionHistory;
                neighborHistory->x = neighbor->getX();
                neighborHistory->y = neighbor->getY();
                neighborHistory->parent_x = x;
                neighborHistory->parent_y = y;
                stack.push(neighborHistory);
                neighbor->setStatus(MAZE_STATUS_VISITED);
                neighbor->setAlreadyVisited(true);
                if (neighbor->getX() == maze->getEndX() &&
                    neighbor->getY() == maze->getEndY()) {
                    neighbor->setStatus(MAZE_STATUS_WAY_OUT);
                    refreshShow(show, 1, &neighbor);
                    while (!stack.empty()) {
                        positionHistory *currentCell = (positionHistory*)stack.top();
                        positionHistory *cellTop = (positionHistory*)stack.top();
                        while (!stack.empty() &&
                               (cellTop->x != currentCell->parent_x ||
                                cellTop->y != currentCell->parent_y)) {
                            stack.pop();
                            cellTop = (positionHistory*)stack.top();
                        }
                        if (stack.empty()) {
                            break;
                        }
                        cell = maze->getCell(cellTop->x, cellTop->y);
                        if (cell != nullptr) {
                            cell->setStatus(MAZE_STATUS_WAY_OUT);
                            refreshShow(show, 1, &cell);
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
