#include "core/FontManager.h"
#include <iostream>

FontManager* FontManager::s_instance = nullptr;

FontManager* FontManager::Instance() {
    if (!s_instance) {
        s_instance = new FontManager();
    }
    return s_instance;
}

bool FontManager::Load(const std::string& id, const std::string& path, int size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << path << " - " << TTF_GetError() << std::endl;
        return false;
    }
    m_fontMap[id] = font;
    return true;
}

void FontManager::DrawText(const std::string& id, const std::string& text, SDL_Color color, int x, int y, SDL_Renderer* renderer) {
    if (!m_fontMap.count(id)) {
        std::cerr << "Font ID not found: " << id << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(m_fontMap[id], text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create surface from text: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void FontManager::Clean() {
    for (auto const& [key, val] : m_fontMap) {
        TTF_CloseFont(val);
    }
    m_fontMap.clear();
}
