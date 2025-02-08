#include "show.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <random>

#include "var.hpp"

Show::Show(Maze *maze) {
    maze_ = maze;
    renderWindow_ = nullptr;
    cellSize_ = 50;
    if (!font_.loadFromFile("src/assets/poppins.ttf")) {
        std::cerr << "Error: cannot load font" << std::endl;
    }
}

void Show::create() {
    cellSize_ = 50;
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
    if (maze_->getWidth() * cellSize_ >
            desktopSize.width * MAZE_MAX_WINDOW_RATIO ||
        maze_->getHeight() * cellSize_ >
            desktopSize.height * MAZE_MAX_WINDOW_RATIO) {
        cellSize_ = std::min(desktopSize.width / maze_->getWidth(),
                             desktopSize.height / maze_->getHeight()) *
                    MAZE_MAX_WINDOW_RATIO;
    }
    renderWindow_ =
        new sf::RenderWindow(sf::VideoMode(maze_->getWidth() * cellSize_,
                                           maze_->getHeight() * cellSize_),
                             "Maze");
    renderWindow_->setVerticalSyncEnabled(true);

    const sf::Vector2i screenCenter(static_cast<int>(desktopSize.width / 2),
                                    static_cast<int>(desktopSize.height / 2));
    renderWindow_->setPosition(screenCenter -
                               sf::Vector2i(renderWindow_->getSize().x / 2,
                                            renderWindow_->getSize().y / 2));
}

void Show::destroy() {
    if (renderWindow_ == nullptr) {
        return;
    }
    delete renderWindow_;
    renderWindow_ = nullptr;
}

bool Show::isOpen() const {
    if (renderWindow_ == nullptr) {
        return false;
    }
    return renderWindow_->isOpen();
}

void Show::eventHandler() const {
    sf::Event event{};
    while (renderWindow_->pollEvent(event)) {
        eventHandler_(event);
    }
}

bool Show::pollEvent(sf::Event &event) const {
    return renderWindow_->pollEvent(event);
}

void Show::eventHandler_(const sf::Event &event) const {
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed &&
         event.key.code == sf::Keyboard::Escape)) {
        renderWindow_->close();
    }
}

void Show::clearBlack() const { renderWindow_->clear(sf::Color::Black); }

void Show::refreshDisplay() const {
    renderWindow_->display();
    sf::sleep(sf::milliseconds(1000 / 60 + 1));
}

void Show::drawCells() const {
    for (int y = 0; y < maze_->getHeight(); y++) {
        for (int x = 0; x < maze_->getWidth(); x++) {
            drawCell(maze_->getCell(x, y));
        }
    }
}

void Show::refreshMaze() const {
    eventHandler();
    // clear();
    drawCells();
    refreshDisplay();
}

void Show::drawCell_(const Cell *cell) const {
    sf::RectangleShape visited(sf::Vector2f(static_cast<float>(cellSize_),
                                            static_cast<float>(cellSize_)));
    visited.setPosition(static_cast<float>(cell->getX() * cellSize_),
                        static_cast<float>(cell->getY() * cellSize_));
    if (cell->getStatus() == MAZE_STATUS_IDLE) {
        visited.setFillColor(sf::Color(MAZE_STATUS_IDLE_COLOR, 255));
    } else if (cell->getStatus() == MAZE_STATUS_VISITED) {
        visited.setFillColor(sf::Color(MAZE_STATUS_VISITED_COLOR, 255));
    } else if (cell->getStatus() == MAZE_STATUS_HOPELESS) {
        visited.setFillColor(sf::Color(MAZE_STATUS_HOPELESS_COLOR, 255));
    } else if (cell->getStatus() == MAZE_STATUS_TOO_MANY_NEIGHBORS) {
        visited.setFillColor(
            sf::Color(MAZE_STATUS_TOO_MANY_NEIGHBORS_COLOR, 255));
    } else if (cell->getStatus() == MAZE_STATUS_WAY_OUT) {
        visited.setFillColor(sf::Color(MAZE_STATUS_WAY_OUT_COLOR, 255));
    } else if (cell->getStatus() == MAZE_STATUS_CURRENT) {
        visited.setFillColor(sf::Color(MAZE_STATUS_CURRENT_COLOR, 255));
    } else {
        visited.setFillColor(sf::Color::Black);
    }
    renderWindow_->draw(visited);
}

void Show::drawWall_(const Cell *cell, const int orientation) const {
    int x = cell->getX();
    int y = cell->getY();
    if (cell->getWall(orientation)) {
        sf::RectangleShape wall(sf::Vector2f(cellSize_, 1));
        wall.setFillColor(sf::Color::White);
        if (x == maze_->getEndX() && y == maze_->getEndY()) {
            wall.setFillColor(sf::Color::Green);
        } else if (x == maze_->getStartX() && y == maze_->getStartY()) {
            wall.setFillColor(sf::Color::Red);
        }
        Cell *neighbor = nullptr;
        if (orientation == MAZE_CELL_TOP) {
            neighbor = maze_->getCell(x, y - 1);
            if (neighbor->getWall(MAZE_CELL_BOTTOM)) y--;
            wall.setPosition(x * cellSize_, y * cellSize_ + cellSize_);
        } else if (orientation == MAZE_CELL_RIGHT) {
            neighbor = maze_->getCell(x + 1, y);
            wall.setSize(sf::Vector2f(1, cellSize_));
            wall.setPosition(x * cellSize_ + cellSize_, y * cellSize_);
        } else if (orientation == MAZE_CELL_BOTTOM) {
            neighbor = maze_->getCell(x, y + 1);
            wall.setPosition(x * cellSize_, y * cellSize_ + cellSize_);
        } else {
            neighbor = maze_->getCell(x - 1, y);
            if (maze_->getCell(x - 1, y)->getWall(MAZE_CELL_RIGHT)) x--;
            wall.setSize(sf::Vector2f(1, cellSize_));
            wall.setPosition(x * cellSize_ + cellSize_, y * cellSize_);
        }
        if (neighbor->getX() == maze_->getEndX() &&
            neighbor->getY() == maze_->getEndY()) {
            wall.setFillColor(sf::Color::Green);
        } else if (neighbor->getX() == maze_->getStartX() &&
                   neighbor->getY() == maze_->getStartY()) {
            wall.setFillColor(sf::Color::Red);
        }
        renderWindow_->draw(wall);
    }
}

void Show::drawFrontier_(const Cell *cell, const int orientation) const {
    sf::RectangleShape frontier(sf::Vector2f(cellSize_, 1));
    if (orientation == MAZE_CELL_TOP) {
        frontier.setPosition(cell->getX() * cellSize_, 0);
    } else if (orientation == MAZE_CELL_RIGHT) {
        frontier.setSize(sf::Vector2f(1, cellSize_));
        frontier.setPosition(maze_->getWidth() * cellSize_ - 1,
                             cell->getY() * cellSize_);
    } else if (orientation == MAZE_CELL_BOTTOM) {
        frontier.setPosition(cell->getX() * cellSize_,
                             maze_->getHeight() * cellSize_ - 1);
    } else {
        frontier.setSize(sf::Vector2f(1, cellSize_));
        frontier.setPosition(0, cell->getY() * cellSize_);
    }
    if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
        frontier.setFillColor(sf::Color::Green);
    } else if (cell->getX() == maze_->getStartX() &&
               cell->getY() == maze_->getStartY()) {
        frontier.setFillColor(sf::Color::Red);
    } else {
        frontier.setFillColor(sf::Color::White);
    }
    renderWindow_->draw(frontier);
}

void Show::drawCell(const Cell *cell) const {
    const int x = cell->getX();
    const int y = cell->getY();
    drawCell_(cell);
    // Dessin des murs
    if (y > 0) {
        drawWall_(cell, MAZE_CELL_TOP);
    }
    if (x < maze_->getWidth() - 1) {
        drawWall_(cell, MAZE_CELL_RIGHT);
    }
    if (y < maze_->getHeight() - 1) {
        drawWall_(cell, MAZE_CELL_BOTTOM);
    }
    if (x > 0) {
        drawWall_(cell, MAZE_CELL_LEFT);
    }

    if (cell->getX() == 0) {
        drawFrontier_(cell, MAZE_CELL_LEFT);
    }
    if (cell->getY() == 0) {
        drawFrontier_(cell, MAZE_CELL_TOP);
    }
    if (cell->getX() == maze_->getWidth() - 1) {
        drawFrontier_(cell, MAZE_CELL_RIGHT);
    }
    if (cell->getY() == maze_->getHeight() - 1) {
        drawFrontier_(cell, MAZE_CELL_BOTTOM);
    }
}

bool Show::keyPress() {
    sf::Event event{};
    while (renderWindow_->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            lastKeyPressed_ = event.key;
            return true;
        }
    }
    return false;
}

sf::Event::KeyEvent Show::getLastKeyPressed() const { return lastKeyPressed_; }

void Show::close() const {
    if (renderWindow_ == nullptr) {
        return;
    }
    renderWindow_->close();
}

void updateShowLive(const Show *show, const Maze *maze,
                    const bool fastCooling) {
    if (show == nullptr || maze == nullptr) return;
    if (!show->isOpen()) return;
    show->eventHandler();
    if (fastCooling) {
        if (maze->getWidth() <= MAZE_REFRESH_SIZE &&
            maze->getHeight() <= MAZE_REFRESH_SIZE) {
            show->drawCells();
        }
    } else {
        if (maze->getWidth() > MAZE_REFRESH_SIZE ||
            maze->getHeight() > MAZE_REFRESH_SIZE) {
            show->drawCells();
        }
    }
    show->refreshDisplay();
}

void updateShowLive(const Show *show, const Maze *maze) {
    if (show == nullptr || maze == nullptr) return;
    if (!show->isOpen()) return;
    show->eventHandler();
    updateShowLive(show, maze, false);
    updateShowLive(show, maze, true);
    show->refreshDisplay();
}

void updateShowLive(const Show *show, const Maze *maze, const int argc,
                    Cell *argv[]) {
    if (show == nullptr || maze == nullptr) return;
    if (!show->isOpen()) return;
    if (argc <= 0) return;
    show->eventHandler();
    for (int i = 0; i < argc; i++) {
        if (argv[i] != nullptr) show->drawCell(argv[i]);
    }
    show->refreshDisplay();
}

void refreshShow(const Show *show) {
    if (show == nullptr) return;
    if (!show->isOpen()) return;
    // show->eventHandler();
    show->drawCells();
}