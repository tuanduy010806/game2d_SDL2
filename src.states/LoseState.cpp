#include "states/LoseState.h"
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

//  destructor
LoseState::~LoseState() {}

LoseState::LoseState(float record) : m_record(record) {}

void LoseState::Enter() {
    std::cout << "Entering LoseState..." << std::endl;
    AudioManager::Instance()->PlaySound("lose", 0);

    auto renderer = Game::Instance()->GetRenderer();
    if (!renderer) return;
    TextureManager::Instance()->Load("restartbutton", "assets/images/restartbutton.png", renderer);
    TextureManager::Instance()->Load("menu_bg", "assets/images/menu_bg.png", renderer);

    int w = Game::Instance()->GetWidth();
    int h = Game::Instance()->GetHeight();

    m_panelRect = { w / 4, h / 4, w / 2, h / 2 };
    m_restartButton = { m_panelRect.x + (m_panelRect.w / 2) - 100, m_panelRect.y + 150, 200, 75 };
}

void LoseState::HandleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mousePoint = {e.button.x, e.button.y};
        if (SDL_PointInRect(&mousePoint, &m_restartButton)) {
            AudioManager::Instance()->PlaySound("click", 0);
            Game::Instance()->ChangeState(new PlayState());
        }
    }
}

void LoseState::Update() {}

void LoseState::Render() {
    auto renderer = Game::Instance()->GetRenderer();
    if (!renderer) return;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(renderer, nullptr);

    TextureManager::Instance()->Draw("menu_bg", m_panelRect.x, m_panelRect.y, m_panelRect.w, m_panelRect.h, renderer);
    TextureManager::Instance()->Draw("restartbutton", m_restartButton.x, m_restartButton.y, m_restartButton.w, m_restartButton.h, renderer);

    SDL_Color red = {255, 50, 50, 255};
    SDL_Color white = {255, 255, 255, 255};

    // render chữ you lose7
    FontManager::Instance()->DrawText("large_main_font", "YOU LOSE!!!", red, m_panelRect.x + 75, m_panelRect.y + 30, renderer);

    // render chữ time
    std::string recordText = "Time: " + std::to_string((int)m_record) + "s";
    FontManager::Instance()->DrawText("main_font", recordText, white, m_panelRect.x + 165, m_panelRect.y + 110, renderer);
}

void LoseState::Exit() {
    std::cout << "Exiting LoseState..." << std::endl;
    TextureManager::Instance()->ClearFromTextureMap("restartbutton");
    TextureManager::Instance()->ClearFromTextureMap("menu_bg");
}
