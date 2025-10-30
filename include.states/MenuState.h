#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"
#include <SDL_rect.h>

union SDL_Event;
class MenuState : public GameState {
public:
    MenuState();
    virtual ~MenuState();
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;
private:
    SDL_Rect m_menuRect;
    SDL_Rect m_playButton;
    SDL_Rect m_soundButton;
    bool m_soundOn;
};

#endif // MENUSTATE_H
