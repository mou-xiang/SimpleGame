#include "Game.hpp"

Game::Game()  : window(nullptr), renderer(nullptr), isRunning(false), DeltaTime(0)  {}

bool Game::init(const char* title, int width, int height) {
  m_windowHeight = height;
  m_windowWidth = width;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)  return false;
  if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) return false;
  //! 初始化窗口和渲染器
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  //! 初始化游戏角色
  SDL_Texture* pTex = IMG_LoadTexture(renderer, "../assets/img.jpg");
  mainPlayer = new Player(width / 3, height / 3 * 2, 100, 100, pTex);

  lastTick = SDL_GetTicks();
  isRunning = true;
  return true;
}

void Game::handleEvents(){
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) isRunning = false;
    mainPlayer->handleInput(event);
  }
}

void Game::update() {
  Uint32 currentTick = SDL_GetTicks();
  DeltaTime = (currentTick - lastTick) / 1000.0f;
  lastTick = currentTick;
  if (DeltaTime > 0.05f)  DeltaTime = 0.05f;

  mainPlayer->update(DeltaTime);
}

void Game::render() {
  //! 清空上一帧画面
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  //! 画路面分界线
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawLine(renderer, m_windowWidth/2, m_windowHeight/2 - 200, 0,
                       m_windowHeight);
    SDL_RenderDrawLine(renderer, m_windowWidth/2, m_windowHeight/2 - 200,
                       m_windowWidth / 3, m_windowHeight);
    SDL_RenderDrawLine(renderer, m_windowWidth/2, m_windowHeight/2 - 200,
                       m_windowWidth / 3 * 2, m_windowHeight);
    SDL_RenderDrawLine(renderer, m_windowWidth/2, m_windowHeight/2 - 200,
                       m_windowWidth, m_windowHeight);

    mainPlayer->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::clean()  {
  delete mainPlayer;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  SDL_Log("Game Cleaned");
}

Game::~Game() { clean(); }