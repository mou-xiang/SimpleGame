#pragma once

//! 静态工具类，投影成伪3D
class Projection{
  static const int SCREEN_W = 1200;
  static const int SCREEN_H = 900;
  static const int VANISH_Y = 250;

  struct ScreenPos {
    int x, y, size;
  };
};