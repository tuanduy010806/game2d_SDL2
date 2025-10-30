#include "states/WinState.h"
#include "states/PlayState.h"
#include "core/Game.h"
#include "core/AudioManager.h"
#include "core/FontManager.h"
#include "core/TextureManager.h"
#include <iostream>
#include <string>
#include <SDL_render.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <cmath>

// destructor
WinState::~WinState() {}

WinState::WinState(float record) : m_record(record) {}

void WinState::Enter() {
    std::cout << "Entering WinState..." << std::endl;
    AudioManager::Instance()->PlaySound("win", 0);

    auto renderer = Game::Instance()->GetRenderer();
    //check render thành công?
    if (!renderer) return;
    TextureManager::Instance()->Load("restartbutton", "assets/images/restartbutton.png", renderer);
    TextureManager::Instance()->Load("menu_bg", "assets/images/menu_bg.png", renderer);

    int w = Game::Instance()->GetWidth();
    int h = Game::Instance()->GetHeight();
    // nút restar
    m_panelRect = { w / 4, h / 4, w / 2, h / 2 };
    m_restartButton = { m_panelRect.x + (m_panelRect.w / 2) - 100, m_panelRect.y + 150, 200, 75 };
}

void WinState::HandleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mousePoint = {e.button.x, e.button.y};
        if (SDL_PointInRect(&mousePoint, &m_restartButton)) {
            AudioManager::Instance()->PlaySound("click", 0);
            Game::Instance()->ChangeState(new PlayState());
        }
    }
}

void WinState::Update() {}

void WinState::Render() {
    auto renderer = Game::Instance()->GetRenderer();
    if (!renderer) return;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(renderer, nullptr);

    TextureManager::Instance()->Draw("menu_bg", m_panelRect.x, m_panelRect.y, m_panelRect.w, m_panelRect.h, renderer);
    TextureManager::Instance()->Draw("restartbutton", m_restartButton.x, m_restartButton.y, m_restartButton.w, m_restartButton.h, renderer);
    SDL_Color orange = {255, 165, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
     // Dòng YOU WIN!!!
    FontManager::Instance()->DrawText("large_main_font", "YOU WIN!!!", orange, m_panelRect.x + 85, m_panelRect.y + 30, renderer);
    // điểm 20s - 10 điểm
    float score = 100.0f - floor(m_record / 20.0f) * 10.0f;
    if (score < 0.0f) {
    score = 0.0f;
    }
    std::string recordText = "YOUR RECORD: " + std::to_string((int)score) + "P";
    // Vẽ text điểm
    FontManager::Instance()->DrawText("main_font", recordText, white,
                                  m_panelRect.x + 125, m_panelRect.y + 110, renderer);
}

void WinState::Exit() {
    std::cout << "Exiting WinState..." << std::endl;
    TextureManager::Instance()->ClearFromTextureMap("restartbutton");
    TextureManager::Instance()->ClearFromTextureMap("menu_bg");
}
