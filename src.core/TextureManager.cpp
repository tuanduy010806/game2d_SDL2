#include "core/TextureManager.h"
#include <SDL_image.h>
#include <iostream>

TextureManager* TextureManager::s_instance = nullptr;

TextureManager* TextureManager::Instance() {
    if (!s_instance) {
        s_instance = new TextureManager();
    }
    return s_instance;
}

bool TextureManager::Load(const std::string& id, const std::string& file, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(file.c_str());
    if (!tempSurface) {
        std::cerr << "Failed to load image: " << file << " - " << IMG_GetError() << std::endl;
        return false;
    }
    // sao chép ảnh từ tempSurface sang texture rồi giải phóng tempSuface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    //lưu id của ảnh vào textureMap: lập danh mục tài nguyên
    if (texture) {
        m_textureMap[id] = texture;
        return true;
    }

    std::cerr << "Failed to create texture from surface: " << file << " - " << SDL_GetError() << std::endl;
    return false;
}

void TextureManager::Draw(const std::string& id, int x, int y, int w, int h, SDL_Renderer* renderer) {
    if (m_textureMap.count(id) == 0) return;

    SDL_Rect srcRect = {0, 0, 0, 0};
    SDL_Rect destRect = {x, y, w, h};
    SDL_QueryTexture(m_textureMap[id], NULL, NULL, &srcRect.w, &srcRect.h);

    SDL_RenderCopy(renderer, m_textureMap[id], &srcRect, &destRect);
}

void TextureManager::ClearFromTextureMap(const std::string& id) {
    if (m_textureMap.count(id)) {
        SDL_DestroyTexture(m_textureMap[id]);
        m_textureMap.erase(id);
    }
}

void TextureManager::Clean() {
    for (auto const& [key, val] : m_textureMap) {
        SDL_DestroyTexture(val);
    }
    m_textureMap.clear();
}
