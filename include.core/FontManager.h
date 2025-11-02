#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL_ttf.h>
#include <string>
#include <map>

class FontManager {
public:
    static FontManager* Instance();

    bool Load(const std::string& id, const std::string& path, int size);

    void DrawText(const std::string& id, const std::string& text,
                  SDL_Color color, int x, int y, SDL_Renderer* renderer);

    //  hiệu ứng phát sáng LED
    void DrawTextWithGlow(const std::string& id, const std::string& text,
                          SDL_Color mainColor, SDL_Color glowColor,
                          int x, int y, SDL_Renderer* renderer, int intensity = 6);

    void ClearFromTextureMap(const std::string& id);
    void Clean();

private:
    FontManager() {}
    ~FontManager() {}
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    static FontManager* s_instance;
    std::map<std::string, TTF_Font*> m_fontMap;
};

#endif // FONTMANAGER_H
