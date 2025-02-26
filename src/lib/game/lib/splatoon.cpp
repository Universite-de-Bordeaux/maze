#include "splatoon.hpp"

int MinCountCell(const Cell *cell, int **counts, const bool checkVisited) {
    int minCount = -1;
    const int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
    const auto neighbors = new Cell *[nbNeighbors];
    cell->getAbsoluteNeighbors(neighbors);
    for (int i = 0; i < nbNeighbors; i++) {
        if (neighbors[i] != nullptr &&
            (!checkVisited || !neighbors[i]->isAlreadyVisited())) {
            const int count =
                counts[neighbors[i]->getX()][neighbors[i]->getY()];
            if (minCount == -1 || count < minCount) {
                minCount = count;
            }
        }
    }
    delete[] neighbors;
    return minCount;
}

int nbMinCountCell(const Cell *cell, int **counts, const int minCount,
                   const bool checkVisited) {
    int nbMinCount = 0;
    const int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
    const auto neighbors = new Cell *[nbNeighbors];
    cell->getAbsoluteNeighbors(neighbors);
    for (int i = 0; i < nbNeighbors; i++) {
        if (neighbors[i] != nullptr &&
            (!checkVisited || !neighbors[i]->isAlreadyVisited())) {
            const int count =
                counts[neighbors[i]->getX()][neighbors[i]->getY()];
            if (count == minCount) {
                nbMinCount++;
            }
        }
    }
    delete[] neighbors;
    return nbMinCount;
}

void cellsMinCountCell(const Cell *cell, int **counts, const int minCount,
                       Cell **cells, const bool checkVisited) {
    int index = 0;
    const int nbNeighbors = cell->getAbsoluteNumberOfNeighbors();
    const auto neighbors = new Cell *[nbNeighbors];
    cell->getAbsoluteNeighbors(neighbors);
    for (int i = 0; i < nbNeighbors; i++) {
        if (neighbors[i] != nullptr &&
            (!checkVisited || !neighbors[i]->isAlreadyVisited())) {
            const int count =
                counts[neighbors[i]->getX()][neighbors[i]->getY()];
            if (count == minCount) {
                cells[index] = neighbors[i];
                index++;
            }
        }
    }
    delete[] neighbors;
}