#ifndef LOSESTATE_H
#define LOSESTATE_H
#include "states/GameState.h"
#include <SDL.h>

class LoseState : public GameState {
public:
    LoseState(float record);
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;
    std::string GetStateID() const override { return "LOSE"; }

private:
    float m_record;
    SDL_Rect m_restartButton;
};
#endif
