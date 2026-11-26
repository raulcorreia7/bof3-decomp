#include "area189_13.h"

MATCH bool func_801F5EA8(void) {
    if ((g_PadStates[0].pressed & g_InputMasks[FIELD_INPUT_MENU]) == 0) {
        return 0;
    }
    if (g_Game.flags & GAME_FLAG_MENU_LOCK) {
        return 0;
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 5));
    g_GameStateIndex         = GAME_REQUEST_MENU;
    SELF(Actor)->header.step = 2;
    return 1;
}
