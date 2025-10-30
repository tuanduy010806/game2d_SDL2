#include "core/Game.h"
#include "states/GameState.h"
#include "states/PlayState.h"
#include "core/TextureManager.h"
#include "core/FontManager.h"
#include "core/AudioManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <time.h>

Game* Game::s_instance = nullptr;

Game* Game::Instance() {
    if (!s_instance) {
        s_instance = new Game();
    }
    return s_instance;
}

Game::Game()
    : m_window(nullptr), m_renderer(nullptr), m_running(false), m_width(800), m_height(600) {}

Game::~Game() { }


bool Game::Init(const std::string& title, int width, int height) {
    srand((unsigned int)time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;
    if (TTF_Init() == -1) return false;


    m_width = width;
    m_height = height;
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height, SDL_WINDOW_SHOWN);
    if (!m_window) return false;

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) return false;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    TextureManager::Instance()->Load("background", "assets/images/background.png", m_renderer);
    FontManager::Instance()->Load("main_font", "assets/fonts/OpenSans-Regular.ttf", 24);
    FontManager::Instance()->Load("large_main_font", "assets/fonts/OpenSans-Regular.ttf", 72);
    FontManager::Instance()->Load("medium_main_font", "assets/fonts/OpenSans-Regular.ttf", 48);

    AudioManager::Instance();

    m_running = true;
    return true;
}

void Game::Run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (m_running) {
        frameStart = SDL_GetTicks();

        HandleEvents();
        Update();
        Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_running = false;
        }
        if (!m_states.empty()) {
            m_states.back()->HandleEvents(event);
        }
    }
}

void Game::Update() {
    if (!m_states.empty()) {
        m_states.back()->Update();
    }
}

void Game::Render() {
    SDL_RenderClear(m_renderer);
    TextureManager::Instance()->Draw("background", 0, 0, m_width, m_height, m_renderer);

    if (!m_states.empty()) {
        m_states.back()->Render();
    }
    SDL_RenderPresent(m_renderer);
}

void Game::Clean() {
    // giai phong tai nguyen state
    while (!m_states.empty()) {
        m_states.back()->Exit();
        delete m_states.back();
        m_states.pop_back();
    }
    TextureManager::Instance()->Clean();
    AudioManager::Instance()->Clean();
    FontManager::Instance()->Clean();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::PushState(GameState* state) {
    m_states.push_back(state);
    state->Enter();
}

void Game::PopState() {
    if (!m_states.empty()) {
        m_states.back()->Exit();
        delete m_states.back();
        m_states.pop_back();

        if (!m_states.empty()) {
            if (PlayState* p = dynamic_cast<PlayState*>(m_states.back())) {
                p->ResumePlay();
            }
        }
    }
}

void Game::ChangeState(GameState* state) {
    if (!m_states.empty()) {
        m_states.back()->Exit();
        delete m_states.back();
        m_states.pop_back();
    }
    m_states.push_back(state);
    state->Enter();
}

GameState* Game::CurrentState() {
    return m_states.empty() ? nullptr : m_states.back();
}
