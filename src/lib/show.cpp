#include "show.hpp"
#include "var.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/InputStream.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>

Show::Show(Maze* maze) {
    maze_ = maze;
    renderWindow_ = nullptr;
    cellSize_ = 50;
    if (!font_.loadFromFile("src/assets/poppins.ttf")) {
        std::cerr << "Error: cannot load font" << std::endl;
    }
}

void Show::create() {
    cellSize_ = 50;
    sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
    if (maze_->getWidth() * cellSize_ > desktopSize.width *.9 || maze_->getHeight() * cellSize_ > desktopSize.height *.9) {
        cellSize_ = std::min(desktopSize.width / maze_->getWidth(), desktopSize.height / maze_->getHeight()) *.9;
    }
    renderWindow_ = new sf::RenderWindow(sf::VideoMode(maze_->getWidth() * cellSize_, maze_->getHeight() * cellSize_), "Maze");
    renderWindow_->setVerticalSyncEnabled(true);

    sf::Vector2i screenCenter(desktopSize.width / 2, desktopSize.height / 2);
    renderWindow_->setPosition(screenCenter - sf::Vector2i(renderWindow_->getSize().x / 2, renderWindow_->getSize().y / 2));

    // sf::Text text;
    // text.setFont(font_);
    // text.setString("Hello World");
    // text.setCharacterSize(24);
    // text.setFillColor(sf::Color::Red);

    // int x = 0;
    // while (renderWindow_->isOpen()) {
    //     eventHandler();
    //     clear();
    //     // text.setString(std::to_string(x));
    //     // renderWindow_->draw(text);
    //     display();
    //     // x++;
    // }
}

void Show::destroy() {
    if (renderWindow_ == nullptr) {
        return;
    }
    delete renderWindow_;
    renderWindow_ = nullptr;
}

bool Show::isOpen() {
    if (renderWindow_ == nullptr) {
        return false;
    }
    return renderWindow_->isOpen();
}

void Show::draw() {
    // Dessin du labyrinthe
    for (int y = 0; y < maze_->getHeight(); y++) {
        for (int x = 0; x < maze_->getWidth(); x++) {
            Cell* cell = maze_->getCell(x, y);

            // Dessin de la case
            sf::RectangleShape visited(sf::Vector2f(cellSize_, cellSize_));
            visited.setPosition(x * cellSize_, y * cellSize_);
            if (cell->getStatus() == MAZE_STATUS_IDLE) {
                visited.setFillColor(sf::Color(MAZE_STATUS_IDLE_COLOR, 255));
            } else if (cell->getStatus() == MAZE_STATUS_VISITED) {
                visited.setFillColor(sf::Color(MAZE_STATUS_VISITED_COLOR, 255));
            } else if (cell->getStatus() == MAZE_STATUS_HOPELESS) {
                visited.setFillColor(sf::Color(MAZE_STATUS_HOPELESS_COLOR, 255));
            } else if (cell->getStatus() == MAZE_STATUS_TOO_MANY_NEIGHBORS) {
                visited.setFillColor(sf::Color(MAZE_STATUS_TOO_MANY_NEIGHBORS_COLOR, 255));
            }
            renderWindow_->draw(visited);

            // Dessin des murs
            if (cell->getWall(MAZE_CELL_BOTTOM)) {
                sf::RectangleShape wall(sf::Vector2f(cellSize_, 2));
                wall.setPosition(x * cellSize_, y * cellSize_ + cellSize_ - 2);
                wall.setFillColor(sf::Color::White);
                renderWindow_->draw(wall);
            }
            if (cell->getWall(MAZE_CELL_RIGHT)) {
                sf::RectangleShape wall(sf::Vector2f(2, cellSize_));
                wall.setPosition(x * cellSize_ + cellSize_ - 2, y * cellSize_);
                wall.setFillColor(sf::Color::White);
                renderWindow_->draw(wall);
            }
        }
    }

    // Dessin des bordures
    sf::RectangleShape border(sf::Vector2f(maze_->getWidth() * cellSize_, 1));
    border.setPosition(0, 0);
    border.setFillColor(sf::Color::White);
    renderWindow_->draw(border);
    border.setPosition(0, maze_->getHeight() * cellSize_ - 1);
    renderWindow_->draw(border);
    border.setSize(sf::Vector2f(1, maze_->getHeight() * cellSize_));
    border.setPosition(0, 0);
    renderWindow_->draw(border);
    border.setPosition(maze_->getWidth() * cellSize_ - 1, 0);
    renderWindow_->draw(border);
    border.setFillColor(sf::Color::Red);
    border.setSize(sf::Vector2f(1, cellSize_));
    border.setPosition(0, 0);
    renderWindow_->draw(border);
    border.setSize(sf::Vector2f(cellSize_, 1));
    border.setPosition(0, 0);
    renderWindow_->draw(border);
    border.setFillColor(sf::Color::Green);
    border.setSize(sf::Vector2f(1, cellSize_));
    border.setPosition(maze_->getWidth() * cellSize_ - 1, maze_->getHeight() * cellSize_ - cellSize_);
    renderWindow_->draw(border);
    border.setSize(sf::Vector2f(cellSize_, 1));
    border.setPosition(maze_->getWidth() * cellSize_ - cellSize_, maze_->getHeight() * cellSize_ - 1);
    renderWindow_->draw(border);
}

void Show::eventHandler_(sf::Event &event) {
    if (event.type == sf::Event::Closed) {
        renderWindow_->close();
    }
}

void Show::eventHandler() {
    sf::Event event;
    while (renderWindow_->pollEvent(event)) {
        eventHandler_(event);
    }
}

bool Show::pollEvent(sf::Event &event) {
    return renderWindow_->pollEvent(event);
}

void Show::clear() {
    renderWindow_->clear(sf::Color::Black);
}

void Show::display() {
    renderWindow_->display();
}

void Show::update() {
    eventHandler();
    clear();
    draw();
    display();
}
