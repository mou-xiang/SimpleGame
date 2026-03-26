#include "Entity.hpp"
#include "Utils.hpp"  

void Entity::render(SDL_Renderer *renderer) {
  SDL_Rect rect = {(int)x - w / 2, (int)y - h / 2, w, h};
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Player::handleInput(SDL_Event &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_LEFT && currentLine > 0)
      currentLine--;
    if (event.key.keysym.sym == SDLK_RIGHT && currentLine < 2)
      currentLine++;
    if (event.key.keysym.sym == SDLK_UP && !isJump) {
      jumpV = JUMP_FORCE;
      isJump = true;
    }
    //! 计算目标位置
    targetX = 400.0f + currentLine * 200.0f;
  }
}

void Player::update(float dt) {
  x += (targetX - x) * moveSpeed * dt;
  //! 实现跳跃
  if (isJump) {
    //! 物理运动实现
    jumpV += GRAVITY * dt;
    y += jumpV * dt;

    //! 落地检测
    if (y >= GROUND_Y) {
      y = GROUND_Y;
      jumpV = 0;
      isJump = false;
    }
  }
}

Player::Player(int setX, int setY, int setW, int setH, SDL_Texture *setTexture)
    : Entity(setX, setY, setW, setH, setTexture) {
  // x = setX - static_cast<float>(w) / 2;
  // y = setY - static_cast<float>(h) / 2;
  // x = setX;
  // y = setY;
  // w = setW;
  // h = setH;
  // texture = setTexture;
  // GROUND_Y = setY;
  SDL_Log("Player created");
}

void Obstacle::updateVisuals() {
  auto pos = Projection::project(m_line, m_z, 100);
  x = pos.x;
  y = pos.y;
  w = h = pos.size;
}

void Obstacle::update(float dt) {
  m_z -= speed * dt;
  updateVisuals();
}