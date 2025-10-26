#include "objects/Brick.h"
#include "core/TextureManager.h"


Brick::Brick(int x, int y, int w, int h, int hp, const std::string& textureID)
    : m_hp(hp), m_originalHp(hp), m_textureID(textureID) {
    m_rect = {x, y, w, h};
}

void Brick::Draw(SDL_Renderer* renderer) {
    if (m_hp != 0) {
        std::string texID = m_textureID;
        // Logic hiển thị gạch nứt vẫn giữ nguyên
        if (m_textureID == "brickmedium" && m_hp == 1) {
            texID = "brickeasy";
        }
        TextureManager::Instance()->Draw(texID, m_rect.x, m_rect.y, m_rect.w, m_rect.h, renderer);
    }
}

void Brick::Hit() {
    if (m_hp > 0) {
        m_hp--;
    }
}
