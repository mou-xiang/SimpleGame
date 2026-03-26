#include "Game.hpp"
#include "AssetManager.hpp"

Game::Game()
    : window(nullptr), renderer(nullptr), assets(nullptr), isRunning(false),
      DeltaTime(0) {}

bool Game::init(const char *title, int width, int height) {
  m_windowHeight = height;
  m_windowWidth = width;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    return false;
  if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    return false;
  //! 初始化窗口和渲染器
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  assets = new AssetManager(renderer);

  //! 初始化游戏角色并加载纹理
  // SDL_Texture* pTex = IMG_LoadTexture(renderer, "../assets/img.jpg");
  assets->AddTexture("player", "../assets/runner.png");
  assets->AddTexture("obs", "../assets/obs.png");
  mainPlayer = new Player(width / 3, height / 3 * 2, 100, 100,
                          assets->GetTexture("player"));

  lastTick = SDL_GetTicks();
  isRunning = true;
  return true;
}

void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      isRunning = false;
    mainPlayer->handleInput(event);
  }
}

void Game::update() {
  Uint32 currentTick = SDL_GetTicks();
  DeltaTime = (currentTick - lastTick) / 1000.0f;
  lastTick = currentTick;
  if (DeltaTime > 0.05f)
    DeltaTime = 0.05f;

  // 2. 障碍物生成逻辑
  spawnTimer += DeltaTime;
  if (spawnTimer >= spawnInterval) {
    int lane = rand() % 3; // 随机 0, 1, 2 轨道

    // 创建新的 Obstacle 并加入容器
    // 注意：这里需要你已经加载好的纹理
    SDL_Texture *obsTex = IMG_LoadTexture(renderer, "../obs.png");
    gameEntities.push_back(
        new Obstacle(lane, 1000.0f, assets->GetTexture("obs")));

    spawnTimer = 0;
  }

  // 3. 更新所有障碍物并处理“越界回收”
  for (auto it = gameEntities.begin(); it != gameEntities.end();) {
    (*it)->update(DeltaTime);

    // 假设你在 Obstacle 类里写了 getZ() 方法
    // 如果障碍物跑到了玩家身后（z < 0），就删掉它
    if (static_cast<Obstacle *>(*it)->getZ() < -50.0f) {
      delete *it;                  // 释放内存
      it = gameEntities.erase(it); // 从 vector 中移除
    } else {
      ++it;
    }
  }

  mainPlayer->update(DeltaTime);
}

void Game::render() {
  //! 清空上一帧画面
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  //! 画路面分界线
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawLine(renderer, m_windowWidth / 2, m_windowHeight / 2 - 200, 0,
                     m_windowHeight);
  SDL_RenderDrawLine(renderer, m_windowWidth / 2, m_windowHeight / 2 - 200,
                     m_windowWidth / 3, m_windowHeight);
  SDL_RenderDrawLine(renderer, m_windowWidth / 2, m_windowHeight / 2 - 200,
                     m_windowWidth / 3 * 2, m_windowHeight);
  SDL_RenderDrawLine(renderer, m_windowWidth / 2, m_windowHeight / 2 - 200,
                     m_windowWidth, m_windowHeight);

  //! 渲染障碍物
  for (auto e : gameEntities) {
    e->render(renderer);
  }
  mainPlayer->render(renderer);

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  delete mainPlayer;
  //! 释放障碍物
  for (auto e : gameEntities) {
    delete e;
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  SDL_Log("Game Cleaned");
}

Game::~Game() { clean(); }