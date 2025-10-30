#ifndef WINSTATE_H
#define WINSTATE_H
#include "GameState.h"
#include <SDL_rect.h>

union SDL_Event;

class WinState : public GameState {
public:
    WinState(float record);
    virtual ~WinState();
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;
private:
    float m_record;
    SDL_Rect m_restartButton;
    SDL_Rect m_panelRect;
};

#endif // WINSTATE_H
