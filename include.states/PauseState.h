#ifndef PAUSESTATE_H
#define PAUSESTATE_H
#include "GameState.h"
#include <SDL_rect.h>

union SDL_Event;

class PauseState : public GameState {
public:
    PauseState(float playTime);
    virtual ~PauseState();
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;
private:
    SDL_Rect m_panelRect;
    SDL_Rect m_resumeButton;
    SDL_Rect m_quitButton;
    SDL_Rect m_soundButton;
    bool m_soundOn;
    float m_playTime;
};

#endif // PAUSESTATE_H
