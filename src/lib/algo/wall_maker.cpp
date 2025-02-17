#include "wall_maker.hpp"

#include <iostream>

#include "../checker/depth_first.hpp"
#include "../queue.hpp"
#include "../show.hpp"
#include "../stack.hpp"

struct wall_maker {
    int x;
    int y;
    bool horizontal;
};

static int getNbNeighbors(const Maze* maze, const wall_maker* wall) {
    int nbNeighbors = 0;
    if (wall->horizontal) {
        if (maze->getWall(wall->x - 1, wall->y, true) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x - 1, wall->y, false) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x, wall->y, false) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x - 1, wall->y + 1, false) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr)
            nbNeighbors++;
    } else {
        if (maze->getWall(wall->x, wall->y - 1, false) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x, wall->y - 1, true) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x, wall->y, true) != nullptr) nbNeighbors++;
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x + 1, wall->y - 1, true) != nullptr)
            nbNeighbors++;
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr) nbNeighbors++;
    }
    return nbNeighbors;
}

static int getNbNeighborsNotVisited(const Maze* maze, const wall_maker* wall) {
    int nbNeighborsNotVisited = 0;
    if (wall->horizontal) {
        if (maze->getWall(wall->x - 1, wall->y, true) != nullptr &&
            !maze->getWall(wall->x - 1, wall->y, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x - 1, wall->y, false) != nullptr &&
            !maze->getWall(wall->x - 1, wall->y, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y, false) != nullptr &&
            !maze->getWall(wall->x, wall->y, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr &&
            !maze->getWall(wall->x + 1, wall->y, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x - 1, wall->y + 1, false) != nullptr &&
            !maze->getWall(wall->x - 1, wall->y + 1, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr &&
            !maze->getWall(wall->x, wall->y + 1, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
    } else {
        if (maze->getWall(wall->x, wall->y - 1, false) != nullptr &&
            !maze->getWall(wall->x, wall->y - 1, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y - 1, true) != nullptr &&
            !maze->getWall(wall->x, wall->y - 1, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y, true) != nullptr &&
            !maze->getWall(wall->x, wall->y, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr &&
            !maze->getWall(wall->x, wall->y + 1, false)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x + 1, wall->y - 1, true) != nullptr &&
            !maze->getWall(wall->x + 1, wall->y - 1, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr &&
            !maze->getWall(wall->x + 1, wall->y, true)->isAlreadyVisited())
            nbNeighborsNotVisited++;
    }
    return nbNeighborsNotVisited;
}

static void getNeighbors(const Maze* maze, const wall_maker* wall,
                         wall_maker* neighbors) {
    int count = 0;
    if (wall->horizontal) {
        if (maze->getWall(wall->x - 1, wall->y, true) != nullptr) {
            neighbors[count] = {wall->x - 1, wall->y, true};
            count++;
        }
        if (maze->getWall(wall->x - 1, wall->y, false) != nullptr) {
            neighbors[count] = {wall->x - 1, wall->y, false};
            count++;
        }
        if (maze->getWall(wall->x, wall->y, false) != nullptr) {
            neighbors[count] = {wall->x, wall->y, false};
            count++;
        }
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr) {
            neighbors[count] = {wall->x + 1, wall->y, true};
            count++;
        }
        if (maze->getWall(wall->x - 1, wall->y + 1, false) != nullptr) {
            neighbors[count] = {wall->x - 1, wall->y + 1, false};
            count++;
        }
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr) {
            neighbors[count] = {wall->x, wall->y + 1, false};
        }
    } else {
        if (maze->getWall(wall->x, wall->y - 1, false) != nullptr) {
            neighbors[count] = {wall->x, wall->y - 1, false};
            count++;
        }
        if (maze->getWall(wall->x, wall->y - 1, true) != nullptr) {
            neighbors[count] = {wall->x, wall->y - 1, true};
            count++;
        }
        if (maze->getWall(wall->x, wall->y, true) != nullptr) {
            neighbors[count] = {wall->x, wall->y, true};
            count++;
        }
        if (maze->getWall(wall->x, wall->y + 1, false) != nullptr) {
            neighbors[count] = {wall->x, wall->y + 1, false};
            count++;
        }
        if (maze->getWall(wall->x + 1, wall->y - 1, true) != nullptr) {
            neighbors[count] = {wall->x + 1, wall->y - 1, true};
            count++;
        }
        if (maze->getWall(wall->x + 1, wall->y, true) != nullptr) {
            neighbors[count] = {wall->x + 1, wall->y, true};
        }
    }
}

void processNeighbor(const Maze* maze, Queue& queue, Stack& stack, const int x,
                     const int y, const bool horizontal, int& nbBorders,
                     int& j) {
    Wall* neighbor = maze->getWall(x, y, horizontal);
    if (neighbor != nullptr && !neighbor->isAlreadyVisited()) {
        neighbor->setAlreadyVisited(true);
        if ((horizontal && (x == 0 || x == maze->getWidth() - 1)) ||
            (!horizontal && (y == 0 || y == maze->getHeight() - 1))) {
            nbBorders++;
        }
        auto* wall = new wall_maker;
        wall->x = x;
        wall->y = y;
        wall->horizontal = horizontal;
        queue.push(wall);
        stack.push(wall);
        j++;
    }
}

static void validWall(const Maze* maze, wall_maker* wall, int& nbBorders,
                      int& nbLoops) {
    if (wall == nullptr ||
        maze->getWall(wall->x, wall->y, wall->horizontal) == nullptr) {
        nbBorders = 0;
        return;
    }
    Wall* current = maze->getWall(wall->x, wall->y, wall->horizontal);
    Queue queue;
    Stack stack;
    queue.push(wall);
    stack.push(wall);
    current->setAlreadyVisited(true);
    if ((wall->horizontal &&
         (wall->x == 0 || wall->x == maze->getWidth() - 1)) ||
        (!wall->horizontal &&
         (wall->y == 0 || wall->y == maze->getHeight() - 1))) {
        nbBorders++;
    }
    while (!queue.empty() && nbBorders < 2 && nbLoops < 1) {
        wall = static_cast<wall_maker*>(queue.front());
        queue.pop();
        int j = 0;
        const int nbNeighbors = getNbNeighbors(maze, wall);
        wall_maker neighbors[nbNeighbors];
        getNeighbors(maze, wall, neighbors);
        const int nbNeighborsNotVisited = getNbNeighborsNotVisited(maze, wall);
        for (int i = 0; i < nbNeighbors; i++) {
            processNeighbor(maze, queue, stack, neighbors[i].x, neighbors[i].y,
                            neighbors[i].horizontal, nbBorders, j);
        }
        if (nbNeighbors - nbNeighborsNotVisited >= 3 ||
            (nbNeighbors == 2 && nbNeighborsNotVisited == 0)) {
            nbLoops++;
        }
    }
    while (!queue.empty()) {
        queue.pop();
    }
    while (!stack.empty()) {
        wall = static_cast<wall_maker*>(stack.top());
        stack.pop();
        Wall* current_tmp = maze->getWall(wall->x, wall->y, wall->horizontal);
        if (current_tmp != nullptr) {
            current_tmp->setAlreadyVisited(false);
        }
    }
}
struct double_cell {
    Cell* cell1;
    Cell* cell2;
};

void processStackRecursive(const Maze* maze, const Stack& stackDoubleCell,
                           bool& isValid, bool& isPerfect,
                           const int currentIndex) {
    if (currentIndex >= stackDoubleCell.size()) {
        return;
    }

    // Tente d'ajouter les prochains murs
    for (int j = 0; j < 10 && currentIndex + j < stackDoubleCell.size(); j++) {
        const auto* doubleCell =
            static_cast<double_cell*>(stackDoubleCell.get(currentIndex + j));
        maze->addWall(doubleCell->cell1, doubleCell->cell2);
    }

    // Vérifie la validité
    checker_depth_first(maze, true, false, nullptr, &isValid, &isPerfect);
    maze->clearMaze();

    if (isValid) {
        // Si c'est valid, on avance de 10
        processStackRecursive(maze, stackDoubleCell, isValid, isPerfect,
                              currentIndex + 10);
        return;
    }

    // Si non valid, retire les 10 murs
    for (int j = 0; j < 10 && currentIndex + j < stackDoubleCell.size(); j++) {
        const auto* doubleCell =
            static_cast<double_cell*>(stackDoubleCell.get(currentIndex + j));
        maze->removeWall(doubleCell->cell1, doubleCell->cell2);
    }

    // Ajoute à nouveau le premier mur
    if (currentIndex < stackDoubleCell.size()) {
        const auto* doubleCell =
            static_cast<double_cell*>(stackDoubleCell.get(currentIndex));
        maze->addWall(doubleCell->cell1, doubleCell->cell2);
    }

    // Vérifie à nouveau
    checker_depth_first(maze, true, false, nullptr, &isValid, &isPerfect);
    maze->clearMaze();

    if (!isValid) {
        // Si toujours non valid, retire le mur
        const auto* doubleCell =
            static_cast<double_cell*>(stackDoubleCell.get(currentIndex));
        maze->removeWall(doubleCell->cell1, doubleCell->cell2);
    }

    // Passe au prochain index
    processStackRecursive(maze, stackDoubleCell, isValid, isPerfect,
                          currentIndex + 1);
}

void algo_wall_maker(Maze* maze, const int width, const int height,
                     const bool perfect, const double probability, Show* show) {
    maze->setWidthHeight(width, height);
    if (show) {
        show->create();
    }
    refreshShow(show);
    Stack stack;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int i = 0; i < 2; i++) {
                if (i == 0 && x < width - 1) {
                    auto* wall = new wall_maker;
                    wall->x = x;
                    wall->y = y;
                    wall->horizontal = false;
                    stack.push(wall);
                } else if (i == 1 && y < height - 1) {
                    auto* wall = new wall_maker;
                    wall->x = x;
                    wall->y = y;
                    wall->horizontal = true;
                    stack.push(wall);
                }
            }
        }
    }

    while (!stack.empty()) {
        auto* wallsPossible =
            static_cast<wall_maker*>(stack.pop(maze->getRand()));
        const int x = wallsPossible->x;
        const int y = wallsPossible->y;
        const bool direction = wallsPossible->horizontal;
        maze->addWall(x, y, direction);
        int nbBorders = 0;
        int nbLoops = 0;
        validWall(maze, wallsPossible, nbBorders, nbLoops);
        if (nbBorders >= 2 || nbLoops >= 1) {
            maze->removeWall(x, y, direction);
        }
        Cell* showCell[1] = {maze->getCell(x, y)};
        refreshShow(show, 1, showCell);
    }
    bool isValid = false;
    bool isPerfect = false;
    checker_depth_first(maze, true, false, show, &isValid, &isPerfect);
    Stack stackDoubleCell;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int i = 0; i < 2; i++) {
                Cell* cell1 = maze->getCell(x, y);
                if (i == 0 && x < width - 1) {
                    Cell* cell2 = maze->getCell(x + 1, y);
                    if (cell1->getStatus() == MAZE_STATUS_TOO_MANY_NEIGHBORS &&
                        cell2->getStatus() == MAZE_STATUS_TOO_MANY_NEIGHBORS) {
                        stackDoubleCell.push(new double_cell{cell1, cell2});
                    }
                } else if (i == 1 && y < height - 1) {
                    Cell* cell2 = maze->getCell(x, y + 1);
                    if (cell1->getStatus() == MAZE_STATUS_TOO_MANY_NEIGHBORS &&
                        cell2->getStatus() == MAZE_STATUS_TOO_MANY_NEIGHBORS) {
                        stackDoubleCell.push(new double_cell{cell1, cell2});
                    }
                }
            }
        }
    }
    std::cout << "stackDoubleCell size : " << stackDoubleCell.size()
              << std::endl;
    processStackRecursive(maze, stackDoubleCell, isValid, isPerfect, 0);
    if (!perfect)
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                for (int i = 0; i < 2; i++) {
                    if (maze->getRand()->get(probability)) {
                        if (i == 0 && x < width - 1) {
                            maze->removeWall(x, y, false);
                        } else if (i == 1 && y < height - 1) {
                            maze->removeWall(x, y, true);
                        }
                        Cell* showCell[1] = {maze->getCell(x, y)};
                        refreshShow(show, 1, showCell);
                    }
                }
            }
        }
}
