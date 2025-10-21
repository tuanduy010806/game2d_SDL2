#include "objects/Ball.h"
#include "core/TextureManager.h"

// khởi tạo bóng ban đầu với vị trí, size và vận tốc ban đầu
Ball::Ball( float x,float y, int size, const std::string& textureID)
    : m_x(x), m_y(y), m_size(size), m_textureID(textureID) {
    // Initial velocity vận tốc ban đầu
    m_velX = 350.0f;
    m_velY = -350.0f;
}
//update bóng theo từng khung hình chạy theo thời gian thực
void Ball::Update(float deltaTime, int screenW, int screenH) {
    m_x += m_velX * deltaTime;
    m_y += m_velY * deltaTime;

    // Wall collision heck va chạm với tường trái
    if (m_x <= 0) {
        m_x = 0;// kẹp bóng lại tránh tràn hình
        BounceX();
    }
    // Wall collision heck va chạm với tường phải
    if (m_x + m_size >= screenW) {
        m_x = (float)screenW - m_size;// kẹp bóng lại tránh tràn hình
        BounceX();// logic nảy lại
    }
    if (m_y <= 0) {
        m_y = 0;
        BounceY();
    }
}

void Ball::Draw(SDL_Renderer* renderer) {
    TextureManager::Instance()->Draw(m_textureID, (int)m_x, (int)m_y, m_size, m_size, renderer);
}

void Ball::Reset( float x,float  y) {
    m_x = x;
    m_y = y;
    m_velX = 350.0f;
    m_velY = -350.0f;
}

void Ball::BounceX() {
    m_velX = -m_velX;// nảy hường ngược lại theo chiều ngang
}

void Ball::BounceY() {
    m_velY = -m_velY;// nảy hướng ngược lại theo chiều dọc
}

SDL_Rect Ball::GetRect() const {
    return {(int)m_x, (int)m_y, m_size, m_size};// lấy khung hcn để chưa ảnh render
}
// set vận tốc bóng
void Ball::SetVelocity(float vx, float vy) {
    m_velX = vx;
    m_velY = vy;
}
