#include "show.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "var.hpp"

void show(Maze *maze) {
    for (int x = 0; x < maze->getWidth() * 2 + 1; x++) {
        std::cout << "_";
    }
    std::cout << std::endl;
    for (int y = 0; y < maze->getHeight() - 1; y++) {
        std::cout << "|";
        for (int x = 0; x < maze->getWidth() - 1; x++) {
            Cell* cell = maze->getCell(x, y);
            if (cell->getWall(MAZE_CELL_BOTTOM)) {
                std::cout << "_";
            } else {
                std::cout << " ";
            }
            if (cell->getWall(MAZE_CELL_RIGHT)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
        }
        if (maze->getCell(maze->getWidth() - 1, y)->getWall(MAZE_CELL_BOTTOM)) {
            std::cout << "_";
        } else {
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "|";
    for (int x = 0; x < maze->getWidth() - 1; x++) {
        Cell* cell = maze->getCell(x, maze->getHeight() - 1);
        std::cout << "_";
        if (cell->getWall(MAZE_CELL_RIGHT)) {
            std::cout << "|";
        } else {
            std::cout << "_";
        }
    }
    std::cout << "_|" << std::endl;

    // Création de la fenêtre
    // sf::RenderWindow window(sf::VideoMode(maze->getWidth() * 20, maze->getHeight() * 20), "Maze");

    // Boucle principale
    // while (window.isOpen()) {
        // Gestion des événements
        // sf::Event event;
        // while (window.pollEvent(event)) {
        //     if (event.type == sf::Event::Closed)
        //         window.close();
        // }

        // Dessin du labyrinthe
        // window.clear(sf::Color::White);
        // for (int y = 0; y < maze->getHeight(); y++) {
        //     for (int x = 0; x < maze->getWidth(); x++) {
        //         Cell* cell = maze->getCell(x, y);

        //         // Dessin des murs
        //         if (cell->getWall(cell->NeighborsEnum::BOTTOM)) {
        //             sf::RectangleShape wall(sf::Vector2f(20, 2));
        //             wall.setPosition(x * 20, y * 20 + 19);
        //             wall.setFillColor(sf::Color::Black);
        //             window.draw(wall);
        //         }
        //         if (cell->getWall(cell->NeighborsEnum::RIGHT)) {
        //             sf::RectangleShape wall(sf::Vector2f(2, 20));
        //             wall.setPosition(x * 20 + 19, y * 20);
        //             wall.setFillColor(sf::Color::Black);
        //             window.draw(wall);
        //         }
        //     }
        // }

        // Dessin des bordures
        // sf::RectangleShape border(sf::Vector2f(maze->getWidth() * 20, 1));
        // border.setPosition(0, 0);
        // border.setFillColor(sf::Color::Red);
        // window.draw(border);
        // border.setPosition(0, maze->getHeight() * 20-1);
        // window.draw(border);
        // border.setSize(sf::Vector2f(1, maze->getHeight() * 20));
        // border.setPosition(0, 0);
        // window.draw(border);
        // border.setPosition(maze->getWidth() * 20 - 1, 0);
        // window.draw(border);

        // Affichage de la fenêtre
        // window.display();
    // }
}
