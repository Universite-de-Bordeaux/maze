#ifndef SHOW_HPP
#define SHOW_HPP

#include <SFML/Graphics.hpp>
#include "maze.hpp" // Incluez votre fichier de header Maze.hpp

class Show {
public:
    Show(Maze* maze);
    void create();
    void update();
    void destroy();
    bool isOpen();

private:
    Maze* maze_;
    sf::RenderWindow* window_;
    int cellSize_;
};

#endif  // SHOW_HPP
