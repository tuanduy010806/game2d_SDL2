#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "objects/Brick.h"
#include <SDL.h>

class Level {
public:
    Level();
    void LoadMap(int mapIndex, SDL_Renderer* renderer);
    void Draw(SDL_Renderer* renderer);
    std::vector<Brick>& GetBricks() { return m_bricks; }
    bool AllCleared() const;

private:
    std::vector<Brick> m_bricks;
    int m_tileW, m_tileH;
};

#endif // LEVEL_H
