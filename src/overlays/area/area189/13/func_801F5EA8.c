#include "area189_13.h"

MATCH s32 func_801F5EA8(void) {
    if ((g_InputPressed & g_InputMasks[FIELD_INPUT_MENU]) == 0) {
        return 0;
    }
    if (g_GameFlags & GAME_FLAG_MENU_LOCK) {
        return 0;
    }
    SND_PlayCue(EMI_CUE_ID(1, 5));
    g_GameStateIndex    = GAME_REQUEST_MENU;
    g_Task->header.step = 2;
    return 1;
}
