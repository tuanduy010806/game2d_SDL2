#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "states/GameState.h"
#include "objects/Paddle.h"
#include "objects/Ball.h"
#include "objects/Level.h"
#include "core/Timer.h"
#include <SDL.h>

class PlayState : public GameState {
public:
    PlayState();
    void Enter() override;
    void HandleEvents(SDL_Event& e) override;
    void Update() override;
    void Render() override;
    void Exit() override;
    std::string GetStateID() const override { return "PLAY"; }

    // Sửa: Thêm hàm để PauseState gọi (Cho logic Resume)
    void ResumePlay() { m_paused = false; m_timer.Resume(); }

private:
    Paddle* m_paddle;
    Ball* m_ball;
    Level* m_level;
    Timer m_timer;
    bool m_paused;
    SDL_Rect m_infoPanel;
    SDL_Rect m_pauseButton;
    float m_deltaTime;
};
#endif
