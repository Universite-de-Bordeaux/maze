#include "show.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>

#include "var.hpp"

Show::Show(Maze *maze) {
    maze_ = maze;
    renderWindow_ = nullptr;
    cellSize_ = 50;
    lastDisplay_ = std::chrono::high_resolution_clock::now();
    lowFreq_ = true;

    std::ifstream envFile(".env");
    if (envFile.is_open()) {
        std::string line;
        unsigned int framerate = 60;
        float delay = 0;
        while (std::getline(envFile, line)) {
            if (line.find("FRAMERATE=") == 0) {
                framerate = std::stoi(line.substr(10));
            } else if (line.find("DELAY_SHOW=") == 0) {
                delay = std::stof(line.substr(11));
            }
        }
        setRefreshRate(framerate);
        setDelay(delay);
        envFile.close();
    } else {
        setRefreshRate(60);
        setDelay(0);
    }

    if (!font_.loadFromFile("src/assets/poppins.ttf")) {
        std::cerr << "Error: cannot load font" << std::endl;
    }
}

void Show::create() {
    cellSize_ = 50;
    lastDisplay_ = std::chrono::high_resolution_clock::now();
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
    if (static_cast<float>(maze_->getWidth()) * cellSize_ >
            desktopSize.width * MAZE_MAX_WINDOW_RATIO ||
        static_cast<float>(maze_->getHeight()) * cellSize_ >
            desktopSize.height * MAZE_MAX_WINDOW_RATIO) {
        const bool priorityWidth = maze_->getWidth() / desktopSize.width >
                                   maze_->getHeight() / desktopSize.height;
        if (priorityWidth) {
            cellSize_ = static_cast<float>(desktopSize.width) /
                        static_cast<float>(maze_->getWidth()) *
                        MAZE_MAX_WINDOW_RATIO;
        } else {
            cellSize_ = static_cast<float>(desktopSize.height) /
                        static_cast<float>(maze_->getHeight()) *
                        MAZE_MAX_WINDOW_RATIO;
        }
    }
    renderWindow_ = new sf::RenderWindow(
        sf::VideoMode(static_cast<unsigned int>(
                          static_cast<float>(maze_->getWidth()) * cellSize_),
                      static_cast<unsigned int>(
                          static_cast<float>(maze_->getHeight()) * cellSize_)),
        "Maze");
    renderWindow_->setVerticalSyncEnabled(true);

    const sf::Vector2i screenCenter(static_cast<int>(desktopSize.width / 2),
                                    static_cast<int>(desktopSize.height / 2));
    renderWindow_->setPosition(
        screenCenter -
        sf::Vector2i(static_cast<int>(renderWindow_->getSize().x / 2),
                     static_cast<int>(renderWindow_->getSize().y / 2)));
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
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape)) {
            renderWindow_->close();
        }
    }
}

bool Show::pollEvent(sf::Event &event) const {
    return renderWindow_->pollEvent(event);
}

void Show::clearBlack() const { renderWindow_->clear(sf::Color::Black); }

void Show::refreshDisplay() {
    const auto now = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - lastDisplay_);
    if (duration >= refreshRate_) {
        renderWindow_->display();
        lastDisplay_ = std::chrono::high_resolution_clock::now();
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(delay_));
}

void Show::drawCells_() const {
    for (int y = 0; y < maze_->getHeight(); y++) {
        for (int x = 0; x < maze_->getWidth(); x++) {
            drawCell(maze_->getCell(x, y));
        }
    }
}

void Show::refreshMaze() {
    eventHandler();
    // clearBlack();
    drawCells_();
    refreshDisplay();
}

void Show::drawCell_(const Cell *cell) const {
    sf::RectangleShape visited(sf::Vector2f(cellSize_, cellSize_));
    visited.setPosition(static_cast<float>(cell->getX()) * cellSize_,
                        static_cast<float>(cell->getY()) * cellSize_);
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
        wall.setFillColor(sf::Color(MAZE_WALL_COLOR, 255));
        if (x == maze_->getEndX() && y == maze_->getEndY()) {
            wall.setFillColor(sf::Color(MAZE_WALL_END_COLOR, 255));
        } else if (x == maze_->getStartX() && y == maze_->getStartY()) {
            wall.setFillColor(sf::Color(MAZE_WALL_START_COLOR, 255));
        }
        const Cell *neighbor = nullptr;
        if (orientation == MAZE_CELL_TOP) {
            neighbor = maze_->getCell(x, y - 1);
            if (neighbor->getWall(MAZE_CELL_BOTTOM)) y--;
            wall.setPosition(static_cast<float>(x) * cellSize_,
                             static_cast<float>(y) * cellSize_ + cellSize_);
        } else if (orientation == MAZE_CELL_RIGHT) {
            neighbor = maze_->getCell(x + 1, y);
            wall.setSize(sf::Vector2f(1, cellSize_));
            wall.setPosition(static_cast<float>(x) * cellSize_ + cellSize_,
                             static_cast<float>(y) * cellSize_);
        } else if (orientation == MAZE_CELL_BOTTOM) {
            neighbor = maze_->getCell(x, y + 1);
            wall.setPosition(static_cast<float>(x) * cellSize_,
                             static_cast<float>(y) * cellSize_ + cellSize_);
        } else {
            neighbor = maze_->getCell(x - 1, y);
            if (maze_->getCell(x - 1, y)->getWall(MAZE_CELL_RIGHT)) x--;
            wall.setSize(sf::Vector2f(1, cellSize_));
            wall.setPosition(static_cast<float>(x) * cellSize_ + cellSize_,
                             static_cast<float>(y) * cellSize_);
        }
        if (neighbor->getX() == maze_->getEndX() &&
            neighbor->getY() == maze_->getEndY()) {
            wall.setFillColor(sf::Color(MAZE_WALL_END_COLOR, 255));
        } else if (neighbor->getX() == maze_->getStartX() &&
                   neighbor->getY() == maze_->getStartY()) {
            wall.setFillColor(sf::Color(MAZE_WALL_START_COLOR, 255));
        }
        renderWindow_->draw(wall);
    }
}

void Show::drawFrontier_(const Cell *cell, const int orientation) const {
    sf::RectangleShape frontier(sf::Vector2f(cellSize_, 1));
    if (orientation == MAZE_CELL_TOP) {
        frontier.setPosition(static_cast<float>(cell->getX()) * cellSize_, 0);
    } else if (orientation == MAZE_CELL_RIGHT) {
        frontier.setSize(sf::Vector2f(1, cellSize_));
        frontier.setPosition(
            static_cast<float>(maze_->getWidth()) * cellSize_ - 1,
            static_cast<float>(cell->getY()) * cellSize_);
    } else if (orientation == MAZE_CELL_BOTTOM) {
        frontier.setPosition(
            static_cast<float>(cell->getX()) * cellSize_,
            static_cast<float>(maze_->getHeight()) * cellSize_ - 1);
    } else {
        frontier.setSize(sf::Vector2f(1, cellSize_));
        frontier.setPosition(0, static_cast<float>(cell->getY()) * cellSize_);
    }
    if (cell->getX() == maze_->getEndX() && cell->getY() == maze_->getEndY()) {
        frontier.setFillColor(sf::Color(MAZE_WALL_END_COLOR, 255));
    } else if (cell->getX() == maze_->getStartX() &&
               cell->getY() == maze_->getStartY()) {
        frontier.setFillColor(sf::Color(MAZE_WALL_START_COLOR, 255));
    } else {
        frontier.setFillColor(sf::Color(MAZE_WALL_COLOR, 255));
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
    } else if (y == 0) {
        drawFrontier_(cell, MAZE_CELL_TOP);
    }
    if (x < maze_->getWidth() - 1) {
        drawWall_(cell, MAZE_CELL_RIGHT);
    } else if (x == maze_->getWidth() - 1) {
        drawFrontier_(cell, MAZE_CELL_RIGHT);
    }
    if (y < maze_->getHeight() - 1) {
        drawWall_(cell, MAZE_CELL_BOTTOM);
    } else if (y == maze_->getHeight() - 1) {
        drawFrontier_(cell, MAZE_CELL_BOTTOM);
    }
    if (x > 0) {
        drawWall_(cell, MAZE_CELL_LEFT);
    } else if (x == 0) {
        drawFrontier_(cell, MAZE_CELL_LEFT);
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

void refreshShow(Show *show, const int argc, Cell *argv[]) {
    if (show == nullptr) return;
    if (!show->isOpen()) return;
    if (argc <= 0) return;
    show->eventHandler();
    for (int i = 0; i < argc; i++) {
        if (argv[i] != nullptr) show->drawCell(argv[i]);
    }
    show->refreshDisplay();
}

void refreshShow(Show *show, const int argc, Cell *argv[], const bool lowFreq) {
    if (show == nullptr) return;
    if (show->getLowFreq() && lowFreq) refreshShow(show);
    else if (!show->getLowFreq()) refreshShow(show, argc, argv);
}

void refreshShow(Show *show) {
    if (show == nullptr) return;
    if (!show->isOpen()) return;
    if (show->mazeIsEmpty()) return;
    show->refreshMaze();
}

bool Show::mazeIsEmpty() const { return maze_ == nullptr; }

void Show::setRefreshRate(const unsigned int rate) {
    if (rate <= 0) exit(MAZE_GRAPHIC_ERROR);
    refreshRate_ = std::chrono::milliseconds(1000 / rate);
}

void Show::setDelay(const float delay) {
    delay_ = std::chrono::microseconds(static_cast<int>(delay * 1000));
}