#ifndef LOSESTATE_H
#define LOSESTATE_H
#include "GameState.h"
#include <SDL_rect.h>

union SDL_Event;
class LoseState : public GameState {
public:
    LoseState(float record);
    virtual ~LoseState();
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

#endif // LOSESTATE_H
