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

void FontManager::DrawText(const std::string& id, const std::string& text,
                           SDL_Color color, int x, int y, SDL_Renderer* renderer) {
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

    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

//  hiệu ứng phát sáng
void FontManager::DrawTextWithGlow(const std::string& id, const std::string& text,
                                   SDL_Color mainColor, SDL_Color glowColor,
                                   int x, int y, SDL_Renderer* renderer, int intensity) {
    if (!m_fontMap.count(id)) {
        std::cerr << "Font ID not found: " << id << std::endl;
        return;
    }

    TTF_Font* font = m_fontMap[id];

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), mainColor);
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

    SDL_Rect dstRect = { x, y, surface->w, surface->h };

    // lớp phát sáng mờ xung quanh chữ
    for (int dx = -intensity; dx <= intensity; ++dx) {
        for (int dy = -intensity; dy <= intensity; ++dy) {
            if (dx * dx + dy * dy <= intensity * intensity) {
                SDL_SetTextureColorMod(texture, glowColor.r, glowColor.g, glowColor.b);
                SDL_SetTextureAlphaMod(texture, glowColor.a);
                SDL_Rect glowRect = { x + dx, y + dy, surface->w, surface->h };
                SDL_RenderCopy(renderer, texture, nullptr, &glowRect);
            }
        }
    }

    // lớp chữ chính sáng rõ nét
    SDL_SetTextureColorMod(texture, mainColor.r, mainColor.g, mainColor.b);
    SDL_SetTextureAlphaMod(texture, mainColor.a);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void FontManager::ClearFromTextureMap(const std::string& id) {
    if (m_fontMap.count(id)) {
        TTF_CloseFont(m_fontMap[id]);
        m_fontMap.erase(id);
    }
}

void FontManager::Clean() {
    for (auto const& [key, val] : m_fontMap) {
        TTF_CloseFont(val);
    }
    m_fontMap.clear();
}
