#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "states/GameState.h"
#include "core/TextureManager.h"
#include "core/AudioManager.h"
#include <SDL.h>

class MenuState : public GameState {
public:
    MenuState() {}
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;

    std::string GetStateID() const override { return "MENU"; }

private:
    SDL_Rect m_menuRect;
    SDL_Rect m_playButton;
    SDL_Rect m_soundButton;
    bool m_soundOn;
};
#endif
