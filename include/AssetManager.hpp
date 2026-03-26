#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <string>
// #include <iostream>

class AssetManager {
public:
    // 构造函数需要 renderer 引用，用于加载纹理
    AssetManager(SDL_Renderer* renderer);
    
    // 析构函数负责清理所有缓存的纹理
    ~AssetManager();

    // 加载并缓存纹理：如果已存在则直接返回，否则加载新纹理
    SDL_Texture* GetTexture(const std::string& id);

    // 辅助方法：手动添加路径（建立 ID 与 文件路径的映射）
    void AddTexture(const std::string& id, const std::string& path);

private:
    SDL_Renderer* m_renderer;
    std::map<std::string, SDL_Texture*> m_textures;
    std::map<std::string, std::string> m_paths;
};