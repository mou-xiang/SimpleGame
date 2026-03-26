#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "AssetManager.hpp"

class Game {
public:
  Game();
  ~Game();

  bool init(const char* title, int width, int height);
  void handleEvents();
  void update();
  void render();
  void clean();

  bool running()  { return isRunning; }

private:
  int m_windowWidth;
  int m_windowHeight;
  bool isRunning;
  SDL_Window* window;
  SDL_Renderer* renderer;
  AssetManager* assets;
  //! 时间控制
  Uint32 lastTick;
  float DeltaTime;
  //! 游戏对象
  Player* mainPlayer;

};