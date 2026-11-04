#include "game_00.h"

MATCH void Game_RunCameraLookState(void) {
    if (g_GameEntrySubstate == 0) {
        func_80198F1C();
    } else {
        func_801981D4();
    }
    func_801992B8();
}
