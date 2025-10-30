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
    //check danh sách gạch xem bóng có đụng trúng viên nào không
    std::vector<Brick>& GetBricks() { return m_bricks; }
    // check viên nào trong map còn sống
    bool AllCleared() const;

private:
    std::vector<Brick> m_bricks;
    int m_tileW, m_tileH;
};

#endif // LEVEL_H
