#pragma once

#include <SDL.h>

//! 基类 实体
class Entity {
protected:
  float x, y;
  int w, h;
  SDL_Texture* texture;
public:
  virtual void update(float dt) = 0;
  void render(SDL_Renderer*);
};

class Player : public Entity {
private:
  int8_t currentLine = 1; //? 左0，中1，右2
  float targetX = 400.0f;
  const float moveSpeed = 10.0f;

public:
  Player(int, int, int, int, SDL_Texture*);
  void handleInput(SDL_Event&);   //? 处理移动事件并计算目标x坐标
  void update(float dt) override; //? 实现移动
};

