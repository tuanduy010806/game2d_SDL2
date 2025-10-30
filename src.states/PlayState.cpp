#include "states/PlayState.h"
#include "core/Game.h"
#include "states/PauseState.h"
#include "states/WinState.h"
#include "states/LoseState.h"
#include "core/AudioManager.h"
#include "core/FontManager.h"
#include "core/Utils.h"
#include "objects/Ball.h"
#include "objects/Brick.h"
#include "objects/Level.h"
#include "objects/Paddle.h"
#include <iostream>
#include <cmath>
#include <string>
#include <SDL_render.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include "core/TextureManager.h"

static constexpr float DEFAULT_BALL_SPEED = 500.0f;
static constexpr float MAX_BOUNCE_ANGLE = 3.14159f / 3.0f; // 60 độ

PlayState::PlayState()
: m_paddle(nullptr)
, m_ball(nullptr)
, m_level(nullptr)
, m_timer()
, m_boostTimer()
, m_isBoosted(false)
, m_paused(false)
, m_gameStarted(false)
{}

PlayState::~PlayState() {}

void PlayState::Enter() {
    std::cout << "Entering PlayState..." << std::endl;
    auto renderer = Game::Instance()->GetRenderer();
    if (!renderer) {
        std::cerr << "Renderer is null in PlayState::Enter!" << std::endl;
        return;
    }
    int w = Game::Instance()->GetWidth();
    int h = Game::Instance()->GetHeight();
    // load ảnh
    TextureManager::Instance()->Load("paddle", "assets/images/paddle.png", renderer);
    TextureManager::Instance()->Load("ball", "assets/images/ball.png", renderer);
    TextureManager::Instance()->Load("brickeasy", "assets/images/brickeasy.png", renderer);
    TextureManager::Instance()->Load("brickmedium", "assets/images/brickmedium.png", renderer);
    TextureManager::Instance()->Load("brickmedium_break", "assets/images/brickmedium_break.png", renderer);
    TextureManager::Instance()->Load("brickhard", "assets/images/brickhard.png", renderer);
    TextureManager::Instance()->Load("pausebutton", "assets/images/pausebutton.png", renderer);
    // load âm thanh
    AudioManager::Instance()->LoadSound("hit", "assets/sounds/hit.wav");
    AudioManager::Instance()->LoadSound("lose", "assets/sounds/lose.wav");
    AudioManager::Instance()->LoadSound("win", "assets/sounds/win.wav");
    AudioManager::Instance()->LoadMusic("bgm", "assets/sounds/backgroundMusic.mp3");
    // phát âm thanh nền
    AudioManager::Instance()->PlayMusic("bgm", -1);

    if (!FontManager::Instance()->Load("default", "assets/fonts/OpenSans-Regular.ttf", 24)) {
        std::cerr << "Could not load font!" << std::endl;
    }
    // khởi tạo paddle, ball, màn chơi
    m_paddle = new Paddle(w / 2 - 60, h - 40, 120, 20, "paddle");
    m_ball = new Ball(400, 560, 16, "ball");
    m_level = new Level();

    m_level->LoadMap(Utils::RandomInt(0, 3), renderer);
    ResetBallOnPaddle();

    m_infoPanel = {10, 10, 150, 40};
    m_pauseButton = {w - 50, 10, 40, 40};

    m_paused = false;
    m_gameStarted = false;
    m_isBoosted = false;
}
// ball trên paddle
void PlayState::ResetBallOnPaddle() {
    if (!m_paddle || !m_ball) return;
    float paddleX = (float)m_paddle->GetRect().x;
    float paddleW = (float)m_paddle->GetRect().w;
    float paddleY = (float)m_paddle->GetRect().y;
    float ballX = paddleX + (paddleW / 2.0f) - (m_ball->GetSize() / 2.0f);
    float ballY = paddleY - m_ball->GetSize();
    m_ball->SetVelocity(0, 0);
    m_ball->SetX(ballX);
    m_ball->SetY(ballY);
}
// debuff bóng x1.5 tốc độ trong 2s
void PlayState::ActivateSpeedBoost() {
    if (!m_ball) return;
    if (m_isBoosted) {
        m_boostTimer.Start();
    } else {
        m_isBoosted = true;
        m_boostTimer.Start();
        m_ball->SetVelocity(m_ball->GetVelX() * 1.5f, m_ball->GetVelY() * 1.5f);
    }
}

void PlayState::HandleEvents(SDL_Event& e) {
    if (m_paused) return;
    if (!m_paddle) return;

    if (e.type == SDL_MOUSEMOTION) {
        m_paddle->Update(e.motion.x, Game::Instance()->GetWidth());
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mousePoint = {e.button.x, e.button.y};

        if (!m_gameStarted) {
            m_gameStarted = true;
            m_timer.Start();
            if (m_ball) {
                m_ball->SetVelocity(0, -DEFAULT_BALL_SPEED);
            }
            AudioManager::Instance()->PlaySound("click", 0);
        }
        else if (SDL_PointInRect(&mousePoint, &m_pauseButton)) {
            m_paused = true;
            m_timer.Pause();
            if (m_isBoosted) m_boostTimer.Pause();
            Game::Instance()->PushState(new PauseState(m_timer.GetSeconds()));
        }
    }
}
// update các va chạm
void PlayState::Update() {
    if (m_paused) return;

    if (!m_gameStarted) {
        ResetBallOnPaddle();
        return;
    }

    if (!m_ball || !m_paddle || !m_level) return;

    // Kiểm tra debuff
    if (m_isBoosted && m_boostTimer.IsStarted() && m_boostTimer.GetSeconds() >= 2.0f) {
        m_isBoosted = false;
        m_boostTimer.Stop();
        if (m_ball) {
            m_ball->SetVelocity(m_ball->GetVelX() * 0.5f, m_ball->GetVelY() * 0.5f);
        }
    }
    // sủa bug bóng đi xuyên gạch ở tốc độ cao
    const float dt = 1.0f / 60.0f;
    int subSteps = 8;
    if (m_isBoosted) {
        subSteps = 8;
    }
    const float sub_dt = dt / (float)subSteps;
    for (int i = 0; i < subSteps; ++i) {
        m_ball->Update(sub_dt, Game::Instance()->GetWidth(), Game::Instance()->GetHeight());
        checkCollisions();

        if (m_level->AllCleared()) {
            break;
        }
        if (m_ball->GetY() > Game::Instance()->GetHeight()) {
            break;
        }
    }

    // check Win / Lose
    if (m_level->AllCleared()) {
        AudioManager::Instance()->StopMusic();
        AudioManager::Instance()->PlaySound("win", 0);
        Game::Instance()->ChangeState(new WinState(m_timer.GetSeconds()));
        return;
    }
    if (m_ball->GetY() > Game::Instance()->GetHeight()) {
        AudioManager::Instance()->StopMusic();
        AudioManager::Instance()->PlaySound("lose", 0);
        Game::Instance()->ChangeState(new LoseState(m_timer.GetSeconds()));
        return;
    }
}

void PlayState::checkCollisions() {
    if (!m_ball || !m_paddle || !m_level) return;

    SDL_Rect ballRect = m_ball->GetRect();
    SDL_Rect paddleRect = m_paddle->GetRect();

    if (SDL_HasIntersection(&ballRect, &paddleRect)) {
        AudioManager::Instance()->PlaySound("hit", 0);

        if (m_ball->GetVelY() > 0) {

            // Tính AABB overlap
            float ballCenterX = m_ball->GetX() + m_ball->GetSize() / 2.0f;
            float ballCenterY = m_ball->GetY() + m_ball->GetSize() / 2.0f;
            float paddleCenterX = (float)paddleRect.x + paddleRect.w / 2.0f;
            float paddleCenterY = (float)paddleRect.y + paddleRect.h / 2.0f;
            float combinedHalfW = m_ball->GetSize() / 2.0f + paddleRect.w / 2.0f;
            float combinedHalfH = m_ball->GetSize() / 2.0f + paddleRect.h / 2.0f;
            float diffX = ballCenterX - paddleCenterX;
            float diffY = ballCenterY - paddleCenterY;
            float overlapX = combinedHalfW - std::abs(diffX);
            float overlapY = combinedHalfH - std::abs(diffY);
            // Xác định hướng va chạm
            if (overlapY < overlapX) // va chạm dọc
                {
                m_ball->SetY((float)paddleRect.y - m_ball->GetSize());
                // Tính góc nảy
                float hitPoint = m_ball->GetX() + m_ball->GetSize() / 2.0f;
                float relativeHit = hitPoint - paddleCenterX;
                float normalizedHit = Utils::Clamp(relativeHit / (paddleRect.w / 2.0f), -1.0f, 1.0f);
                float bounceAngle = normalizedHit * MAX_BOUNCE_ANGLE;
                float currentSpeed = m_isBoosted ? (DEFAULT_BALL_SPEED * 2.0f) : DEFAULT_BALL_SPEED;

                m_ball->SetVelocity(currentSpeed * sin(bounceAngle), -currentSpeed * cos(bounceAngle));

            } else //va chạm ngang
             {
                m_ball->BounceX();
                if (diffX > 0) // Bóng ở bên phải paddle
                {
                    m_ball->SetX(m_ball->GetX() + overlapX);
                } else  // Bóng ở bên trái paddle
                {
                    m_ball->SetX(m_ball->GetX() - overlapX);
                }
                // va chạm cạnh
                if (m_ball->GetVelY() > 0) {
                     m_ball->BounceY();
                }
            }
        }
    }
    // ball va chạm với gạch
    for (auto& brick : m_level->GetBricks()) {
        if (brick.GetHp() == 0) continue; // gạch ko thể phá
        SDL_Rect brickRect = brick.GetRect();
        if (SDL_HasIntersection(&ballRect, &brickRect)) {
            AudioManager::Instance()->PlaySound("hit", 0);

            int hpBeforeHit = brick.GetHp();
            int originalHp = brick.GetOriginalHp();

            if (hpBeforeHit > 0) {
                brick.Hit();
                int hpAfterHit = brick.GetHp();

                if (originalHp == 2 && hpBeforeHit == 1 && hpAfterHit == 0) {
                    ActivateSpeedBoost();
                }
            }
            // sửa bug lún ball vào trong gạch
            //  Tính toán tâm và độ lún
            float ballCenterX = m_ball->GetX() + m_ball->GetSize() / 2.0f;
            float ballCenterY = m_ball->GetY() + m_ball->GetSize() / 2.0f;
            float brickCenterX = (float)brickRect.x + brickRect.w / 2.0f;
            float brickCenterY = (float)brickRect.y + brickRect.h / 2.0f;
            float combinedHalfW = m_ball->GetSize() / 2.0f + brickRect.w / 2.0f;
            float combinedHalfH = m_ball->GetSize() / 2.0f + brickRect.h / 2.0f;

            // K/c giữa các tâm
            float diffX = ballCenterX - brickCenterX;
            float diffY = ballCenterY - brickCenterY;

            // Tính độ lún
            float overlapX = combinedHalfW - std::abs(diffX);
            float overlapY = combinedHalfH - std::abs(diffY);

            //  Xác định hướng va chạm
            if (overlapX < overlapY) {
                // Va chạm ngang
                m_ball->BounceX();
                // Đẩy bóng ra theo trục X
                if (diffX > 0)// Bóng ở bên phải gạch
                {
                    m_ball->SetX(m_ball->GetX() + overlapX);
                } else // Bóng ở bên trái gạch
                {
                    m_ball->SetX(m_ball->GetX() - overlapX);
                }
            } else {
                // Va chạm dọc
                m_ball->BounceY();
                // Đẩy  bóng ra theo trục Y
                if (diffY > 0) // Bóng ở bên dưới gạch
                {
                    m_ball->SetY(m_ball->GetY() + overlapY);
                } else // Bóng ở bên trên gạch
                {
                    m_ball->SetY(m_ball->GetY() - overlapY);
                }
            }
            break;
        }
    }
}
// render game khi chơi
void PlayState::Render() {
    auto renderer = Game::Instance()->GetRenderer();
    // check render thành công?
    if (!renderer) return;
    // render tài nguyên
    if (m_paddle) m_paddle->Draw(renderer);
    if (m_ball) m_ball->Draw(renderer);
    if (m_level) m_level->Draw(renderer);

    TextureManager::Instance()->Draw("pausebutton", m_pauseButton.x, m_pauseButton.y, m_pauseButton.w, m_pauseButton.h, renderer);

    SDL_Color textColor = {255, 255, 255, 255};

    if (!m_gameStarted) { // chưa chơi
        int w = Game::Instance()->GetWidth();
        int h = Game::Instance()->GetHeight();
        FontManager::Instance()->DrawText("default", "Click to play", textColor, w / 2 - 50 , h / 2 + 200, renderer);
    }
    else if (m_timer.IsStarted()){ // đã chơi nên render đồng hồ
        std::string timeText = "Time: " + std::to_string((int)m_timer.GetSeconds()) + "s";
        FontManager::Instance()->DrawText("default", timeText, textColor, m_infoPanel.x + 5, m_infoPanel.y + 5, renderer);
    }
}
// giải phóng tài nguyên
void PlayState::Exit() {
    std::cout << "Exiting PlayState..." << std::endl;
    m_timer.Stop();
    if (m_boostTimer.IsStarted()) m_boostTimer.Stop();
    AudioManager::Instance()->StopMusic();

    delete m_paddle;    m_paddle = nullptr;
    delete m_ball;      m_ball = nullptr;
    delete m_level;     m_level = nullptr;

    TextureManager::Instance()->ClearFromTextureMap("paddle");
    TextureManager::Instance()->ClearFromTextureMap("ball");
    TextureManager::Instance()->ClearFromTextureMap("brickeasy");
    TextureManager::Instance()->ClearFromTextureMap("brickmedium");
    TextureManager::Instance()->ClearFromTextureMap("brickhard");
    TextureManager::Instance()->ClearFromTextureMap("pausebutton");

    FontManager::Instance()->ClearFromTextureMap("default");
}
// réume
void PlayState::ResumePlay() {
    m_paused = false;
    if (m_timer.IsStarted()) m_timer.Resume();
    if (m_isBoosted && m_boostTimer.IsStarted()) {
        m_boostTimer.Resume();
    }
}

