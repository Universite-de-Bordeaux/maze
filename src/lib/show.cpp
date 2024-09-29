#include "show.hpp"
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "var.hpp"

void showOld(Maze *maze) {
    std::cout << "Show" << std::endl;
    std::cout << maze->getWidth() << " x " << maze->getHeight() << std::endl;
    for (int y = 0; y < maze->getHeight(); y++) {
        for (int x = 0; x < maze->getWidth(); x++) {
            Cell* cell = maze->getCell(x, y);
            if (cell->getWall(cell->NeighborsEnum::RIGHT)) {
                std::cout << x << " " << y << " " << "V" << std::endl;
            }
            if (cell->getWall(cell->NeighborsEnum::BOTTOM)) {
                std::cout << x << " " << y << " " << "H" << std::endl;
            }
        }
    }
}

void show(Maze *maze) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(MAZE_SDL_ERROR);
    }

    SDL_Window *win = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        maze->getWidth()*10, maze->getHeight()*10, SDL_WINDOW_SHOWN);
    if(win == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(MAZE_SDL_ERROR);
    }

    SDL_Delay(1000);

    SDL_DestroyWindow(win);

    SDL_Quit();
}
