#include "show.hpp"
#include "var.hpp"

Show::Show(Maze* maze) {
    maze_ = maze;
    window_ = nullptr;
}

void Show::create() {
    // Création de la fenêtre
    sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

    int cellSize = 50;
    if (maze_->getWidth() * cellSize > desktopSize.width *.9 || maze_->getHeight() * cellSize > desktopSize.height *.9) {
        cellSize = std::min(desktopSize.width / maze_->getWidth(), desktopSize.height / maze_->getHeight()) *.9;
    }

    window_ = new sf::RenderWindow(sf::VideoMode(maze_->getWidth() * cellSize, maze_->getHeight() * cellSize), "Maze");

    // Positionnement de la fenêtre au centre de l'écran
    sf::Vector2i screenCenter(desktopSize.width / 2, desktopSize.height / 2);
    window_->setPosition(screenCenter - sf::Vector2i(window_->getSize().x / 2, window_->getSize().y / 2));
    cellSize_ = cellSize;
}

void Show::update() {
    // Gestion des événements
    sf::Event event;
    while (window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window_->close();
    }

    // Dessin du labyrinthe
    window_->clear(sf::Color::Black);
    for (int y = 0; y < maze_->getHeight(); y++) {
        for (int x = 0; x < maze_->getWidth(); x++) {
            Cell* cell = maze_->getCell(x, y);

            // Dessin des murs
            if (cell->getWall(MAZE_CELL_BOTTOM)) {
                sf::RectangleShape wall(sf::Vector2f(cellSize_, 2));
                wall.setPosition(x * cellSize_, y * cellSize_ + cellSize_ - 2);
                wall.setFillColor(sf::Color::White);
                window_->draw(wall);
            }
            if (cell->getWall(MAZE_CELL_RIGHT)) {
                sf::RectangleShape wall(sf::Vector2f(2, cellSize_));
                wall.setPosition(x * cellSize_ + cellSize_ - 2, y * cellSize_);
                wall.setFillColor(sf::Color::White);
                window_->draw(wall);
            }
        }
    }

    // Dessin des bordures
    sf::RectangleShape border(sf::Vector2f(maze_->getWidth() * cellSize_, 1));
    border.setPosition(0, 0);
    border.setFillColor(sf::Color::White);
    window_->draw(border);
    border.setPosition(0, maze_->getHeight() * cellSize_ - 1);
    window_->draw(border);
    border.setSize(sf::Vector2f(1, maze_->getHeight() * cellSize_));
    border.setPosition(0, 0);
    window_->draw(border);
    border.setPosition(maze_->getWidth() * cellSize_ - 1, 0);
    window_->draw(border);
    border.setFillColor(sf::Color::Red);
    border.setSize(sf::Vector2f(1, cellSize_));
    border.setPosition(0, 0);
    window_->draw(border);
    border.setSize(sf::Vector2f(cellSize_, 1));
    border.setPosition(0, 0);
    window_->draw(border);
    border.setFillColor(sf::Color::Green);
    border.setSize(sf::Vector2f(1, cellSize_));
    border.setPosition(maze_->getWidth() * cellSize_ - 1, maze_->getHeight() * cellSize_ - cellSize_);
    window_->draw(border);
    border.setSize(sf::Vector2f(cellSize_, 1));
    border.setPosition(maze_->getWidth() * cellSize_ - cellSize_, maze_->getHeight() * cellSize_ - 1);
    window_->draw(border);

    // Affichage de la fenêtre
    window_->display();
}

void Show::destroy() {
    delete window_;
    window_ = nullptr;
}

bool Show::isOpen() {
    return window_->isOpen();
}
