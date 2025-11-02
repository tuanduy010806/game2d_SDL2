#ifndef PAUSESTATE_H
#define PAUSESTATE_H
#include "states/GameState.h"
#include "core/TextureManager.h"
#include "core/AudioManager.h"
#include <SDL.h>

class PauseState : public GameState {
public:
    PauseState(float playTime);
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;
    std::string GetStateID() const override { return "PAUSE"; }

private:
    SDL_Rect m_panelRect;
    SDL_Rect m_resumeButton;
    SDL_Rect m_quitButton;
    SDL_Rect m_soundButton;
    bool m_soundOn;
    float m_playTime;
};
#endif
