#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>
#include <SDL.h>

class GameState {
public:
    virtual ~GameState() {}

    virtual void Enter() = 0;
    virtual void HandleEvents(SDL_Event& e) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;
    virtual std::string GetStateID() const = 0;
};
#endif
