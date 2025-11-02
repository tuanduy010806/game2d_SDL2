#ifndef WINSTATE_H
#define WINSTATE_H
#include "states/GameState.h"
#include <SDL.h>

class WinState : public GameState {
public:
    WinState(float record);
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;
    std::string GetStateID() const override { return "WIN"; }

private:
    float m_record;
    SDL_Rect m_restartButton;
};
#endif
