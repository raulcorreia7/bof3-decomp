#include "engine/game/00/game_00.h"

MATCH void Game_CameraLookUpdate(void) {
    if (g_GameEntrySubstate == 0) {
        func_80198F1C();
    } else {
        Game_CameraLookEnd();
    }
    Area_RunLoadingFrame();
}
