#include "show.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include "var.hpp"

void show(Maze *maze) {
    // Création de la fenêtre
    sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

    int cellSize = 50;
    if (maze->getWidth() * cellSize > desktopSize.width * .9 || maze->getHeight() * cellSize > desktopSize.height * .9) {
        cellSize = std::min(desktopSize.width / maze->getWidth(), desktopSize.height / maze->getHeight()) * .9;
    }

    sf::RenderWindow window(sf::VideoMode(maze->getWidth() * cellSize, maze->getHeight() * cellSize), "Maze");

    // Positionnement de la fenêtre au centre de l'écran
    sf::Vector2i screenCenter(desktopSize.width / 2, desktopSize.height / 2);
    window.setPosition(screenCenter - sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));

    // Boucle principale
    while (window.isOpen()) {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Dessin du labyrinthe
        window.clear(sf::Color::Black);
        for (int y = 0; y < maze->getHeight(); y++) {
            for (int x = 0; x < maze->getWidth(); x++) {
                Cell* cell = maze->getCell(x, y);

                // Dessin des murs
                if (cell->getWall(MAZE_CELL_BOTTOM)) {
                    sf::RectangleShape wall(sf::Vector2f(cellSize, 2));
                    wall.setPosition(x * cellSize, y * cellSize + cellSize - 2);
                    wall.setFillColor(sf::Color::White);
                    window.draw(wall);
                }
                if (cell->getWall(MAZE_CELL_RIGHT)) {
                    sf::RectangleShape wall(sf::Vector2f(2, cellSize));
                    wall.setPosition(x * cellSize + cellSize - 2, y * cellSize);
                    wall.setFillColor(sf::Color::White);
                    window.draw(wall);
                }
            }
        }

        // Dessin des bordures
        sf::RectangleShape border(sf::Vector2f(maze->getWidth() * cellSize, 1));
        border.setPosition(0, 0);
        border.setFillColor(sf::Color::White);
        window.draw(border);
        border.setPosition(0, maze->getHeight() * cellSize - 1);
        window.draw(border);
        border.setSize(sf::Vector2f(1, maze->getHeight() * cellSize));
        border.setPosition(0, 0);
        window.draw(border);
        border.setPosition(maze->getWidth() * cellSize - 1, 0);
        window.draw(border);
        border.setFillColor(sf::Color::Red);
        border.setSize(sf::Vector2f(1, cellSize));
        border.setPosition(0, 0);
        window.draw(border);
        border.setSize(sf::Vector2f(cellSize, 1));
        border.setPosition(0, 0);
        window.draw(border);
        border.setFillColor(sf::Color::Green);
        border.setSize(sf::Vector2f(1, cellSize));
        border.setPosition(maze->getWidth() * cellSize - 1, maze->getHeight() * cellSize - cellSize);
        window.draw(border);
        border.setSize(sf::Vector2f(cellSize, 1));
        border.setPosition(maze->getWidth() * cellSize - cellSize, maze->getHeight() * cellSize - 1);
        window.draw(border);

        // Affichage de la fenêtre
        window.display();
    }
}
