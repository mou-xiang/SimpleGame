#pragma once

//! 静态工具类，投影成伪3D
class Projection{
public:
  static const int SCREEN_W = 1200;
  static const int SCREEN_H = 900;
  static const int VANISH_X = SCREEN_W / 2;
  static const int VANISH_Y = SCREEN_H / 2 - 200;

  struct ScreenPos {
    int x, y, size;
  };

  // line: 0, 1, 2; z: 深度; baseSize: 基础大小
    static ScreenPos project(int line, float z, int baseSize) {
        float perspective = 400.0f;
        float scale = perspective / (perspective + z);

        // 这里的 400.0f 是逻辑上的轨道间距
        float logicX = (line - 1) * 400.0f; 
        
        int x = (int)(VANISH_X + (logicX * scale));
        int y = (int)(VANISH_Y + ( (SCREEN_H - VANISH_Y) * scale ));
        int size = (int)(baseSize * scale);

        return { x, y, size };
    }
};