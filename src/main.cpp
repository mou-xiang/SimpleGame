// #include "BackGround.hpp"
#include "Entity.hpp"
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>

// Uint32 getDeltaTime();
SDL_Texture *loadTexture(const std::string &, SDL_Renderer *);
//! 定义初始化函数
void g_Init();

constexpr int windowWidth = 1200;
constexpr int windowHeight = 900;

constexpr int windowCenterX = windowWidth / 2;
constexpr int windowCenterY = windowHeight / 2;

int main(int argc, char *argv[]) {
  //! 初始化SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  //! 初始化IMG
  if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
    SDL_Log("SDL_image初始化失败");
    exit(1);
  }
  //! 创建窗口
  SDL_Window *window = SDL_CreateWindow("SimpleGame", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, windowWidth,
                                        windowHeight, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  //! 创建渲染器
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  //! 创建并初始化游戏角色
  // SDL_Surface *temp = SDL_LoadBMP("../img.bmp");
  // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temp);
  Player mainPlayer{windowWidth / 2, windowHeight / 3 * 2, 100, 100,
                    loadTexture("../img.jpg", renderer)};
  // SDL_FreeSurface(temp);

  //! 游戏结束条件
  bool isquit = false;
  SDL_Event event;
  //! 时间步长控制
  Uint32 lastTick = SDL_GetTicks();
  float DeltaTime = 0.0f;
  //! 游戏循环
  while (!isquit) {
    //? 计算游戏帧
    Uint32 currentTick = SDL_GetTicks();
    DeltaTime = (currentTick - lastTick) / 1000.0f;
    lastTick = currentTick;
    // SDL_Log("DeltaTime = ");
    // std::cout << DeltaTime << '\n';
    //! 检测DeltaTime过大
    if (DeltaTime > 0.05f)
      DeltaTime = 0.05f;

    //! 处理键盘按下事件
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        isquit = true;
      mainPlayer.handleInput(event);
      SDL_Log("进行了一个读取操作循环");
    }

    //! 更新玩家状态
    mainPlayer.update(DeltaTime);
    //! 清除上一帧画面
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //! 绘制地面
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(renderer, windowCenterX, windowCenterY - 200, 0,
                       windowHeight);
    SDL_RenderDrawLine(renderer, windowCenterX, windowCenterY - 200,
                       windowWidth / 3, windowHeight);
    SDL_RenderDrawLine(renderer, windowCenterX, windowCenterY - 200,
                       windowWidth / 3 * 2, windowHeight);
    SDL_RenderDrawLine(renderer, windowCenterX, windowCenterY - 200,
                       windowWidth, windowHeight);
    //! 渲染玩家
    mainPlayer.render(renderer);

    SDL_RenderPresent(renderer);
  }

  //! 释放window和renderer
  // SDL_Delay(3000); // 显示3秒
  // SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  SDL_Log("内存已释放");

  return 0;
}
//! 直接调用SDL_image库加载纹理
SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *renderer) {
  //! 使用IMG_LoadTexture加载图片
  SDL_Texture *newTexture = IMG_LoadTexture(renderer, path.c_str());
  if (newTexture == nullptr)
    SDL_Log("图片加载失败");
  return newTexture;
}
