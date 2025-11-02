#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL.h>
#include <string>
#include <map>

class TextureManager {
public:
    static TextureManager* Instance();

    bool Load(const std::string& id, const std::string& file, SDL_Renderer* renderer);
    void Draw(const std::string& id, int x, int y, int w, int h, SDL_Renderer* renderer);
    void DrawFrame(const std::string& id, int x, int y, int w, int h,
                   int row, int frame, SDL_Renderer* renderer, double angle = 0.0);
    void ClearFromTextureMap(const std::string& id);
    void Clean();

private:
    TextureManager() {}
    std::map<std::string, SDL_Texture*> m_textureMap;
    static TextureManager* s_instance;
};
#endif
