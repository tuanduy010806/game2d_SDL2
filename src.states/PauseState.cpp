#include "states/PauseState.h"
#include "states/MenuState.h"
#include "core/Game.h"
#include "core/FontManager.h"
#include "core/AudioManager.h"
#include "core/TextureManager.h"
#include <iostream>
#include <SDL_render.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>

//  destructor
PauseState::~PauseState() {}

PauseState::PauseState(float playTime)
: m_soundOn(false)
, m_playTime(playTime)
{}

void PauseState::Enter() {
    std::cout << "Entering PauseState..." << std::endl;
    m_soundOn = !AudioManager::Instance()->IsMuted();

    auto renderer = Game::Instance()->GetRenderer();
    // check render thành công?
    if (!renderer) return;
    // load ảnh
    TextureManager::Instance()->Load("resumebutton", "assets/images/resumebutton.png", renderer);
    TextureManager::Instance()->Load("quitbutton", "assets/images/quitbutton.png", renderer);
    TextureManager::Instance()->Load("soundon", "assets/images/soundon.png", renderer);

    int w = Game::Instance()->GetWidth();
    int h = Game::Instance()->GetHeight();
    // nút chức nâng
    m_panelRect = { w / 4, h / 4, w / 2, h / 2 };
    m_resumeButton = { m_panelRect.x + (m_panelRect.w / 2) - 100, m_panelRect.y + 50, 200, 60 };
    m_soundButton = { m_panelRect.x + (m_panelRect.w / 2) - 100, m_panelRect.y + 130, 200, 60 };
    m_quitButton = { m_panelRect.x + (m_panelRect.w / 2) - 100, m_panelRect.y + 210, 200, 60 };
}

void PauseState::HandleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mousePoint = {e.button.x, e.button.y};

        if (SDL_PointInRect(&mousePoint, &m_resumeButton)) {
            AudioManager::Instance()->PlaySound("click", 0);
            Game::Instance()->PopState();
        }

        if (SDL_PointInRect(&mousePoint, &m_soundButton)) {
            AudioManager::Instance()->PlaySound("click", 0);
            AudioManager::Instance()->ToggleMute();
            m_soundOn = !AudioManager::Instance()->IsMuted();
        }

        if (SDL_PointInRect(&mousePoint, &m_quitButton)) {
            AudioManager::Instance()->PlaySound("click", 0);
            Game::Instance()->ChangeState(new MenuState());
        }
    }
}

void PauseState::Update() {}

void PauseState::Render() {
    auto renderer = Game::Instance()->GetRenderer();
    if (!renderer) return;

    // render tấm nền
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(renderer, nullptr);

    // render nút
    TextureManager::Instance()->Draw("resumebutton", m_resumeButton.x, m_resumeButton.y, m_resumeButton.w, m_resumeButton.h, renderer);
    TextureManager::Instance()->Draw("soundon", m_soundButton.x, m_soundButton.y, m_soundButton.w, m_soundButton.h, renderer);
    TextureManager::Instance()->Draw("quitbutton", m_quitButton.x, m_quitButton.y, m_quitButton.w, m_quitButton.h, renderer);

    // render chữ
    //SDL_Color white = {255, 255, 255, 255};
    //FontManager::Instance()->DrawText("main_font", "PAUSED GAME ARKANOID", white, m_panelRect.x + 102, m_panelRect.y + 10, renderer);

    SDL_Color white = {255, 255, 255, 255};      // màu chính sáng
    SDL_Color glowWhite = {255, 255, 180, 90};   // ánh sáng mờ (vàng trắng nhẹ)

    FontManager::Instance()->DrawTextWithGlow(
        "main_font",
        "PAUSED GAME ARKANOID",
        white,          // màu chữ chính
        glowWhite,      // màu phát sáng
        m_panelRect.x + 102,
        m_panelRect.y + 10,
        renderer,
        2               // cường độ sáng (bán kính)
    );
}

void PauseState::Exit() {
    std::cout << "Exiting PauseState..." << std::endl;
    TextureManager::Instance()->ClearFromTextureMap("resumebutton");
    TextureManager::Instance()->ClearFromTextureMap("quitbutton");
    TextureManager::Instance()->ClearFromTextureMap("soundon");
}
