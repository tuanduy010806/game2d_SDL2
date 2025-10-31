#include "core/Game.h"
#include "states/MenuState.h"
#include <iostream>
#include <windows.h>   // 🔹 thêm dòng này

int main(int argc, char* argv[]) {
    // 🔹 Ẩn cửa sổ console (nếu có)
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

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
