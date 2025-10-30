#include "objects/Level.h"

static int map1[10][15] = {
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,1,1,1,1,1,1,1,1,1,1,1,0,3},
    {3,0,2,2,2,2,2,2,2,2,2,2,2,0,3},
    {3,0,1,2,1,2,1,2,1,2,1,2,1,0,3},
    {3,0,0,1,1,1,1,1,1,1,1,1,0,0,3},
    {3,0,0,2,2,2,2,2,2,2,2,2,0,0,3},
    {3,0,0,0,1,1,1,1,1,1,1,0,0,0,3},
    {3,0,0,0,0,2,2,2,2,2,0,0,0,0,3},
    {3,0,0,0,0,0,1,1,1,0,0,0,0,0,3},
    {3,0,0,3,3,3,3,3,3,3,3,0,0,3,3}
};



static int map2[10][15] = {
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,1,1,1,1,1,1,2,2,2,1,1,1,0,3},
    {3,2,2,2,2,2,1,1,1,1,2,2,2,0,3},
    {3,1,1,1,2,3,3,3,3,2,1,1,1,0,3},
    {3,2,2,2,1,1,2,2,1,1,2,2,2,0,3},
    {3,1,1,0,0,0,0,0,0,0,0,1,1,0,3},
    {3,2,1,0,2,2,1,2,1,2,2,0,2,0,3},
    {3,1,2,0,1,1,2,1,2,1,1,0,1,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,3,0,0,3,0,0,3,0,0,3,0,3}
};

static int map3[10][15] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,3,3,3,3,0,0,0,0,0,0,3,3,3,3}
};

// kích thước gạch
Level::Level() : m_tileW(53), m_tileH(30) {}

void Level::LoadMap(int mapIndex, SDL_Renderer* renderer) {
    m_bricks.clear();

    static int (*maps[])[15] = { map1, map2, map3};
    // Chọn map theo mapIndex
    int (*selectedMap)[15] = maps[mapIndex % 3];
    const int rows = 10;
    const int cols = 15;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int val = selectedMap[row][col];
            if (val == 0) continue; // 0 = khoảng trống
            std::string texture;
            int hp = 0;
            switch (val) {
                case 1:
                    texture = "brickeasy";
                    hp = 1;
                    break;
                case 2:
                    texture = "brickmedium";
                    hp = 2;
                    break;
                case 3:
                default:
                    texture = "brickhard"; // Không phá được
                    hp = -1;
                    break;
            }
            m_bricks.emplace_back(
                col * m_tileW,          // x
                row * m_tileH + 50,     // y
                m_tileW - 2,            // tạo khe gạch
                m_tileH - 2,            // height
                hp,
                texture
            );
        }
    }
}

void Level::Draw(SDL_Renderer* renderer) {
    for (auto& brick : m_bricks) {
        brick.Draw(renderer);
    }
}

bool Level::AllCleared() const {
    for (const auto& b : m_bricks) {
        //  thắng:tất cả gạch (hp > 0) đã bị phá
        if (b.IsAlive()) return false;
    }
    return true;
}
