#include "objects/Paddle.h"
#include "core/TextureManager.h"
#include "core/Utils.h"
// khởi tạo paddle
Paddle::Paddle(int x, int y, int w, int h, const std::string& textureID)
    : m_textureID(textureID) {
    m_rect = {x, y, w, h};
}
// update vtri paddle theo chuột
void Paddle::Update(int mouseX, int windowWidth) {
    m_rect.x = (int)Utils::Clamp((float)mouseX - m_rect.w / 2.0f, 0.0f, (float)(windowWidth - m_rect.w));
}
// vẽ
void Paddle::Draw(SDL_Renderer* renderer) {
    TextureManager::Instance()->Draw(m_textureID, m_rect.x, m_rect.y, m_rect.w, m_rect.h, renderer);
}
