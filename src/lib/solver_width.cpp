#include "show.hpp"
#include "maze.hpp"
#include "var.hpp"
#include <iostream>
#include "queue.hpp"

static bool solver_bfs(Maze *maze, Show *show, bool toLeft) {
    // On récupère les cellules de départ et d'arrivée
    Cell* startCell = maze->getStartCell();
    Cell* endCell = maze->getEndCell();

    // tester si les cellules de départ et d'arrivée sont définies
    if (startCell == nullptr || endCell == nullptr) {
        std::cerr << "Error: les cellule d'arriver ou de depart sont pas valide" << std::endl;
        return false;
    }

    // Instanciation de la file personnalisée
    Queue queue;

    // Marquer la cellule de départ comme visitée et l'ajouter à la file
    startCell->setAlreadyVisited(true);
    startCell->setStatus(MAZE_STATUS_VISITED);
    queue.enqueue(startCell);
    show->updateCell(startCell);  // Mise à jour visuelle
    show->display();

    // Parcours en largeur
    while (!queue.is_empty()) {
        // Récupérer et retirer la cellule en tête de la file
        Cell* currentCell = queue.dequeue();

        // Vérifie si nous avons atteint la fin du labyrinthe
        if (currentCell == endCell) {
            std::cout << "Labyrinthe résolu !" << std::endl;

            // Marquer le chemin jusqu'à l'entrée
            while (currentCell != nullptr && currentCell != startCell) {
                currentCell->setStatus(MAZE_STATUS_CURRENT);
                show->updateCell(currentCell);
                show->display();
                // currentCell = currentCell->getParent();
                //
            }
            return true;
        }

        // Récupérer les voisins non visités de la cellule actuelle
        Cell* neighbors[4];
        currentCell->getAbsoluteNeighborsNotVisited(neighbors);
        bool foundNext = false;

        for (int i = 0; i < 4; ++i) {
            if (neighbors[i] != nullptr) {
                // Ajouter le voisin à la file et le marquer comme visité
                neighbors[i]->setAlreadyVisited(true);
                neighbors[i]->setStatus(MAZE_STATUS_VISITED);
                neighbors[i]->setParent(currentCell);  // Définit le parent pour remonter le chemin plus tard
                queue.enqueue(neighbors[i]);
                show->updateCell(neighbors[i]);
                show->display();
                foundNext = true;
            }
        }

        // Si aucune cellule n'est trouvée, marquez comme cul-de-sac
        if (!foundNext) {
            currentCell->setStatus(MAZE_STATUS_HOPELESS);
            show->updateCell(currentCell);
            show->display();
        }
    }

    // Si le labyrinthe n'a pas de solution
    std::cout << "Le labyrinthe est impossible à résoudre." << std::endl;
    return false;
}


bool solver_width(Maze *maze, Show *show, bool toLeft) {
    updateShowLive(show, maze);
    std::cout << "Résolution du labyrinthe en largeur" << std::endl;
    return solver_bfs(maze, show, toLeft);
}
