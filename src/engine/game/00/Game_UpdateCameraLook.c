#include "game_00.h"

MATCH void Game_UpdateCameraLook(void) {
    if (g_GameEntrySubstate == 0) {
        func_80198F1C();
    } else {
        Game_FinishCameraLook();
    }
    func_801992B8();
}
