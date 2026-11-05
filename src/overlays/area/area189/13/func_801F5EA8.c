#include "area189_13.h"

MATCH s32 func_801F5EA8(void) {
    if ((g_InputPressed & D_80145AB8) == 0) {
        return 0;
    }
    if (g_GameFlags & GAME_FLAG_RUN_LOCK) {
        return 0;
    }
    SND_PlayCue(EMI_CUE_ID(1, 5));
    g_GameStateIndex = GAME_REQUEST_MENU;
    g_Task->step     = 2;
    return 1;
}
