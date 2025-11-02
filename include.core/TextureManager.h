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
    void ClearFromTextureMap(const std::string& id);
    void Clean();
private:
    TextureManager() {}
    ~TextureManager() {}
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    std::map<std::string, SDL_Texture*> m_textureMap;
    static TextureManager* s_instance;
};

#endif // TEXTUREMANAGER_H
