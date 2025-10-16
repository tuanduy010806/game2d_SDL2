#ifndef BRICK_H
#define BRICK_H

#include <SDL.h>
#include <string>

class Brick {
public:
    Brick(int x, int y, int w, int h, int hp, const std::string& textureID);

    void Draw(SDL_Renderer* renderer);
    bool IsAlive() const { return m_hp > 0; }
    void Hit();
    SDL_Rect GetRect() const { return m_rect; }

private:
    SDL_Rect m_rect;
    int m_hp;
    std::string m_textureID;
};

#endif // BRICK_H
