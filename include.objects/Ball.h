#ifndef BALL_H
#define BALL_H
#include <SDL.h>
#include <string>
#include "core/TextureManager.h"

class Ball {
public:
    Ball(float x, float y, int size, const std::string& textureID);

    void Update(float deltaTime, int screenW, int screenH);
    void Draw(SDL_Renderer* renderer);
    void Reset(float x, float y);
    void BounceX();
    void BounceY();

    SDL_Rect GetRect() const;
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }

    void SetX(float x) { m_x = x; }
    void SetY(float y) { m_y = y; }

    void SetVelocity(float vx, float vy);
    float GetVelX() const { return m_velX; }
    float GetVelY() const { return m_velY; }
    int GetSize() const { return m_size; }
private:
    float m_x, m_y;
    float m_velX, m_velY;
    int m_size;
    std::string m_textureID;
};
#endif
