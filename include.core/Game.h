#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <vector>
#include <string>

class GameState;

class Game {
public:
    static Game* Instance();

    bool Init(const std::string& title, int width, int height);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();

    bool Running() const { return m_running; }
    void Quit() { m_running = false; }

    SDL_Renderer* GetRenderer() const { return m_renderer; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

    const std::vector<GameState*>& GetStates() const { return m_states; }

    void PushState(GameState* state);
    void PopState();
    void ChangeState(GameState* state);
    GameState* CurrentState();

private:
    Game();
    ~Game();

    static Game* s_instance;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_running;
    int m_width, m_height;

    std::vector<GameState*> m_states;
};
#endif
