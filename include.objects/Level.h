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

    //truy cập vào danh sách tất cả các viên gạch để kiểm tra xem quả bóng có đụng trúng viên nào không
    std::vector<Brick>& GetBricks() { return m_bricks; }

    //kiểm tra xem viên nào trong map còn sống, const để đảm bảo chỉ đọc qua chứ không thay đổi dữ liệu của map
    bool AllCleared() const;

private:
    std::vector<Brick> m_bricks;
    int m_tileW, m_tileH; // chiều rộng và chiều cao của viên gạch
};

#endif // LEVEL_H
