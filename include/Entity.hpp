#pragma once

// #include "Utils.hpp"
#include <SDL.h>


//! 基类 实体
class Entity {
protected:
  float x, y;
  int w, h;
  SDL_Texture *texture;

public:
  Entity(float x, float y, int w, int h, SDL_Texture *Tex)
      : x(x), y(y), w(w), h(h), texture(Tex) {}

  virtual ~Entity() {}

  virtual void update(float dt) = 0;
  virtual void render(SDL_Renderer *);
};

class Player : public Entity {
private:
  int8_t currentLine = 1; //? 左0，中1，右2
  float targetX = 400.0f;
  const float moveSpeed = 10.0f;
  float jumpV = 0.0f;  //? 竖直速度
  bool isJump = false; //? 跳跃状态

  const float GRAVITY = 1500.0f;
  const float JUMP_FORCE = -600.0f;
  float GROUND_Y = y;

public:
  Player(int, int, int, int, SDL_Texture *);
  void handleInput(SDL_Event &);  //? 处理移动事件并计算目标x坐标
  void update(float dt) override; //? 实现移动
};

class Obstacle : public Entity {
private:
  int8_t m_line;
  float m_z;
  float speed = 400.0f;
  //! 障碍物伪3D实现
  void updateVisuals();

public:
  Obstacle(int line, float z, SDL_Texture *Tex)
      : Entity(0, 0, 100, 100, Tex), m_line(line), m_z(z) {
    updateVisuals();
  };

  void update(float dt) override;

  float getZ() const { return m_z; }
};