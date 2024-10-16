#include "show.hpp"
#include "var.hpp"
#include <SFML/Graphics/CircleShape.hpp>
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
    if (maze_->getWidth() * cellSize_ > desktopSize.width * MAZE_MAX_WINDOW_RATIO || maze_->getHeight() * cellSize_ > desktopSize.height * MAZE_MAX_WINDOW_RATIO) {
        cellSize_ = std::min(desktopSize.width / maze_->getWidth(), desktopSize.height / maze_->getHeight()) * MAZE_MAX_WINDOW_RATIO;
    }
    renderWindow_ = new sf::RenderWindow(sf::VideoMode(maze_->getWidth() * cellSize_, maze_->getHeight() * cellSize_), "Maze");
    renderWindow_->setVerticalSyncEnabled(true);

    sf::Vector2i screenCenter(desktopSize.width / 2, desktopSize.height / 2);
    renderWindow_->setPosition(screenCenter - sf::Vector2i(renderWindow_->getSize().x / 2, renderWindow_->getSize().y / 2));
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
            updateCell(cell);
        }
    }

    // Dessin des bordures
    // sf::RectangleShape border(sf::Vector2f(maze_->getWidth() * cellSize_, 1));
    // border.setPosition(0, 0);
    // border.setFillColor(sf::Color::White);
    // renderWindow_->draw(border);
    // border.setPosition(0, maze_->getHeight() * cellSize_ - 1);
    // renderWindow_->draw(border);
    // border.setSize(sf::Vector2f(1, maze_->getHeight() * cellSize_));
    // border.setPosition(0, 0);
    // renderWindow_->draw(border);
    // border.setPosition(maze_->getWidth() * cellSize_ - 1, 0);
    // renderWindow_->draw(border);
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
    // clear();
    draw();
    display();
}

void Show::updateCell(Cell *cell) {
    int x = cell->getX();
    int y = cell->getY();
    // fait un rectangle noir de taille cellSize_ x cellSize_
    sf::RectangleShape rectangle(sf::Vector2f(cellSize_ - 1, cellSize_ - 1));
    rectangle.setPosition(x * cellSize_, y * cellSize_);
    rectangle.setFillColor(sf::Color::Black);
    renderWindow_->draw(rectangle);


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
    } else if (cell->getStatus() == MAZE_STATUS_WAY_OUT) {
        visited.setFillColor(sf::Color(MAZE_STATUS_WAY_OUT_COLOR, 255));
    } else if (cell->getStatus() == MAZE_STATUS_CURRENT) {
        visited.setFillColor(sf::Color(MAZE_STATUS_CURRENT_COLOR, 255));
    } else {
        visited.setFillColor(sf::Color::Black);
    }
    renderWindow_->draw(visited);

    // Dessin des murs
    if (cell->getWall(MAZE_CELL_BOTTOM) || y == maze_->getHeight() - 1) {
        sf::RectangleShape wall(sf::Vector2f(cellSize_, 1));
        wall.setPosition(x * cellSize_, y * cellSize_ + cellSize_ - 1);
        if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
            wall.setFillColor(sf::Color::Green);
        } else if (cell->getX() == maze_->getStartX() && cell->getY() == maze_->getStartY()) {
            wall.setFillColor(sf::Color::Red);
        } else {
            wall.setFillColor(sf::Color::White);
        }
        renderWindow_->draw(wall);
    }
    if (cell->getWall(MAZE_CELL_RIGHT) || x == maze_->getWidth() - 1) {
        sf::RectangleShape wall(sf::Vector2f(1, cellSize_));
        wall.setPosition(x * cellSize_ + cellSize_ - 1, y * cellSize_);
        if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
            wall.setFillColor(sf::Color::Green);
        } else if (cell->getX() == maze_->getStartX() && cell->getY() == maze_->getStartY()) {
            wall.setFillColor(sf::Color::Red);
        } else {
            wall.setFillColor(sf::Color::White);
        }
        renderWindow_->draw(wall);
    }

    if (cell->getX() == maze_->getStartX() && cell->getY() == maze_->getStartY()) {
        sf::CircleShape start(2);
        start.setFillColor(sf::Color::Red);
        start.setPosition(cell->getX() * cellSize_ + cellSize_ / 2 - 2, cell->getY() * cellSize_ + cellSize_ / 2 - 2);
        renderWindow_->draw(start);
    }
    if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
        sf::CircleShape end(2);
        end.setFillColor(sf::Color::Green);
        end.setPosition(cell->getX() * cellSize_ + cellSize_ / 2 - 2, cell->getY() * cellSize_ + cellSize_ / 2 - 2);
        renderWindow_->draw(end);
    }

    if (cell->getX() == 0) {
        sf::RectangleShape wall(sf::Vector2f(1, cellSize_));
        wall.setPosition(0, y * cellSize_);
        if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
            wall.setFillColor(sf::Color::Green);
        } else if (cell->getX() == maze_->getStartX() && cell->getY() == maze_->getStartY()) {
            wall.setFillColor(sf::Color::Red);
        } else {
            wall.setFillColor(sf::Color::White);
        }
        renderWindow_->draw(wall);
    }
    if (cell->getY() == 0) {
        sf::RectangleShape wall(sf::Vector2f(cellSize_, 1));
        wall.setPosition(x * cellSize_, 0);
        if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
            wall.setFillColor(sf::Color::Green);
        } else if (cell->getX() == maze_->getStartX() && cell->getY() == maze_->getStartY()) {
            wall.setFillColor(sf::Color::Red);
        } else {
            wall.setFillColor(sf::Color::White);
        }
        renderWindow_->draw(wall);
    }
    if (cell->getX() == maze_->getWidth() - 1) {
        sf::RectangleShape wall(sf::Vector2f(1, cellSize_));
        wall.setPosition((x + 1) * cellSize_, y * cellSize_);
        if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
            wall.setFillColor(sf::Color::Green);
        } else if (cell->getX() == maze_->getStartX() && cell->getY() == maze_->getStartY()) {
            wall.setFillColor(sf::Color::Red);
        } else {
            wall.setFillColor(sf::Color::White);
        }
        renderWindow_->draw(wall);
    }
    if (cell->getY() == maze_->getHeight() - 1) {
        sf::RectangleShape wall(sf::Vector2f(cellSize_, 1));
        wall.setPosition(x * cellSize_, (y + 1) * cellSize_);
        if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
            wall.setFillColor(sf::Color::Green);
        } else if (cell->getX() == maze_->getStartX() && cell->getY() == maze_->getStartY()) {
            wall.setFillColor(sf::Color::Red);
        } else {
            wall.setFillColor(sf::Color::White);
        }
        renderWindow_->draw(wall);
    }
}

void updateShowLive(Show *show, Maze *maze, bool fastCooling) {
    if (show == nullptr || maze == nullptr) return;
    if (!show->isOpen()) return;
    if (fastCooling) {
        if (maze -> getWidth() <= MAZE_REFRESH_SIZE && maze -> getHeight() <= MAZE_REFRESH_SIZE) {
            show->update();
        }
    } else {
        if (maze -> getWidth() > MAZE_REFRESH_SIZE || maze -> getHeight() > MAZE_REFRESH_SIZE) {
            show->update();
        }
    }
}

void updateShowLive(Show* show, Maze* maze) {
    updateShowLive(show, maze, false);
    updateShowLive(show, maze, true);
}

void updateShowLive(Show *show, Maze *maze, int argc, Cell *argv[]) {
    if (show == nullptr || maze == nullptr) return;
    if (!show->isOpen()) return;
    if (argc <= 0) return;
    show->eventHandler();
    for (int i = 0; i < argc; i++) {
        show->updateCell(argv[i]);
    }
    show->display();
}
