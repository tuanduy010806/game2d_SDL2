#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SDL.h>
#include <string>

class GameState {
public:
    //  destructor
    virtual ~GameState() {}
    virtual void Enter() = 0;
    virtual void HandleEvents(SDL_Event& e) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;
};

#endif // GAMESTATE_H
