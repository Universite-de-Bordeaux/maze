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

    // Initialisation des couleurs par défaut
    colorConfig_.wall = sf::Color(MAZE_WALL_COLOR, 255);
    colorConfig_.wallStart = sf::Color(MAZE_WALL_START_COLOR, 255);
    colorConfig_.wallEnd = sf::Color(MAZE_WALL_END_COLOR, 255);
    colorConfig_.idle = sf::Color(MAZE_STATUS_IDLE_COLOR, 255);
    colorConfig_.visited = sf::Color(MAZE_STATUS_VISITED_COLOR, 255);
    colorConfig_.hopeless = sf::Color(MAZE_STATUS_HOPELESS_COLOR, 255);
    colorConfig_.tooManyNeighbors =
        sf::Color(MAZE_STATUS_TOO_MANY_NEIGHBORS_COLOR, 255);
    colorConfig_.wayOut = sf::Color(MAZE_STATUS_WAY_OUT_COLOR, 255);
    colorConfig_.current = sf::Color(MAZE_STATUS_CURRENT_COLOR, 255);

    loadColorsFromEnv_("MAZE_WALL_COLOR", colorConfig_.wall);
    loadColorsFromEnv_("MAZE_WALL_START_COLOR", colorConfig_.wallStart);
    loadColorsFromEnv_("MAZE_WALL_END_COLOR", colorConfig_.wallEnd);
    loadColorsFromEnv_("MAZE_STATUS_IDLE_COLOR", colorConfig_.idle);
    loadColorsFromEnv_("MAZE_STATUS_VISITED_COLOR", colorConfig_.visited);
    loadColorsFromEnv_("MAZE_STATUS_HOPELESS_COLOR", colorConfig_.hopeless);
    loadColorsFromEnv_("MAZE_STATUS_TOO_MANY_NEIGHBORS_COLOR",
                       colorConfig_.tooManyNeighbors);
    loadColorsFromEnv_("MAZE_STATUS_WAY_OUT_COLOR", colorConfig_.wayOut);
    loadColorsFromEnv_("MAZE_STATUS_CURRENT_COLOR", colorConfig_.current);

    resetValues();

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
            cellSize_ = static_cast<float>(static_cast<double>(desktopSize.width) /
                                           static_cast<double>(maze_->getWidth()) *
                                           MAZE_MAX_WINDOW_RATIO);
        } else {
            cellSize_ = static_cast<float>(static_cast<double>(desktopSize.height) /
                        static_cast<double>(maze_->getHeight()) *
                        MAZE_MAX_WINDOW_RATIO);
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

void Show::eventHandler() {  // NOLINT
    sf::Event event{};
    while (renderWindow_->pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape)) {
            renderWindow_->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            const auto key = event.key.code;
            if (key == sf::Keyboard::D) {
                drawCells_();
            } else if (key == sf::Keyboard::Space) {
                while (true) {
                    if (pollEvent(event)) {
                        if (event.type == sf::Event::KeyPressed &&
                            event.key.code == sf::Keyboard::Space) {
                            break;
                        }
                    }
                }
            } else if (key == sf::Keyboard::L) {
                lowFreq_ = !lowFreq_;
            } else if (key == sf::Keyboard::Add || key == sf::Keyboard::Equal) {
                refreshRate_ += std::chrono::milliseconds(10);
            } else if (key == sf::Keyboard::Subtract ||
                       key == sf::Keyboard::Dash) {
                refreshRate_ -= std::chrono::milliseconds(10);
                if (refreshRate_ < std::chrono::milliseconds(0)) {
                    refreshRate_ = std::chrono::milliseconds(0);
                }
            } else if (key == sf::Keyboard::Multiply) {
                delay_ += std::chrono::milliseconds(10);
            } else if (key == sf::Keyboard::Divide ||
                       key == sf::Keyboard::Slash) {
                delay_ -= std::chrono::milliseconds(10);
                if (delay_ < std::chrono::milliseconds(0)) {
                    delay_ = std::chrono::milliseconds(0);
                }
            } else if (key == sf::Keyboard::R) {
                resetValues();
            }
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            if (maze_->getWidth() <= 100 && maze_->getHeight() <= 100) {
                static constexpr float zoomFactor = 1.1f;
                if (event.mouseWheelScroll.delta > 0) {
                    zoomLevel_ *= zoomFactor;
                } else {
                    zoomLevel_ /= zoomFactor;
                }
                zoomLevel_ = std::max(MIN_ZOOM, std::min(zoomLevel_, MAX_ZOOM));
                clearBlack();
                refreshMaze();
            } else {
                std::cerr << "Error: zoom is disabled for mazes larger than "
                             "100x100"
                          << std::endl;
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (maze_->getWidth() <= 100 && maze_->getHeight() <= 100) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging_ = true;
                    lastMousePosition_ = sf::Mouse::getPosition(*renderWindow_);
                    // Enregistrez le centre actuel de la vue
                    lastViewCenter_ = renderWindow_->getView().getCenter();
                }
            } else {
                std::cerr
                    << "Error: mouse dragging is disabled for mazes larger "
                       "100x100"
                    << std::endl;
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (maze_->getWidth() <= 100 && maze_->getHeight() <= 100) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging_ = false;
                }
            }
        } else if (event.type == sf::Event::MouseMoved && isDragging_) {
            if (maze_->getWidth() <= 100 && maze_->getHeight() <= 100) {
                // Récupérez la position actuelle de la souris
                sf::Vector2i mousePosition =
                    sf::Mouse::getPosition(*renderWindow_);
                // Calculez le changement de position
                const sf::Vector2i delta = mousePosition - lastMousePosition_;
                // Convertir le delta en pixels en un décalage proportionnel
                sf::View currentView = renderWindow_->getView();
                const float scale =
                    currentView.getSize().x /
                    static_cast<float>(renderWindow_->getSize().x);
                // Calcul du décalage en coordonné monde
                sf::Vector2f offset(static_cast<float>(-delta.x) / scale,
                                    static_cast<float>(-delta.y) / scale);
                // Met à jour le centre de la vue
                sf::Vector2f newCenter = lastViewCenter_ + offset;
                // Limiter le déplacement dans les limites de la grille
                newCenter.x = std::max(
                    0.0f, std::min(newCenter.x,
                                   static_cast<float>(maze_->getWidth()) *
                                       cellSize_ * zoomLevel_));
                newCenter.y = std::max(
                    0.0f, std::min(newCenter.y,
                                   static_cast<float>(maze_->getHeight()) *
                                       cellSize_ * zoomLevel_));
                // Met à jour la vue
                currentView.setCenter(newCenter);
                renderWindow_->setView(currentView);
                // Mise à jour de la dernière position de la souris et du centre
                lastMousePosition_ = mousePosition;
                lastViewCenter_ = newCenter;
                clearBlack();
                refreshMaze();
            }
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

void Show::refreshMaze() { // NOLINT
    eventHandler();
    // clearBlack();
    drawCells_();
    refreshDisplay();
}

void Show::drawCell_(const Cell *cell) const {
    const float scaledSize = cellSize_ * zoomLevel_;
    sf::RectangleShape visited(sf::Vector2f(scaledSize, scaledSize));
    visited.setPosition(static_cast<float>(cell->getX()) * scaledSize,
                        static_cast<float>(cell->getY()) * scaledSize);
    if (cell->getStatus() == MAZE_STATUS_IDLE) {
        visited.setFillColor(colorConfig_.idle);
    } else if (cell->getStatus() == MAZE_STATUS_VISITED) {
        visited.setFillColor(colorConfig_.visited);
    } else if (cell->getStatus() == MAZE_STATUS_HOPELESS) {
        visited.setFillColor(colorConfig_.hopeless);
    } else if (cell->getStatus() == MAZE_STATUS_TOO_MANY_NEIGHBORS) {
        visited.setFillColor(colorConfig_.tooManyNeighbors);
    } else if (cell->getStatus() == MAZE_STATUS_WAY_OUT) {
        visited.setFillColor(colorConfig_.wayOut);
    } else if (cell->getStatus() == MAZE_STATUS_CURRENT) {
        visited.setFillColor(colorConfig_.current);
    } else {
        visited.setFillColor(sf::Color::Black);
    }
    renderWindow_->draw(visited);
}

void Show::drawWall_(const Cell *cell, const int orientation) const {
    int x = cell->getX();
    int y = cell->getY();
    if (cell->getWall(orientation)) {
        const float scaledSize = cellSize_ * zoomLevel_;
        sf::RectangleShape wall(sf::Vector2f(scaledSize, 1));
        wall.setFillColor(colorConfig_.wall);
        if (x == maze_->getEndX() && y == maze_->getEndY()) {
            wall.setFillColor(colorConfig_.wallEnd);
        } else if (x == maze_->getStartX() && y == maze_->getStartY()) {
            wall.setFillColor(colorConfig_.wallStart);
        }
        const Cell *neighbor = nullptr;
        if (orientation == MAZE_CELL_TOP) {
            neighbor = maze_->getCell(x, y - 1);
            if (neighbor->getWall(MAZE_CELL_BOTTOM)) y--;
            wall.setPosition(static_cast<float>(x) * scaledSize,
                             static_cast<float>(y) * scaledSize + scaledSize);
        } else if (orientation == MAZE_CELL_RIGHT) {
            neighbor = maze_->getCell(x + 1, y);
            wall.setSize(sf::Vector2f(1, scaledSize));
            wall.setPosition(static_cast<float>(x) * scaledSize + scaledSize,
                             static_cast<float>(y) * scaledSize);
        } else if (orientation == MAZE_CELL_BOTTOM) {
            neighbor = maze_->getCell(x, y + 1);
            wall.setPosition(static_cast<float>(x) * scaledSize,
                             static_cast<float>(y) * scaledSize + scaledSize);
        } else {
            neighbor = maze_->getCell(x - 1, y);
            if (maze_->getCell(x - 1, y)->getWall(MAZE_CELL_RIGHT)) x--;
            wall.setSize(sf::Vector2f(1, scaledSize));
            wall.setPosition(static_cast<float>(x) * scaledSize + scaledSize,
                             static_cast<float>(y) * scaledSize);
        }
        if (neighbor->getX() == maze_->getEndX() &&
            neighbor->getY() == maze_->getEndY()) {
            wall.setFillColor(colorConfig_.wallEnd);
        } else if (neighbor->getX() == maze_->getStartX() &&
                   neighbor->getY() == maze_->getStartY()) {
            wall.setFillColor(colorConfig_.wallStart);
        }
        renderWindow_->draw(wall);
    }
}

void Show::drawFrontier_(const Cell *cell, const int orientation) const {
    const float scaledSize = cellSize_ * zoomLevel_;
    sf::RectangleShape frontier(sf::Vector2f(scaledSize, 1));
    if (orientation == MAZE_CELL_TOP) {
        frontier.setPosition(static_cast<float>(cell->getX()) * scaledSize, 0);
    } else if (orientation == MAZE_CELL_RIGHT) {
        frontier.setSize(sf::Vector2f(1, scaledSize));
        frontier.setPosition(
            static_cast<float>(maze_->getWidth()) * scaledSize - 1,
            static_cast<float>(cell->getY()) * scaledSize);
    } else if (orientation == MAZE_CELL_BOTTOM) {
        frontier.setPosition(
            static_cast<float>(cell->getX()) * scaledSize,
            static_cast<float>(maze_->getHeight()) * scaledSize - 1);
    } else {
        frontier.setSize(sf::Vector2f(1, scaledSize));
        frontier.setPosition(0, static_cast<float>(cell->getY()) * scaledSize);
    }
    frontier.setFillColor(cell->getX() == maze_->getEndX() &&
                                  cell->getY() == maze_->getEndY()
                              ? colorConfig_.wallEnd
                          : cell->getX() == maze_->getStartX() &&
                                  cell->getY() == maze_->getStartY()
                              ? colorConfig_.wallStart
                              : colorConfig_.wall);
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
    refreshShow(show, argc, argv, true);
}

void refreshShow(Show *show, const int argc, Cell *argv[], const bool lowFreq) {
    if (show == nullptr) return;
    if (!show->isOpen()) return;
    if (argc <= 0) return;
    show->eventHandler();
    for (int i = 0; i < argc; i++) {
        if (argv[i] != nullptr) show->drawCell(argv[i]);
    }
    if (lowFreq || !show->getLowFreq()) show->refreshDisplay();
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

void Show::resetValues() { // NOLINT
    // Réinitialisation des paramètres par défaut
    std::ifstream envFile(MAZE_ENV_FILE);
    if (envFile.is_open()) {
        std::string line;
        unsigned int framerate = 60;
        float delay = 0.0f;
        bool lowFreq = false;
        while (std::getline(envFile, line)) {
            if (line.find("FRAMERATE=") == 0) {
                framerate = std::stoi(line.substr(10));
            } else if (line.find("DELAY_SHOW=") == 0) {
                delay = std::stof(line.substr(11));
            } else if (line.find("LOW_FREQUENCY=") == 0) {
                if (line.substr(14) == "true") {
                    lowFreq = true;
                } else if (line.substr(14) == "false") {
                    lowFreq = false;
                } else {
                    std::cerr << "Error: incorrect value for LOW_FREQUENCY in "
                                 ".env file."
                              << std::endl;
                    exit(MAZE_COMMAND_ERROR);
                }
            }
        }
        setRefreshRate(framerate);
        setDelay(delay);
        setLowFreq(lowFreq);
        envFile.close();
    } else {
        // Si le fichier .env n'existe pas, utilisez les valeurs par défaut
        setRefreshRate(60);
        setDelay(0.0f);
        setLowFreq(false);
    }

    // Réinitialisation du niveau de zoom
    zoomLevel_ = 1.0f;

    // Réinitialisation du drapeau de déplacement
    isDragging_ = false;

    // Réinitialisation de la position de la souris et du coin en haut à gauche
    lastMousePosition_ = sf::Vector2i(0, 0);
    // Le coin en haut à gauche du labyrinthe est à (0, 0).
    lastViewCenter_ = sf::Vector2f(0, 0);

    // Réinitialisation du RENDER WINDOW View
    if (renderWindow_ != nullptr) {
        // Calcul de la taille de la vue en fonction de la taille des cellules
        float viewWidth = static_cast<float>(maze_->getWidth()) * cellSize_;
        float viewHeight = static_cast<float>(maze_->getHeight()) * cellSize_;

        // Création d'une nouvelle vue centrée sur le coin en haut à gauche
        sf::View defaultView(sf::FloatRect(0, 0, viewWidth, viewHeight));

        // Échelle initialisée à 1.0f
        defaultView.zoom(1.0f);

        // Ajustement de la taille de la fenêtre
        renderWindow_->setSize(sf::Vector2u(static_cast<unsigned int>(viewWidth), static_cast<unsigned int>(viewHeight)));

        // Applique la nouvelle vue
        renderWindow_->setView(defaultView);

        // Efface l'écran
        clearBlack();
        refreshMaze();
    }
}

void Show::loadColorsFromEnv_(const std::string &key, sf::Color &color) {
    std::ifstream envFile(MAZE_ENV_FILE);
    std::string line;

    while (std::getline(envFile, line)) {
        if (line.find(key + "=") == 0) {
            std::string values = line.substr(key.length() + 1);
            Queue tokens = splitString_(values, ',');
            uint8_t r = 0, g = 0, b = 0;
            int count = 0;

            while (!tokens.empty()) {
                auto tokenPtr = static_cast<std::string *>(tokens.front());
                try {
                    uint8_t value = std::stoul(*tokenPtr);
                    switch (count) {
                        case 0:
                            r = value;
                            break;
                        case 1:
                            g = value;
                            break;
                        case 2:
                            b = value;
                            break;
                        default:;
                    }
                    count++;
                } catch (const std::invalid_argument &) {
                    // Gestion d'erreur si un token n'est pas un nombre valide
                    std::cerr
                        << "Erreur lors du parsage de la couleur : " << key
                        << std::endl;
                    break;
                }

                // Libère la mémoire de l'objet string
                delete tokenPtr;
                tokens.pop();
            }

            if (count >= 3) {
                color = sf::Color(r, g, b);
            }
            break;
        }
    }
}

Queue Show::splitString_(const std::string &str, const char delimiter) {
    Queue q;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        // Extrait la sous-chaîne de `start` à `end`
        const std::string token = str.substr(start, end - start);
        // Alloue de la mémoire pour la chaîne et ajoute à la queue
        q.push(new std::string(token));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    // Ajoute le dernier token après le dernier délimiteur
    const std::string lastToken = str.substr(start);
    q.push(new std::string(lastToken));

    return q;
}