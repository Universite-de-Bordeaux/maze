#include <queue>
#include <iostream>

#include "solver_breadthfirst.hpp"
#include "../show.hpp"
#include "../var.hpp"

struct Position {
    int x, y, direction;
};

static bool solver_bfs(Maze *maze, Show *show, bool toLeft) {
    std::queue<Position> q;
    Cell *startCell = maze->getCell(maze->getStartX(), maze->getStartY());
    startCell->setAlreadyVisited(true);
    startCell->setStatus(MAZE_STATUS_CURRENT);

    q.push({maze->getStartX(), maze->getStartY(), 0});
    updateShowLive(show, maze, 1, &startCell);

    while (!q.empty()) {
        refreshShow(show);
        Position pos = q.front();
        q.pop();
        Cell *cell = maze->getCell(pos.x, pos.y);
        if (pos.x == maze->getEndX() && pos.y == maze->getEndY()) {
            cell->setStatus(MAZE_STATUS_WAY_OUT);
            updateShowLive(show, maze, 1, &cell);
            return true;
        }

        // Exploration des voisins
        for (int i = 0; i < 4; i++) {
            int index = (toLeft) ? (pos.direction + i) % 4 : (pos.direction - i) % 4;
            if (index < 0) {
                index += 4;
            }
            if (cell->isNeighbor(index)) {
                Cell *neighbor = cell->getNeighbor(index);
                if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
                    neighbor->setAlreadyVisited(true);
                    neighbor->setStatus(MAZE_STATUS_HOPELESS);
                    updateShowLive(show, maze, 1, &neighbor);

                    q.push({neighbor->getX(), neighbor->getY(), (index + 2) % 4});

                    cell->setStatus(MAZE_STATUS_VISITED);
                    updateShowLive(show, maze, 1, &cell);
                }
            }
        }
    }
    return false;
}

bool solver_breadthfirst(Maze *maze, Show *show) {
    updateShowLive(show, maze);
    std::cout << "Résolution du labyrinthe en largeur" << std::endl;
    return solver_bfs(maze, show, true);
}
