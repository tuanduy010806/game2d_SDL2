#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "GameState.h"
#include "core/Timer.h"
#include <SDL_rect.h>

class Paddle;
class Ball;
class Level;
union SDL_Event;

class PlayState : public GameState {
public:
    PlayState();
    virtual ~PlayState();
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;
    void ResumePlay();
private:
    void checkCollisions();
    void ResetBallOnPaddle();
    void ActivateSpeedBoost();

    Paddle* m_paddle;
    Ball* m_ball;
    Level* m_level;
    // thời gian
    Timer m_timer;
    Timer m_boostTimer;
    bool m_isBoosted;
    bool m_paused;
    bool m_gameStarted;

    SDL_Rect m_infoPanel;
    SDL_Rect m_pauseButton;
};

#endif // PLAYSTATE_H
