#include "core/Game.h"
#include "states/MenuState.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game* game = Game::Instance();
    if (!game->Init("BricksBreaker", 800, 600)) {
        std::cerr << "Game initialization failed!" << std::endl;
        return -1;
    }
    game->ChangeState(new MenuState());
    game->Run();
    game->Clean();
    return 0;
}
