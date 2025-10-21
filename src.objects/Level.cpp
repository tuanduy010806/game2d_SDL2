#include "objects/Level.h"

// 2 map gạch gốc kích thước 10x10 tạo ra ban đầu
static int map1[10][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,1,2,3,0,0,0,0,0}
};

static int map2[10][10] = {
    {0,1,2,2,2,2,2,2,1,0},
    {1,1,2,0,1,0,0,2,1,1},
    {1,2,2,2,0,0,2,2,2,1},
    {0,1,1,2,0,1,2,1,1,0},
    {1,2,1,0,0,0,0,1,2,1},
    {0,0,1,2,1,0,2,1,0,0},
    {1,1,0,2,0,0,2,0,1,1},
    {0,1,1,2,0,1,2,1,1,0},
    {1,0,1,2,0,0,2,1,0,1},
    {3,3,3,3,1,1,3,3,3,3}
};
// kích thước của gạch
Level::Level() : m_tileW(80), m_tileH(30) {}

void Level::LoadMap(int mapIndex, SDL_Renderer* renderer) {
    m_bricks.clear(); // loại bỏ hoàn toàn map gạch cũ để tạo màn hình trống up map khác lên khi bắt đầu chơi mới
//con trỏ selectedMap trỏ tới một khối bộ nhớ là một mảng chứa 10 số nguyên
    int (*selectedMap)[10] = (mapIndex == 0) ? map1 : map2;

    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            int val = selectedMap[row][col];
            if (val == 0) continue;

            std::string texture;
            switch (val) {
                case 1: texture = "brickeasy"; break;
                case 2: texture = "brickmedium"; break;
                default: texture = "brickhard"; break;
            }

            m_bricks.emplace_back(col * m_tileW, row * m_tileH + 10, m_tileW - 2, m_tileH - 2, val, texture);
            //vtri toạ độ x, y; chiều rộng, chiều cao, ảnh
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
        if (b.IsAlive()) return false;
    }
    return true;
}
