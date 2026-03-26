#include "AssetManager.hpp"
#include <iostream>

AssetManager::AssetManager(SDL_Renderer* renderer) : m_renderer(renderer) {}

AssetManager::~AssetManager() {
    // 自动清理：遍历 map 销毁所有纹理
    for (auto const& [id, texture] : m_textures) {
        if (texture) {
            SDL_DestroyTexture(texture);
            std::cout << "Released resource: " << id << std::endl;
        }
    }
    m_textures.clear();
}

void AssetManager::AddTexture(const std::string& id, const std::string& path) {
    m_paths[id] = path;
}

SDL_Texture* AssetManager::GetTexture(const std::string& id) {
    // 1. 检查是否已经加载过
    if (m_textures.find(id) != m_textures.end()) {
        return m_textures[id];
    }

    // 2. 如果没加载过，根据路径加载
    if (m_paths.find(id) != m_paths.end()) {
        SDL_Texture* tex = IMG_LoadTexture(m_renderer, m_paths[id].c_str());
        if (tex) {
            m_textures[id] = tex;
            return tex;
        }
    }

    std::cerr << "Failed to get texture: " << id << std::endl;
    return nullptr;
}