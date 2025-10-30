#ifndef PADDLE_H
#define PADDLE_H
#include <SDL.h>
#include <string>

class Paddle {
public:
    Paddle(int x, int y, int w, int h, const std::string& textureID);
    void Update(int mouseX, int windowWidth);
    void Draw(SDL_Renderer* renderer);
    SDL_Rect GetRect() const { return m_rect; }
private:
    SDL_Rect m_rect;
    std::string m_textureID;
};

#endif // PADDLE_H
