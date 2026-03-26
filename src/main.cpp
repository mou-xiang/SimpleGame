// #include "BackGround.hpp"
#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

constexpr int windowWidth = 1200;
constexpr int windowHeight = 900;

constexpr int windowCenterX = windowWidth / 2;
constexpr int windowCenterY = windowHeight / 2;

int main(int argc, char *argv[]) {
  Game *game = new Game();

  if (game->init("SDL Running", 1200, 900)) {
    while (game->running()) {
      game->handleEvents();
      game->update();
      game->render();
    }
  }

  delete game;

  return 0;
}
