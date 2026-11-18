#include "area085_13.h"

MATCH void func_801F3BEC(void) {
    if (g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 1));
    }
}
