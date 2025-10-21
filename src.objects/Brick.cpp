#include "objects/Brick.h"
#include "core/TextureManager.h"

Brick::Brick(int x, int y, int w, int h, int hp, const std::string& textureID)
    : m_hp(hp), m_textureID(textureID) {
    m_rect = {x, y, w, h};
}

void Brick::Draw(SDL_Renderer* renderer) {
    if (m_hp > 0) {
        TextureManager::Instance()->Draw(m_textureID, m_rect.x, m_rect.y, m_rect.w, m_rect.h, renderer);
    }
}

void Brick::Hit() {
    if (m_hp > 0) {
        m_hp--;
    }
}
