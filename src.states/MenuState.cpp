#include "states/MenuState.h"
#include "core/Game.h"
#include "states/PlayState.h"
#include "core/AudioManager.h"
#include "core/TextureManager.h"
#include "core/FontManager.h"
#include <iostream>
#include <SDL_render.h>
#include <SDL_events.h>
#include <SDL_pixels.h>

//  constructor
MenuState::MenuState() : m_soundOn(false) {}
MenuState::~MenuState() {}

void MenuState::Enter() {
    std::cout << "Entering MenuState..." << std::endl;
    m_soundOn = !AudioManager::Instance()->IsMuted();

    // Load tài nguyên
    auto renderer = Game::Instance()->GetRenderer();
    // check tài nguyên khởi tạo thành công?
    if (!renderer) {
        std::cerr << "Renderer is null in MenuState::Enter!" << std::endl;
        return;
    }
    // âm thanh
    AudioManager::Instance()->LoadSound("click", "assets/sounds/click.mp3");
    AudioManager::Instance()->LoadMusic("bg_music", "assets/sounds/bg_music.mp3");
    AudioManager::Instance()->PlayMusic("bg_music", -1);
    // ảnh
    TextureManager::Instance()->Load("menu_bg", "assets/images/menu_bg.png", renderer);
    TextureManager::Instance()->Load("playbutton", "assets/images/playbutton.png", renderer);
    TextureManager::Instance()->Load("soundon", "assets/images/soundon.png", renderer);

    int winW = Game::Instance()->GetWidth();
    int winH = Game::Instance()->GetHeight();

    // vị trí nút chức nâng
    m_menuRect = { winW / 4, winH / 4, winW / 2, winH / 2 };
    m_playButton = { m_menuRect.x + (m_menuRect.w / 2) - 100, m_menuRect.y + 80, 200, 75 };
    m_soundButton = { m_menuRect.x + (m_menuRect.w / 2) - 100, m_menuRect.y + 180, 200, 75 };
}

void MenuState::HandleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        SDL_Point mousePoint = {x, y};

        if (SDL_PointInRect(&mousePoint, &m_playButton)) {
            AudioManager::Instance()->PlaySound("click", 0);
            Game::Instance()->ChangeState(new PlayState());
        }

        if (SDL_PointInRect(&mousePoint, &m_soundButton)) {
            AudioManager::Instance()->PlaySound("click", 0);
            AudioManager::Instance()->ToggleMute();
            m_soundOn = !AudioManager::Instance()->IsMuted();
        }
    }
}

void MenuState::Update() {
}

void MenuState::Render() {
    auto renderer = Game::Instance()->GetRenderer();
    // check renderer thành công?
    if (!renderer) return;

    // load ảnh
    TextureManager::Instance()->Draw("menu_bg", m_menuRect.x, m_menuRect.y, m_menuRect.w, m_menuRect.h, renderer);
    TextureManager::Instance()->Draw("playbutton", m_playButton.x, m_playButton.y, m_playButton.w, m_playButton.h, renderer);
    TextureManager::Instance()->Draw("soundon", m_soundButton.x, m_soundButton.y, m_soundButton.w, m_soundButton.h, renderer);

    // render chữ
    SDL_Color white = {34, 139, 34, 255};
    FontManager::Instance()->DrawText("medium_main_font", "Bricks Breaker", white, 260, m_menuRect.y + 20, renderer);
}

void MenuState::Exit() {
    std::cout << "Exiting MenuState..." << std::endl;
    // load ảnh
    TextureManager::Instance()->ClearFromTextureMap("menu_bg");
    TextureManager::Instance()->ClearFromTextureMap("playbutton");
    TextureManager::Instance()->ClearFromTextureMap("soundon");
}
